#ifndef _Dactyl_Utils_h_
#define _Dactyl_Utils_h_

#include <string>

namespace Dactyl::Application
{
    class Utils
    {
        public:
            static void print_help(std::string value);
            static void print_version();
            static void parse_args(const int argc, const char *argv[]);
    };

} // namespace Dactyl.Application

#endif /* _Dactyl_Utils_h_ */