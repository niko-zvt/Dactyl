#pragma once
#ifndef _Dactyl_IElement_h_
#define _Dactyl_IElement_h_

#include "Nodes/Dactyl.INode.h"
#include <Sparse>
#include <Core>
#include <Dense>
#include <vector>

namespace Dactyl::Model
{
    class IElement
    {
        public:
            virtual int GetElementID() = 0;
            virtual int GetPropertyID() = 0;
            virtual void CalculateStiffnessMatrix(std::vector<Eigen::Triplet<double>>& localStiffnessMatrixes) = 0;
            virtual int GetNodesCount() = 0;
    };
}

#endif /* _Dactyl.IElement.h_ */