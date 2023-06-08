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
            virtual int GetNodeID() = 0;
            virtual int GetGlobalNodeID() = 0;
            virtual void SetGlobalNodeID(int id) = 0;
            virtual Eigen::Vector3d GetCoords() = 0;
    };
}

#endif /* _Dactyl.INode.h_ */