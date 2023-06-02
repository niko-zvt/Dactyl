#pragma once
#ifndef _Dactyl_KResult_h_
#define _Dactyl_KResult_h_

#include <string>
#include <vector>

namespace Dactyl::Application
{
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
            void setMaterial(KMaterial material)
            {
                _materials.push_back(material);
            };
            void setNode(KNode node)
            {
                _nodes.push_back(node);
            };
            void setElement(KElement element)
            {
                _elements.push_back(element);
            };

        private:
            std::vector<KMaterial> _materials;
            std::vector<KNode> _nodes;
            std::vector<KElement> _elements;
    };    
}

#endif /* _Dactyl.KResult.h_ */
