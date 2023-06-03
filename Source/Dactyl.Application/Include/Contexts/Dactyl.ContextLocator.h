#pragma once
#ifndef _Dactyl_ContextLocator_h_
#define _Dactyl_ContextLocator_h_

#include "Dactyl.IContext.h"
#include "Dactyl.NullContext.h"

namespace Dactyl::Application
{
    class ContextLocator
    {
        public:
            static IContext& getContext();
            static void provideContext(IContext* context);
    
        private:
            static void init();
 
            static NullContext nullContext;
            static IContext* _context;
    };
}

#endif /* _Dactyl.ContextLocator.h_ */