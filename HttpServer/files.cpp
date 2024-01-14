#include "files.h"

namespace Files
{
    std::string dirString = "/home/devin/Documents/C++/HttpServer";

    FileManager::FileManager() {
        std::string ext = ".html";
        std::vector<std::string> fileArray = GetFilesInDirectory();
        FilterFilesByExtension(ext, fileArray);
    }
    FileManager::~FileManager() {}
    std::vector<std::string> FileManager::GetFilesInDirectory()
    {
        DIR *dir;
        struct dirent *ent;
        if ((dir = opendir (dirString.c_str())) != NULL) 
        {
            std::vector<std::string> fileArray;
            //print all the files and directories within directory
            while ((ent = readdir (dir)) != NULL) 
            {
                //printf ("%s\n", ent->d_name);
                fileArray.push_back(ent->d_name);
            }
            closedir (dir);
            //TODO: return std::string[] with list of all entries
            return fileArray;
        } 
        else 
        {
            //could not open directory
            perror ("ERROR");
            Log::Debug::ExitWithError("Failed to open given directory.");
        }
    }
    void FileManager::IdentifyIndexFile() {}
    void FileManager::RequestIndexFile() {}
    void FileManager::ReadFileContents() {}
    void FileManager::FilterFilesByExtension(std::string &ext, std::vector<std::string> fileArray)
    {
        std::string delimiter = ".";
        for(int i = 0; i < fileArray.size(); i++)
        {
            std::string extension = fileArray[i].substr(0, fileArray[i].find(delimiter))[1];
            if(extension == ext)
                Log::Debug::Message("Match");
            else
                Log::Debug::Message(extension);
        }
    }
}
