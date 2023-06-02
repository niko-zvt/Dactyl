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

        private:
            std::vector<KMaterial> _materials;
            std::vector<KNode> _nodes;
    };    
}

#endif /* _Dactyl.KResult.h_ */
