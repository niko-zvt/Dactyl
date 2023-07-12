#pragma once
#ifndef _Dactyl_Node_h_
#define _Dactyl_Node_h_

#include <Eigen/Core>
#include <Eigen/Dense>
#include <vector>
#include "Nodes/Dactyl.INode.h"
#include "Nodes/Dactyl.INodeCreator.h"
#include "Dactyl.IModel.h"

namespace Dactyl::Model
{
    class Node : public INode
    {
        public:
            Node(int id, Eigen::Vector3d coords);
            virtual int GetNodeID() override;
            virtual int GetGlobalNodeID() override;
            virtual void SetGlobalNodeID(int id) override;
            virtual Eigen::Vector3d GetCoords() override;
            virtual Eigen::Vector3d GetForce() override;
            virtual Eigen::Vector3i GetMovementDOFs() override;
            virtual Eigen::Vector3i GetRotationDOFs() override;
            virtual void SetDisplacements(Eigen::Vector3d displacements) override;
            virtual Eigen::Vector3d GetDisplacements() override;
            virtual void AddNodeConstraint(ConstraintType type) override;
            virtual void SetNodeForce(Eigen::Vector3d forceVector) override;
            virtual void AddNodeForce(Eigen::Vector3d forceVector) override;
            virtual void AddParentElementID(int parentID) override;
            virtual std::vector<int> GetParentElementIDs() override;

            Node(Node const&) = delete;
            void operator=(Node const&) = delete;

        private:
            int _globalNodeID = -1;
            int _nodeID = -1;
            Eigen::Matrix<int, 2, 3> _dofs;
            Eigen::Vector3d _coords{0,0,0};
            Eigen::Vector3d _nodeForce{0,0,0};
            Eigen::Vector3d _nodeDisplacements{0,0,0};
            std::vector<int> _parentElementIDs;
    };

    class NodeCreator : public INodeCreator
    {
        public:
            NodeCreator(const KNode& kNode);
            INodePtr buildNode();
        
        private:
            INodePtr _node;
    };
}

#endif /* _Dactyl.Node.h_ */
