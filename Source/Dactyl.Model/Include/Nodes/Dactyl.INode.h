#pragma once
#ifndef _Dactyl_INode_h_
#define _Dactyl_INode_h_

#include <Core>
#include <Dense>

namespace Dactyl::Model
{
    class INode
    {
        public:
            virtual int getNodeID() = 0;
            virtual Eigen::Vector3d getCoords() = 0;
    };
}

#endif /* _Dactyl.INode.h_ */