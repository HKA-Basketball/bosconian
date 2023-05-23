#ifndef BOSCONIAN_CONFIG_H
#define BOSCONIAN_CONFIG_H

#include "GlobalVars.h"

namespace fs = std::filesystem;

namespace Utils {

    struct item {
        void* value;
        std::string type;
    };

    class Config {
    public:
        Config(const std::string& filename)
                : filename(filename) {
            if (!fs::exists(filename)) {
                std::ofstream outfile(filename);
                if (!outfile.is_open()) {
                    LOG("Error: cannot create file " + filename);
                    return;
                }
                outfile.close();
            }
        }

        template<typename T>
        void add_item(const std::string& section, const std::string& name, T& value) {
            items[section][name] = {&value, typeid(T).name()};
        }

        bool read() {
            std::ifstream infile(filename);
            if (!infile.is_open()) {
                LOG("Error: cannot open file " + filename);
                return false;
            }
            std::string line;
            std::string current_section;
            while (std::getline(infile, line)) {
                std::istringstream iss(line);
                std::string token;
                if (std::getline(iss, token, '=')) {
                    std::string key = trim(token);
                    if (key.empty()) {
                        continue;
                    }
                    if (key[0] == '[' && key.back() == ']') {
                        current_section = key.substr(1, key.size() - 2);
                    }
                    else {
                        std::string value_str = trim(line.substr(token.size() + 1));
                        if (!value_str.empty()) {
                            auto it = find_item(current_section, key);
                            if (it != items.end()) {
                                std::istringstream viss(value_str);
                                std::map<std::string, item>& inner_map = it->second;
                                if (inner_map[key].type == typeid(int).name()) {
                                    int value;
                                    viss >> value;
                                    *reinterpret_cast<int*>(inner_map[key].value) = value;
                                }
                                else if (inner_map[key].type == typeid(float).name()) {
                                    float value;
                                    viss >> value;
                                    *reinterpret_cast<float*>(inner_map[key].value) = value;
                                }
                                else if (inner_map[key].type == typeid(std::string).name()) {
                                    *reinterpret_cast<std::string*>(inner_map[key].value) = value_str;
                                }
                                else if (inner_map[key].type == typeid(Vector2D).name()) {
                                    Vector2D value;
                                    size_t pos = value_str.find(';');
                                    if (pos != std::string::npos) {
                                        std::istringstream xyiss(value_str.substr(0, pos));
                                        xyiss >> value.x;
                                        std::istringstream yiss(value_str.substr(pos + 1));
                                        yiss >> value.y;
                                    }
                                    *reinterpret_cast<Vector2D*>(inner_map[key].value) = value;
                                }  else if (inner_map[key].type == typeid(std::vector<Vector2D>).name()) {
                                    std::vector<Vector2D>& vectorValue = *reinterpret_cast<std::vector<Vector2D>*>(inner_map[key].value);
                                    vectorValue.clear();
                                    std::istringstream vector_iss(value_str);
                                    std::string vector_item;
                                    while (std::getline(vector_iss, vector_item, ',')) {
                                        Vector2D value;
                                        size_t pos = vector_item.find(';');
                                        if (pos != std::string::npos) {
                                            std::istringstream xyiss(vector_item.substr(0, pos));
                                            xyiss >> value.x;
                                            std::istringstream yiss(vector_item.substr(pos + 1));
                                            yiss >> value.y;
                                        }
                                        vectorValue.push_back(value);
                                    }
                                } else if (inner_map[key].type == typeid(std::vector<Frame>).name()) {
                                    std::vector<Frame>& frameValue = *reinterpret_cast<std::vector<Frame>*>(inner_map[key].value);
                                    frameValue.clear();
                                    std::istringstream frame_iss(value_str);
                                    std::string frame_item;
                                    while (std::getline(frame_iss, frame_item, ',')) {
                                        size_t name_pos = frame_item.find(':');
                                        if (name_pos != std::string::npos) {
                                            std::string name = frame_item.substr(0, name_pos);
                                            std::string rect_str = frame_item.substr(name_pos + 1);
                                            size_t rect_pos = rect_str.find(';');
                                            if (rect_pos != std::string::npos) {
                                                std::istringstream xywh_iss(rect_str.substr(0, rect_pos));
                                                std::istringstream wh_iss(rect_str.substr(rect_pos + 1));
                                                int x, y, w, h;
                                                xywh_iss >> x >> y >> w >> h;
                                                frameValue.push_back({name, {x, y, w, h}});
                                            }
                                        }
                                    }
                                }
                                else if (inner_map[key].type == typeid(SDL_Rect).name()) {
                                    SDL_Rect value;
                                    std::vector<int> values;
                                    std::istringstream rect_iss(value_str);
                                    std::string coord;
                                    while (std::getline(rect_iss, coord, ';')) {
                                        std::istringstream coord_iss(coord);
                                        int val;
                                        coord_iss >> val;
                                        values.push_back(val);
                                    }
                                    if (values.size() == 4) {
                                        value.x = values[0];
                                        value.y = values[1];
                                        value.w = values[2];
                                        value.h = values[3];
                                    }
                                    *reinterpret_cast<SDL_Rect*>(inner_map[key].value) = value;
                                } else if (inner_map[key].type == typeid(Level).name()) {
                                    Level& levelValue = *reinterpret_cast<Level*>(inner_map[key].value);
                                    levelValue = readLevel(value_str);
                                } else if (inner_map[key].type == typeid(std::vector<Level>).name()) {
                                    std::vector<Level>& vectorValue = *reinterpret_cast<std::vector<Level>*>(inner_map[key].value);
                                    vectorValue.clear();
                                    std::istringstream vector_iss(value_str);
                                    std::string vector_item;
                                    while (std::getline(vector_iss, vector_item, ',')) {
                                        Level levelValue = readLevel(vector_item);
                                        vectorValue.push_back(levelValue);
                                    }
                                }
                            }
                        }
                    }
                }
            }
            infile.close();
            return true;
        }

        bool write() {
            std::ofstream outfile(filename);
            if (!outfile.is_open()) {
                LOG("Error: cannot create file " + filename);
                return false;
            }
            for (const auto& [section, kv] : items) {
                if (!section.empty()) {
                    outfile << '[' << section << ']' << '\n';
                }
                for (const auto& [key, item] : kv) {
                    outfile << key << " = ";
                    if (item.type == typeid(int).name()) {
                        outfile << *reinterpret_cast<int*>(item.value);
                    }
                    else if (item.type == typeid(float).name()) {
                        outfile << *reinterpret_cast<float*>(item.value);
                    }
                    else if (item.type == typeid(std::string).name()) {
                        outfile << *reinterpret_cast<std::string*>(item.value);
                    }
                    else if (item.type == typeid(Vector2D).name()) {
                        Vector2D value = *reinterpret_cast<Vector2D*>(item.value);
                        outfile << value.x << ';' << value.y;
                    } else if (item.type == typeid(std::vector<Vector2D>).name()) {
                        const std::vector<Vector2D>& vectorValue = *reinterpret_cast<const std::vector<Vector2D>*>(item.value);
                        for (size_t i = 0; i < vectorValue.size(); ++i) {
                            if (i != 0) {
                                outfile << ',';
                            }
                            outfile << vectorValue[i].x << ';' << vectorValue[i].y;
                        }
                    } else if (item.type == typeid(std::vector<Frame>).name()) {
                        const std::vector<Frame>& frameValue = *reinterpret_cast<const std::vector<Frame>*>(item.value);
                        for (size_t i = 0; i < frameValue.size(); ++i) {
                            if (i != 0) {
                                outfile << ',';
                            }
                            outfile << frameValue[i].filename << ':' << frameValue[i].frame.x << ';' << frameValue[i].frame.y << ';' << frameValue[i].frame.w << ';' << frameValue[i].frame.h;
                        }
                    }
                    else if (item.type == typeid(SDL_Rect).name()) {
                        SDL_Rect value = *reinterpret_cast<SDL_Rect*>(item.value);
                        outfile << value.x << ';' << value.y << ';' << value.w << ';' << value.h;
                    } else if (item.type == typeid(Level).name()) {
                        const Level& levelValue = *reinterpret_cast<const Level*>(item.value);
                        outfile << writeLevel(levelValue);
                    } else if (item.type == typeid(std::vector<Level>).name()) {
                        const std::vector<Level>& vectorValue = *reinterpret_cast<const std::vector<Level>*>(item.value);
                        for (size_t i = 0; i < vectorValue.size(); ++i) {
                            if (i != 0) {
                                outfile << ',';
                            }
                            outfile << writeLevel(vectorValue[i]);
                        }
                    }
                    outfile << '\n';
                }
                outfile << '\n';
            }
            outfile.close();
            return true;
        }

    private:
        std::string filename;
        std::map<std::string, std::map<std::string, item>> items;

        std::string trim(const std::string& str) {
            std::string result = str;
            result.erase(0, result.find_first_not_of(" \t\n\r\f\v"));
            result.erase(result.find_last_not_of(" \t\n\r\f\v") + 1);
            return result;
        }

        std::map<std::string, std::map<std::string, item>>::iterator find_item(const std::string& section, const std::string& key) {
            auto section_it = items.find(section);
            if (section_it != items.end()) {
                auto& section_items = section_it->second;
                auto key_it = section_items.find(key);
                if (key_it != section_items.end()) {
                    return section_it; // Return the iterator of the outer map
                }
            }
            return items.end(); // Return the end iterator of the outer map
        }

        std::string writeLevel(const Level& level) {
            std::ostringstream oss;
            oss << "lvlNum:" << level.lvlNum << ",";
            oss << "baseShipsPos:";
            for (size_t i = 0; i < level.baseShipsPos.size(); ++i) {
                if (i != 0) {
                    oss << ',';
                }
                oss << level.baseShipsPos[i].x << ';' << level.baseShipsPos[i].y;
            }
            oss << ",";
            oss << "playerPos:" << level.playerPos.x << ';' << level.playerPos.y;
            return oss.str();
        }

        Level readLevel(const std::string& value_str) {
            Level level;
            std::istringstream iss(value_str);
            std::string token;
            while (std::getline(iss, token, ',')) {
                size_t pos = token.find(':');
                if (pos != std::string::npos) {
                    std::string key = trim(token.substr(0, pos));
                    std::string value = trim(token.substr(pos + 1));
                    if (key == "lvlNum") {
                        std::istringstream numiss(value);
                        numiss >> level.lvlNum;
                    } else if (key == "baseShipsPos") {
                        std::istringstream vector_iss(value);
                        std::string vector_item;
                        while (std::getline(vector_iss, vector_item, ',')) {
                            Vector2D pos;
                            size_t pos_sep = vector_item.find(';');
                            if (pos_sep != std::string::npos) {
                                std::istringstream xyiss(vector_item.substr(0, pos_sep));
                                xyiss >> pos.x;
                                std::istringstream yiss(vector_item.substr(pos_sep + 1));
                                yiss >> pos.y;
                            }
                            level.baseShipsPos.push_back(pos);
                        }
                    } else if (key == "playerPos") {
                        size_t pos_sep = value.find(';');
                        if (pos_sep != std::string::npos) {
                            std::istringstream xiss(value.substr(0, pos_sep));
                            xiss >> level.playerPos.x;
                            std::istringstream yiss(value.substr(pos_sep + 1));
                            yiss >> level.playerPos.y;
                        }
                    }
                }
            }
            return level;
        }
    };
} // Utils

#endif //BOSCONIAN_CONFIG_H
