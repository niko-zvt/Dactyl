#pragma once
#ifndef _Dactyl_IProperty_h_
#define _Dactyl_IProperty_h_

#include <string>

namespace Dactyl::Model
{
    class IProperty
    {
        public:
            virtual int GetPropertyID() = 0;
            virtual int GetMaterialID() = 0;
            virtual int GetThermalMaterialID() = 0;
            virtual std::vector<double> GetThicknessInNodes() = 0;
            virtual std::string GetName() = 0;
    };
}

#endif /* _Dactyl.IProperty.h_ */