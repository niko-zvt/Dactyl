#pragma once
#ifndef _Dactyl_IProperty_h_
#define _Dactyl_IProperty_h_

#include <string>

namespace Dactyl::Model
{
    class IProperty
    {
        public:
            virtual int getPropertyID() = 0;
            virtual int getMaterialID() = 0;
            virtual int getThermalMaterialID() = 0;
            virtual std::string getName() = 0;
    };
}

#endif /* _Dactyl.IProperty.h_ */