#pragma once
#ifndef _Dactyl_INode_h_
#define _Dactyl_INode_h_

#include "Elements/Dactyl.IElement.h"
#include <Core>
#include <Dense>

namespace Dactyl::Model
{
    enum class ConstraintType
    {
        Free = 0,
        FixUX = 1,
        FixUY = 2,
        FixUXY = 3,
    };

    class INode
    {
        public:
            virtual int GetNodeID() = 0;
            virtual int GetGlobalNodeID() = 0;
            virtual void SetGlobalNodeID(int id) = 0;
            virtual Eigen::Vector3d GetCoords() = 0;
            virtual Eigen::Vector3d GetForce() = 0;
            virtual Eigen::Vector3i GetMovementDOFs() = 0;
            virtual Eigen::Vector3i GetRotationDOFs() = 0;
            virtual void SetDisplacements(Eigen::Vector3d displacements) = 0;
            virtual Eigen::Vector3d GetDisplacements() = 0;
            virtual void AddNodeConstraint(ConstraintType type) = 0;
            virtual void SetNodeForce(Eigen::Vector3d forceVector) = 0;
            virtual void AddNodeForce(Eigen::Vector3d forceVector) = 0;
            virtual void AddParentElementID(int parentID) = 0;
            virtual std::vector<int> GetParentElementIDs() = 0;
    };
}

#endif /* _Dactyl.INode.h_ */