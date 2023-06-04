#pragma once
#ifndef _Dactyl_IElementCreator_h_
#define _Dactyl_IElementCreator_h_

#include "Elements/Dactyl.IElement.h"
#include "Dactyl.KData.h"
#include "Dactyl.ModelAliases.h"

namespace Dactyl::Model
{
    class IElementCreator
    {
        protected:
            IElementCreator(const KElement& kElement) {};
        
        public:
            virtual IElementPtr buildElement() = 0;
            static IElementCreatorPtr getElementCreator(const KElement& kElement);
    };
}

#endif /* _Dactyl.IElementCreator.h_ */