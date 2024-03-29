#ifndef BOSCONIAN_INILIKE_H
#define BOSCONIAN_INILIKE_H

#include <iostream>
#include <string>
#include <vector>
#include <SDL.h>
#include <filesystem>
#include <fstream>
#include <map>
#include "Vector2D.h"
#include "../Model/Level/LevelInfo.h"

namespace fs = std::filesystem;

struct item {
    void* value;       // Pointer to the value
    std::string type;  // Type information of the value
};

class IniLike {
public:
    explicit IniLike(const std::string& filename)
            : filename(filename) {
        // If the file doesn't exist, create it
        if (!fs::exists(filename)) {
            std::ofstream outfile(filename);
            if (!outfile.is_open()) {
                // Error: cannot create file
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
            // Error: cannot open file
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
                            else if (inner_map[key].type == typeid(Uint64).name()) {
                                Uint64 value;
                                viss >> value;
                                *reinterpret_cast<Uint64*>(inner_map[key].value) = value;
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
                            }
                            /*else if (inner_map[key].type == typeid(std::vector<Frame>).name()) {
                                std::vector<Frame>& vectorValue = *reinterpret_cast<std::vector<Frame>*>(inner_map[key].value);
                                vectorValue.clear();
                                std::istringstream vector_iss(value_str);
                                std::string vector_item;
                                while (std::getline(vector_iss, vector_item, ',')) {
                                    Frame frameValue = readFrame(vector_item);
                                    vectorValue.push_back(frameValue);
                                }
                            }*/
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
                            } else if (inner_map[key].type == typeid(LevelInfo).name()) {
                                LevelInfo& levelValue = *reinterpret_cast<LevelInfo*>(inner_map[key].value);
                                levelValue = readLevel(value_str);
                            } else if (inner_map[key].type == typeid(std::vector<LevelInfo>).name()) {
                                std::vector<LevelInfo>& vectorValue = *reinterpret_cast<std::vector<LevelInfo>*>(inner_map[key].value);
                                vectorValue.clear();
                                std::istringstream vector_iss(value_str);
                                std::string vector_item;
                                std::string current_element;
                                while (std::getline(vector_iss, vector_item, ';')) {
                                    if (!current_element.empty()) {
                                        current_element += ';';
                                    }
                                    current_element += vector_item;
                                    if (vector_item.find(']') != std::string::npos) {
                                        LevelInfo levelValue = readLevel(current_element);
                                        vectorValue.push_back(levelValue);
                                        current_element.clear();
                                    }
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
            // Error: cannot create file
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
                else if (item.type == typeid(Uint64).name()) {
                    outfile << *reinterpret_cast<Uint64*>(item.value);
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
                } /*else if (item.type == typeid(std::vector<Frame>).name()) {
                    const std::vector<Frame>& frameValue = *reinterpret_cast<const std::vector<Frame>*>(item.value);
                    for (size_t i = 0; i < frameValue.size(); ++i) {
                        if (i != 0) {
                            outfile << ',';
                        }
                        outfile << frameValue[i].filename << ':' << frameValue[i].frame.x << ';' << frameValue[i].frame.y << ';' << frameValue[i].frame.w << ';' << frameValue[i].frame.h;
                    }
                }*/
                else if (item.type == typeid(SDL_Rect).name()) {
                    SDL_Rect value = *reinterpret_cast<SDL_Rect*>(item.value);
                    outfile << value.x << ';' << value.y << ';' << value.w << ';' << value.h;
                } else if (item.type == typeid(LevelInfo).name()) {
                    const LevelInfo& levelValue = *reinterpret_cast<const LevelInfo*>(item.value);
                    outfile << writeLevel(levelValue);
                } else if (item.type == typeid(std::vector<LevelInfo>).name()) {
                    const std::vector<LevelInfo>& vectorValue = *reinterpret_cast<const std::vector<LevelInfo>*>(item.value);
                    for (size_t i = 0; i < vectorValue.size(); ++i) {
                        if (i != 0) {
                            outfile << ';';
                        }
                        outfile << "[" << writeLevel(vectorValue[i]) << "]";
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

    /*Frame readFrame(const std::string& value_str) {
        Frame frame;
        size_t pos = value_str.find(':');
        if (pos != std::string::npos) {
            frame.filename = trim(value_str.substr(0, pos));
            std::string rect_str = trim(value_str.substr(pos + 1));
            size_t pos_sep = rect_str.find(';');
            if (pos_sep != std::string::npos) {
                std::istringstream xiss(rect_str.substr(0, pos_sep));
                xiss >> frame.frame.x;
                size_t pos_sep2 = rect_str.find(';', pos_sep + 1);
                if (pos_sep2 != std::string::npos) {
                    std::istringstream yiss(rect_str.substr(pos_sep + 1, pos_sep2 - pos_sep - 1));
                    yiss >> frame.frame.y;
                    size_t pos_sep3 = rect_str.find(';', pos_sep2 + 1);
                    if (pos_sep3 != std::string::npos) {
                        std::istringstream wiss(rect_str.substr(pos_sep2 + 1, pos_sep3 - pos_sep2 - 1));
                        wiss >> frame.frame.w;
                        std::istringstream hiss(rect_str.substr(pos_sep3 + 1));
                        hiss >> frame.frame.h;
                    }
                }
            }
        }
        return frame;
    }*/

    static std::string writeLevel(const LevelInfo& level) {
        std::ostringstream oss;
        oss << "lvlNum:" << level.levelNumber << ",";
        oss << "baseShipsPos:[";
        for (size_t i = 0; i < level.basePositions.size(); ++i) {
            if (i != 0) {
                oss << ';';
            }
            oss << level.basePositions[i].x << "-" << level.basePositions[i].y;
        }
        oss << "],";
        oss << "playerPos:" << level.playerSpawn.x << "-" << level.playerSpawn.y;
        return oss.str();
    }

    LevelInfo readLevel(const std::string& value_str) {
        LevelInfo level;
        std::string stripped_value = value_str.substr(1, value_str.size() - 2);  // Remove enclosing square brackets
        std::istringstream iss(stripped_value);
        std::string token;
        while (std::getline(iss, token, ',')) {
            size_t pos = token.find(':');
            if (pos != std::string::npos) {
                std::string key = trim(token.substr(0, pos));
                std::string value = trim(token.substr(pos + 1));
                if (key == "lvlNum") {
                    std::istringstream numiss(value);
                    numiss >> level.levelNumber;
                } else if (key == "baseShipsPos") {
                    size_t pos_start = value.find('[');
                    size_t pos_end = value.find(']');
                    if (pos_start != std::string::npos && pos_end != std::string::npos) {
                        std::string vector_value = value.substr(pos_start + 1, pos_end - pos_start - 1);
                        std::istringstream vector_iss(vector_value);
                        std::string vector_item;
                        while (std::getline(vector_iss, vector_item, ';')) {
                            Vector2D pos;
                            size_t pos_sep = vector_item.find('-');
                            if (pos_sep != std::string::npos) {
                                std::istringstream xyiss(vector_item.substr(0, pos_sep));
                                xyiss >> pos.x;
                                std::istringstream yiss(vector_item.substr(pos_sep + 1));
                                yiss >> pos.y;
                            }
                            level.basePositions.push_back(pos);
                        }
                    }
                } else if (key == "playerPos") {
                    size_t pos_sep = value.find('-');
                    if (pos_sep != std::string::npos) {
                        std::istringstream xiss(value.substr(0, pos_sep));
                        xiss >> level.playerSpawn.x;
                        std::istringstream yiss(value.substr(pos_sep + 1));
                        yiss >> level.playerSpawn.y;
                    }
                }
            }
        }
        return level;
    }
};

#endif //BOSCONIAN_INILIKE_H
