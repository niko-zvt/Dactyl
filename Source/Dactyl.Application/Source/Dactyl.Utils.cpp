#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Dactyl.Utils.h"
#include "Dactyl.Version.h" //Will be generated by CMake

namespace Dactyl::Application
{
    void Utils::print_string(std::string value)
    {
        std::cout 
            << value
            << std::endl;
    }

    void Utils::print_help(std::string value)
    {
        std::cout
            << "Usage: " << value << " <option(s)>\n"
            << "Options:\n"
            << "\t-h, --help    Show this help message\n"
            << "\t-v, --version Show version of program\n"
            << std::endl;
    }

    void Utils::print_version()
    {
        std::cout 
            << "Version: "
            << g_version
            << std::endl;
    }

    void Utils::parse_args(const int argc, const char *argv[])
    {
        for(int i = 0; i < argc; i++)
        {
            std::string param_name = argv[i];

            if(param_name == "-h" || param_name == "--help")
            {
                print_help(argv[0]);
                continue;
            }
            if(param_name == "-v" || param_name == "--version")
            {
                print_version();
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
