#pragma once
#ifndef _Dactyl_KData_h_
#define _Dactyl_KData_h_

#include <string>
#include <vector>

namespace Dactyl::Model
{
    struct KProperty
    {
        std::string Head;
        std::string Type;
        int ID;
        int SectionID;
        int MaterialID;
        int ThermalMaterialID;
    };

    struct KSection
    {
        int ID;
        double T1;
        double T2;
        double T3;
        double T4;
    };

    struct KMaterial
    {
        int ID;
        double Density;
        double ElasticModulus;
        double PoissonRatio;
        std::string Type;
        std::string Name;
    };

    struct KNode
    {
        int ID;
        double X;
        double Y;
        double Z;
    };

    struct KElement
    {
        int ID;
        int PropertyID;
        int N1;
        int N2;
        int N3;
        int N4;
    };

    class KData
    {
        public:
            void insertProperty(KProperty property)
            {
                _properties.push_back(property);
            };
            void insertSection(KSection section)
            {
                _sections.push_back(section);
            };
            void insertMaterial(KMaterial material)
            {
                _materials.push_back(material);
            };
            void insertNode(KNode node)
            {
                _nodes.push_back(node);
            };
            void insertElement(KElement element)
            {
                _elements.push_back(element);
            };

            const std::vector<KMaterial>& getMaterials()
            {
                return _materials;
            };
            const std::vector<KSection>& getSections()
            {
                return _sections;
            };
            const std::vector<KProperty>& getProperties()
            {
                return _properties;
            };
            const std::vector<KNode>& getNodes()
            {
                return _nodes;
            };
            const std::vector<KElement>& getElements()
            {
                return _elements;
            };

        private:
            std::vector<KProperty> _properties;
            std::vector<KSection> _sections;
            std::vector<KMaterial> _materials;
            std::vector<KNode> _nodes;
            std::vector<KElement> _elements;
    };    
}

#endif /* _Dactyl.KData.h_ */
