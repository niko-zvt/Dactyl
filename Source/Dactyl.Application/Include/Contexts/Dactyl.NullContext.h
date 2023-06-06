#pragma once
#ifndef _Dactyl_NullContext_h_
#define _Dactyl_NullContext_h_

#include "Dactyl.IContext.h"

namespace Dactyl::Application
{
    class NullContext : public IContext
    {
        public:
            NullContext() 
            {

            }
    
            virtual bool isRunable() override
            {
                return false;
            }

            virtual const std::string& getAppName() override
            {
                return "";
            }

            virtual void setAppName(const std::string& path) override
            {
                // Do nothing
            }

            virtual const std::string& getAppPath() override
            {
                return "";
            }

            virtual void setAppPath(const std::string& path) override
            {
                // Do nothing
            }

            virtual const std::string& getPathToKFile() override
            {
                return "";
            }

            virtual void setPathToKFile(const std::string& path) override
            {
                // Do nothing
            }

            virtual void makeRunable() override
            {
                // Do nothing
            }

            NullContext(NullContext const&) = delete;
            void operator=(NullContext const&) = delete;
    };
}

#endif /* _Dactyl.NullContext.h_ */
