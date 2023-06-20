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
            static void parse_args(const int argc, const char *argv[]);

            static void print_string(std::string value, bool isEndl = true);
            static void print_help(std::string value);
            static void print_version();

            static std::string to_string(bool value);
            static std::vector<std::string> split_string(std::string str);

            static double to_double(std::string str);

            static int to_int(std::string str);

            static void ConfigurateTest1();
            static void ConfigurateTest2();
            static void ConfigurateTest3();
    };
}

#endif /* _Dactyl.Utils.h_ */