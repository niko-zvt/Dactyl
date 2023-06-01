#include "Dactyl.FEModel.h"
#include "Nodes/Dactyl.INode.h"
#include "Nodes/Dactyl.Node.h"
#include "Dofs/Dactyl.IDof.h"
#include "Elements/Dactyl.IElement.h"
#include "Elements/Dactyl.LinearTriangularElement.h"
#include <Core>
#include <Dense>
#include <vector>

namespace Dactyl::Model
{
    LinearTriangularElement::LinearTriangularElement(int eid, int pid, std::vector<int> nodesIDs)
    {
        _elementID = eid;
        _propertyID = pid;
        _nodesIDs = nodesIDs;
    }

    int LinearTriangularElement::getElementID()
    {
        return _elementID;
    }

    int LinearTriangularElement::getPropertyID()
    {
        return _propertyID;
    }

    void LinearTriangularElement::calculateStiffnessMatrix()
    {

    }

    int LinearTriangularElement::getNodesCount()
    {
        return _nodesIDs.size();
    }
}