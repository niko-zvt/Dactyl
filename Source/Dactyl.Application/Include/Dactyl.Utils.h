#pragma once
#ifndef _Dactyl_Utils_h_
#define _Dactyl_Utils_h_

#include <string>
#include <vector>

namespace Dactyl::Application
{
    class Utils
    {
        public:
            static void print_string(std::string value);
            static void print_help(std::string value);
            static void print_version();
            static void parse_args(const int argc, const char *argv[]);

            static std::string to_string(bool value);
            static std::vector<std::string> split_string(std::string str);

            static double to_double(std::string str);

            static int to_int(std::string str);
    };
}

#endif /* _Dactyl.Utils.h_ */