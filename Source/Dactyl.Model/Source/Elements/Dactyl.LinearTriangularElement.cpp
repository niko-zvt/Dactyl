#include "Dactyl.FEModel.h"
#include "Nodes/Dactyl.INode.h"
#include "Dofs/Dactyl.IDof.h"
#include "Elements/Dactyl.IElement.h"
#include "Elements/Dactyl.LinearTriangularElement.h"
#include <Core>
#include <Dense>
#include <vector>

namespace Dactyl::Model
{
    LinearTriangularElement::LinearTriangularElement()
    {
        // Create nodes
    }

    void LinearTriangularElement::calculateStiffnessMatrix()
    {

    }

    int LinearTriangularElement::getNodesCount()
    {
        return _nodesIDs.size();
    }
}