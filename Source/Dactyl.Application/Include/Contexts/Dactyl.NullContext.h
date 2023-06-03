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
    
            virtual std::string getPathToKFile() override
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
