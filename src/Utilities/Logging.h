#ifndef BOSCONIAN_LOGGING_H
#define BOSCONIAN_LOGGING_H

#include <iostream>
#include <string>
#include <fstream>
#include <chrono>

#define LOG(x) Utils::log(x)

namespace Utils {
    /**
     * Logs a floating-point message to the console.
     * \param message The floating-point value to log.
     */
    void log(float message);

    /**
     * Logs a string message to the console.
     * \param message The string to log.
     */
    void log(std::string message);

} // Utils

#endif //BOSCONIAN_LOGGING_H
