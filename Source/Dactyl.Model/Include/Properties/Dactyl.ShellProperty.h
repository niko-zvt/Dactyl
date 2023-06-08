#pragma once
#ifndef _Dactyl_ShellProperty_h_
#define _Dactyl_ShellProperty_h_

#include "Properties/Dactyl.IProperty.h"
#include "Properties/Dactyl.IPropertyCreator.h"

namespace Dactyl::Model
{
    class ShellProperty : public IProperty
    {
        public:
            ShellProperty(int ID, int materialID, int thermalMaterialID, std::vector<double> thicknessInNodes, std::string name);
            virtual int GetPropertyID() override;
            virtual int GetMaterialID() override;
            virtual int GetThermalMaterialID() override;
            virtual std::vector<double> GetThicknessInNodes() override;
            virtual std::string GetName() override;
            ShellProperty(ShellProperty const&) = delete;
            void operator=(ShellProperty const&) = delete;

        private:
            int _propertyID;
            int _materialID;
            int _thermalMaterialID;
            std::string _name;
            std::vector<double> _thicknessInNodes;
    };

    class ShellPropertyCreator : public IPropertyCreator
    {
        public:
            ShellPropertyCreator(const KProperty& kProperty, const KSection& kSection);
            IPropertyPtr buildProperty();
        
        private:
            IPropertyPtr _property;
    };
}

#endif /* _Dactyl.ShellProperty.h_ */
