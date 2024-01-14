#include "Log.h"

namespace Log
{    
    Debug::Debug()
    {

    }

    Debug::~Debug()
    {

    }

    void Log::Debug::Message(const std::string &message)
    {
        std::cout << message << std::endl;
    }

    void Log::Debug::ExitWithError(const std::string &message)
    {
        std::cout << message << std::endl;
    }
} // namespace Error