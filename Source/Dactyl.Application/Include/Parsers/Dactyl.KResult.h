#pragma once
#ifndef _Dactyl_KResult_h_
#define _Dactyl_KResult_h_

#include <string>
#include <vector>

namespace Dactyl::Application
{
    struct KProperty
    {
        std::string Head;
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

    class KResult
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

        private:
            std::vector<KProperty> _properties;
            std::vector<KSection> _sections;
            std::vector<KMaterial> _materials;
            std::vector<KNode> _nodes;
            std::vector<KElement> _elements;
    };    
}

#endif /* _Dactyl.KResult.h_ */
