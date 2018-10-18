//
// Created by Ryan on 17/10/2018.
//

#include "utils.hpp"
#include <vector>

#if defined(_WIN32)
  #include <windows.h>
#elif defined(__linux__)
  #include <sstream>
  #include <unistd.h>
#elif defined(__APPLE__)
  #include <mach-o/dyld.h>
#endif

std::string directory;

std::string get_running_dir()
{
    if(directory.empty())
    {
        unsigned int bufferSize = 512;
        std::vector<char> buffer(bufferSize + 1);

#if defined(_WIN32)
        GetModuleFileName(NULL, &buffer[0], bufferSize);

#elif defined(__linux__)
        int pid = getpid();

        std::ostringstream oss;
        oss << "/proc/" << pid << "/exe";
        std::string link = oss.str();

        int count = readlink(link.c_str(), &buffer[0], bufferSize);
        if(count == -1) throw std::runtime_error("Could not read symbolic link");
        buffer[count] = '\0';

#elif defined(__APPLE__)
        if(_NSGetExecutablePath(&buffer[0], &bufferSize))
        {
            buffer.resize(bufferSize);
            _NSGetExecutablePath(&buffer[0], &bufferSize);
        }

#else
        print("Error: can't find the executeable on this platform");

#endif
        directory = std::string(&buffer[0]);
        directory = directory.substr(0, directory.find_last_of("\\/") + 1);
    }

    return directory;
}