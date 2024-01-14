#ifndef FILES_H
#define FILES_H
#include <fstream>
#include <dirent.h>
#include <sstream>
#include <vector>

#include "Log.h"

namespace Files
{
    class FileManager
    {
        public:
            FileManager();
            ~FileManager();
            void RequestIndexFile();
            void ReadFileContents();
        private:
            std::ifstream indexFile;
            std::vector<std::string> GetFilesInDirectory();
            void IdentifyIndexFile();
            void FilterFilesByExtension(std::string &ext, std::vector<std::string> fileArray);

    };
}
#endif