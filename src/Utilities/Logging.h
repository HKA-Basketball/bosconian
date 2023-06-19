#ifndef BOSCONIAN_LOGGING_H
#define BOSCONIAN_LOGGING_H

#include <iostream>
#include <string>
#include <fstream>
#include <chrono>

#define LOG(x) Utils::log(x)

namespace Utils {
    void log(float message);

    void log(std::string message);

} // Utils

#endif //BOSCONIAN_LOGGING_H
