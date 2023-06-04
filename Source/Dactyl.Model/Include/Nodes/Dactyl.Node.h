#pragma once
#ifndef _Dactyl_Node_h_
#define _Dactyl_Node_h_

#include <Core>
#include <Dense>
#include <vector>
#include "Nodes/Dactyl.INode.h"
#include "Nodes/Dactyl.INodeCreator.h"
#include "Dofs/Dactyl.IDof.h"
#include "Dactyl.IModel.h"

namespace Dactyl::Model
{
    class Node : public INode
    {
        public:
            Node(int id, Eigen::Vector3d coords);
            virtual int getNodeID() override;
            virtual Eigen::Vector3d getCoords() override;

            Node(Node const&) = delete;
            void operator=(Node const&) = delete;

        private:
            int _nodeID;
            Eigen::Vector3d _coords;
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
