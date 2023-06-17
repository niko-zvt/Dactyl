#include "Nodes/Dactyl.INode.h"
#include "Nodes/Dactyl.Node.h"
#include "Nodes/Dactyl.INodeCreator.h"
#include <Core>
#include <Dense>

namespace Dactyl::Model
{

    Node::Node(int nid, Eigen::Vector3d coords)
    {
        _nodeID = nid;
        _coords = coords;
        _dofs << 0, 0, 0,
                 0, 0, 0;
    }

    int Node::GetNodeID()
    {
        return _nodeID;
    }

    int Node::GetGlobalNodeID()
    {
        return _globalNodeID;
    }

    void Node::SetGlobalNodeID(int id)
    {
        _globalNodeID = id;
    }

    Eigen::Vector3d Node::GetCoords()
    {
        return _coords;
    }

    Eigen::Vector3d Node::GetForce()
    {
        return _nodeForce;
    }

    void Node::SetDisplacements(Eigen::Vector3d displacements)
    {
        _nodeDisplacements = displacements;
    }

    Eigen::Vector3d Node::GetDisplacements()
    {
        return _nodeDisplacements;
    }

    Eigen::Vector3i Node::GetMovementDOFs()
    {
        return _dofs.row(0);
    }

    Eigen::Vector3i Node::GetRotationDOFs()
    {
        return _dofs.row(0);
    }

    void Node::AddNodeConstraint(ConstraintType type)
    {
        if(type == ConstraintType::Free)
        {
            _dofs << 0, 0, 0,
                     0, 0, 0;
        }

        if(type == ConstraintType::FixUX)
        {
            _dofs(0, 0) = 1;
        }

        if(type == ConstraintType::FixUY)
        {
            _dofs(0, 1) = 1;
        }

        if(type == ConstraintType::FixUXY)
        {
            _dofs(0, 0) = 1;
            _dofs(0, 1) = 1;
        }
    }

    void Node::SetNodeForce(Eigen::Vector3d forceVector)
    {
        _nodeForce = forceVector;
    }

    void Node::AddNodeForce(Eigen::Vector3d forceVector)
    {
        _nodeForce = _nodeForce + forceVector;
    }

    void Node::AddParentElementID(int parentID)
    {
        _parentElementIDs.push_back(parentID);
    }

    std::vector<int> Node::GetParentElementIDs()
    {
        return _parentElementIDs;
    }

    NodeCreator::NodeCreator(const KNode &kNode) : INodeCreator(kNode)
    {
        Eigen::Vector3d coords {kNode.X, kNode.Y, kNode.Z};
        _node = std::make_shared<Node>(kNode.ID, coords);
    }

    INodePtr NodeCreator::buildNode()
    {
        return _node;
    }
}