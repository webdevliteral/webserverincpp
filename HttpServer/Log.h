#ifndef LOG_H
#define LOG_H
#include <string>
#include <iostream>

namespace Log
{    
    class Debug
    {
        public:
            Debug();
            ~Debug();
            static void Message(const std::string &message);
            static void ExitWithError(const std::string &message);
        private:
        
    };
} // namespace Error
#endif