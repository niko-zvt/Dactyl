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
    }

    int Node::getNodeID()
    {
        return _nodeID;
    }

    Eigen::Vector3d Node::getCoords()
    {
        return _coords;
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