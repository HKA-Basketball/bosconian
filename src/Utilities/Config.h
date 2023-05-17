#ifndef BOSCONIAN_CONFIG_H
#define BOSCONIAN_CONFIG_H

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
                    }
                    else if (item.type == typeid(SDL_Rect).name()) {
                        SDL_Rect value = *reinterpret_cast<SDL_Rect*>(item.value);
                        outfile << value.x << ';' << value.y << ';' << value.w << ';' << value.h;
                    }
                    outfile << '\n';
                }
                outfile << '\n';
            }
            outfile.close();
            return true;
        }

    private:
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

        std::string filename;
        std::map<std::string, std::map<std::string, item>> items;
    };
} // Utils

#endif //BOSCONIAN_CONFIG_H
