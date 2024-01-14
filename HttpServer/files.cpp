#include "files.h"

namespace Files
{
    // TODO: relative pathing to keep everything contained inside the working directory
    // std::string dirString = "/home/devin/Documents/C++/HttpServer"; //linux path
    std::string dirString = "/home/devin/webserverincpp/HttpServer"; // windows path using WSL

    FileManager::FileManager()
    {
        std::string ext = ".html";
        std::vector<std::string> fileArray = GetFilesInDirectory();
        FilterFilesByExtension(ext, fileArray);
    }
    FileManager::~FileManager() {}
    std::vector<std::string> FileManager::GetFilesInDirectory()
    {
        DIR *dir;
        struct dirent *ent;
        if ((dir = opendir(dirString.c_str())) != NULL)
        {
            std::vector<std::string> fileArray;
            // print all the files and directories within directory
            while ((ent = readdir(dir)) != NULL)
            {
                // printf ("%s\n", ent->d_name);
                fileArray.push_back(ent->d_name);
            }
            closedir(dir);
            // TODO: return std::string[] with list of all entries
            return fileArray;
        }
        else
        {
            // could not open directory
            perror("ERROR");
            Log::Debug::ExitWithError("Failed to open given directory.");
        }
    }
    void FileManager::IdentifyIndexFile() {}

    FileInfo FileManager::RequestIndexFile()
    {
        return indexFile;
    }

    FileInfo FileManager::ReadFileContents(std::string filename, std::string extension)
    {
        FileInfo info;
        std::ifstream file(filename + extension);
        std::string rawContents;
        std::string line;

        while (std::getline(file, line))
        {
            rawContents += line;
        }

        info.filename = filename;
        info.extension = extension;
        info.contents = rawContents;

        return FileInfo(info);
    }

    void FileManager::FilterFilesByExtension(std::string &ext, std::vector<std::string> fileArray)
    {
        std::string delimiter = ".";
        for (int i = 0; i < fileArray.size(); i++)
        {
            std::string extension;
            std::string filename = fileArray[i].substr(0, fileArray[i].find(delimiter));
            extension = fileArray[i].substr(filename.size());

            if (extension == ext)
            {

                // add file to our cached file info if there is actual content
                FileInfo file = ReadFileContents(filename, extension);
                if (file.contents.size() > 0)
                {
                    indexFile = file;
                }
            }
            /* else
                Log::Debug::Message(extension); */
        }
    }
}
