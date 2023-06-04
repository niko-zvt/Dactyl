#pragma once
#ifndef _Dactyl_IPropertyCreator_h_
#define _Dactyl_IPropertyCreator_h_

#include "Properties/Dactyl.IProperty.h"
#include "Dactyl.KData.h"
#include "Dactyl.ModelAliases.h"

namespace Dactyl::Model
{
    class IPropertyCreator
    {
        protected:
            IPropertyCreator(const KProperty& kProperty, const KSection& kSection) {};
        
        public:
            virtual IPropertyPtr buildProperty() = 0;
            static IPropertyCreatorPtr getPropertyCreator(const KProperty& kProperty, const KSection& kSection);
    };
}

#endif /* _Dactyl.IPropertyCreator.h_ */