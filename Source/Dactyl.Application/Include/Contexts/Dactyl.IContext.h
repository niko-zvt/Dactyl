#pragma once
#ifndef _Dactyl_IContext_h_
#define _Dactyl_IContext_h_

#include <string>

namespace Dactyl::Application
{
    class IContext
    {
        public:
            virtual bool isRunable() = 0;
            virtual void makeRunable() = 0;
            virtual std::string getPathToKFile() = 0;
            virtual void setPathToKFile(const std::string& path) = 0;
    };
}

#endif /* _Dactyl.IContext.h_ */