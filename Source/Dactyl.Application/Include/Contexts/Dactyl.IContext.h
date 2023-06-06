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
            
            virtual const std::string& getAppName() = 0;
            virtual void setAppName(const std::string& appName) = 0;

            virtual const std::string& getAppPath() = 0;            
            virtual void setAppPath(const std::string& appPath) = 0;  
            
            virtual const std::string& getPathToKFile() = 0;
            virtual void setPathToKFile(const std::string& path) = 0;
    };
}

#endif /* _Dactyl.IContext.h_ */