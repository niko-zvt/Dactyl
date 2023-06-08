#include "Properties/Dactyl.IProperty.h"
#include "Properties/Dactyl.ShellProperty.h"
#include "Properties/Dactyl.IPropertyCreator.h"

namespace Dactyl::Model
{
    ShellProperty::ShellProperty(int ID, int materialID, int thermalMaterialID, std::vector<double> thicknessInNodes, std::string name)
    {
        _propertyID = ID;
        _materialID = materialID;
        _thermalMaterialID = thermalMaterialID;
        _thicknessInNodes = thicknessInNodes;
        _name = name;
    }

    int ShellProperty::GetPropertyID()
    {
        return _propertyID;
    }

    int ShellProperty::GetMaterialID()
    {
        return _materialID;
    }

    int ShellProperty::GetThermalMaterialID()
    {
        return _thermalMaterialID;
    }

    std::vector<double> ShellProperty::GetThicknessInNodes()
    {
        return _thicknessInNodes;
    }

    std::string ShellProperty::GetName()
    {
        return _name;
    }

    ShellPropertyCreator::ShellPropertyCreator(const KProperty &kProperty, const KSection &kSection) : IPropertyCreator(kProperty, kSection)
    {
        std::vector<double> thickness{ kSection.T1, kSection.T2, kSection.T3, kSection.T4 };
        _property = std::make_shared<ShellProperty>(kProperty.ID,
                                                    kProperty.MaterialID,
                                                    kProperty.ThermalMaterialID,
                                                    thickness,
                                                    kProperty.Head);
    }

    IPropertyPtr ShellPropertyCreator::buildProperty()
    {
        return _property;
    };
}