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
            virtual void setNodeID(int id) = 0;
            virtual Eigen::Vector<double, 3> getCoords() = 0;
            virtual void setNodeCoords(Eigen::Vector<double, 3> coords) = 0;
    };
}

#endif /* _Dactyl.INode.h_ */