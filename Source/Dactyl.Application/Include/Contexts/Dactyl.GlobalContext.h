#pragma once
#ifndef _Dactyl_GlobalContext_h_
#define _Dactyl_GlobalContext_h_

#include "Dactyl.IContext.h"

namespace Dactyl::Application
{
    class GlobalContext : public IContext
    {
        public:
            GlobalContext() {};
    
            virtual bool isRunable() override;
            virtual const std::string& getPathToKFile() override;
            virtual const std::string& getAppName() override;
            virtual const std::string& getAppPath() override;
            virtual void setAppName(const std::string& appName) override;
            virtual void setAppPath(const std::string& appPath) override;
            virtual void setPathToKFile(const std::string& path) override;
            virtual void makeRunable() override;

            GlobalContext(GlobalContext const&) = delete;
            void operator=(GlobalContext const&) = delete;
        
        private:
            bool _isRunable = false;
            std::string _appName = "";
            std::string _appPath = "";
            std::string _pathToKFile = "";
    };
}

#endif /* _Dactyl.GlobalContext.h_ */
