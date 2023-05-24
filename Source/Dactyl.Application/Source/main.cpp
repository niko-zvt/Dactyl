#include <iostream>
#include "Dactyl.Utils.h"
#include "Dactyl.Model.h"

int main(int argc, char *argv[])
{

    if(argc > 1)
    {
        Dactyl::Application::Utils::parse_args(argc, const_cast<const char**>(argv));
    }

    hello_model();

    return 0;
}
