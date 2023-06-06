#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Dactyl.Utils.h"
#include "Dactyl.ContextLocator.h"
#include "Dactyl.Version.h" //Will be generated by CMake

namespace Dactyl::Application
{
    void Utils::parse_args(const int argc, const char *argv[])
    {
        // Get context
        Dactyl::Application::IContext& context = Dactyl::Application::ContextLocator::getContext();

        for(int i = 0; i < argc; i++)
        {
            std::string param_name = argv[i];
            if(i == 0)
            {
                std::string fullPath = argv[i];
                std::size_t found = fullPath.find_last_of("/\\");
                auto appPath = fullPath.substr(0, found);
                auto appName = fullPath.substr(found + 1);
                context.setAppPath(appPath);
                context.setAppName(appName);
                continue;
            }
            if(param_name == "-h" || param_name == "--help")
            {
                print_help(argv[0]);
                continue;
            }
            if(param_name == "-v" || param_name == "--version")
            {
                print_version();
                continue;
            }
            if (param_name == "-k" || param_name == "--kfile")
            {
                std::string path = argv[i + 1];
                // TODO: Full/relative paths - auto fullPath = context.getAppPath() + path;
                context.setPathToKFile(path);
                continue;
            }
            if (param_name == "-r" || param_name == "--run")
            {
                context.makeRunable();
                continue;
            }
        }
    }

    std::string Utils::to_string(bool value)
    {
        if (value)
            return "true";
        
        return "false";
    }

    std::vector<std::string> Utils::split_string(std::string inputString)
    {
        std::vector<std::string> wordVector;
        std::stringstream stringStream(inputString);
        std::string line;

        while(std::getline(stringStream, line)) 
        {
            std::size_t prev = 0, pos;
            while ((pos = line.find_first_of(" \t", prev)) != std::string::npos)
            {
                if (pos > prev)
                    wordVector.push_back(line.substr(prev, pos-prev));
                prev = pos+1;
            }
            if (prev < line.length())
                wordVector.push_back(line.substr(prev, std::string::npos));
        }

        return wordVector;
    }

    void Utils::print_string(std::string value, bool isEndl)
    {
        std::cout << value;

        if (isEndl)
        {
            std::cout << std::endl;
        }
    }

    void Utils::print_help(std::string value)
    {
        std::cout
            << "Usage: " << value << " [OPTION(S)]\n"
            << "Options:\n"
            << "\t-h, --help\t\tShow this help message\n"
            << "\t-v, --version\t\tShow version of program\n"
            << "\n"
            << "\t-r, --run\t\tRequired parameter for starting the calculation\n"
            << "\t-k, --kfile [STRING]\tLocation of *.k mesh file\n"
            << "\t                    \t\"C:\\\\Mesh\\\\example.k\" or \"./Resources/Meshes/example.k\"\n"
            << std::endl;
    }

    void Utils::print_version()
    {
        std::cout
            << "Version: "
            << g_version
            << std::endl;
    }

    double Utils::to_double(std::string str)
    {
        std::string::size_type sz; // alias of size_t
        double result = std::stod(str, &sz);
        return result;
    }

    int Utils::to_int(std::string str)
    {
        int result = std::stoi(str);
        return result;
    }
}
