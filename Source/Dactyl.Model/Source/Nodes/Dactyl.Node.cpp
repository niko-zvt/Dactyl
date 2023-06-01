#include "Nodes/Dactyl.INode.h"
#include "Nodes/Dactyl.Node.h"
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
}