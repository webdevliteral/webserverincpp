#ifndef FILES_H
#define FILES_H
#include <fstream>
#include <dirent.h>
#include <sstream>
#include <vector>

#include "Log.h"

namespace Files
{
    struct FileInfo
    {
        std::string filename;
        std::string extension;
        std::string contents;
    };

    class FileManager
    {
    public:
        FileManager();
        ~FileManager();
        FileInfo RequestIndexFile();
        FileInfo ReadFileContents(std::string filename, std::string extension);

    private:
        FileInfo indexFile;
        std::vector<std::string> GetFilesInDirectory();
        void IdentifyIndexFile();
        void FilterFilesByExtension(std::string &ext, std::vector<std::string> fileArray);
    };
}
#endif