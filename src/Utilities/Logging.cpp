#include "Logging.h"

namespace Utils {
    void log(float message)
    {
        log(std::to_string(message));
    }

    void log(std::string message)
    {
        std::fstream file;

        /*static char file_path[256];
        static bool is_init = false;

        if (!is_init)
        {
            const auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            std::strftime(file_path, 256, ".\\Logs\\%d-%m-%Y-%H-%M-%S.log", std::localtime(&time));

            is_init = true;
            file.open(file_path, std::ios::out | std::ios::in | std::ios::trunc);
        }
        else
            file.open(file_path, std::ios::out | std::ios::in | std::ios::app);*/

        //if (!file.is_open())
        //    return;

        static char curTime[11];
        std::string out;

        const auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        std::strftime(curTime, 256, "[%H:%M:%S] ", std::localtime(&time));
        out += curTime;
        out += message;

        // Only for live LOG
        std::cout << out << std::endl;

        //file << out << std::endl;
        //file.close();
    }
} // Utils