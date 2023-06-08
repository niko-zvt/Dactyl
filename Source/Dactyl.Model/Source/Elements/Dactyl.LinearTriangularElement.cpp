#include "Dactyl.FEModel.h"
#include "Nodes/Dactyl.INode.h"
#include "Nodes/Dactyl.Node.h"
#include "Dofs/Dactyl.IDof.h"
#include "Dactyl.ModelLocator.h"
#include "Elements/Dactyl.IElement.h"
#include "Elements/Dactyl.IElementCreator.h"
#include "Elements/Dactyl.LinearTriangularElement.h"
#include <Sparse>
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

    int LinearTriangularElement::GetElementID()
    {
        return _elementID;
    }

    int LinearTriangularElement::GetPropertyID()
    {
        return _propertyID;
    }

    void LinearTriangularElement::CalculateStiffnessMatrix(std::vector<Eigen::Triplet<double>>& localStiffnessMatrixes)
    {
        Dactyl::Model::IModel& model = Dactyl::Model::ModelLocator::getModel();
        auto D = 0.0;
    }

    int LinearTriangularElement::GetNodesCount()
    {
        return _nodesIDs.size();
    }

    LinearTriangularCreator::LinearTriangularCreator(const KElement &kElement) : IElementCreator(kElement)
    {
        std::vector<int> nodesIDs { kElement.N1, kElement.N2, kElement.N3 };
        _element = std::make_shared<LinearTriangularElement>(kElement.ID, kElement.PropertyID, nodesIDs);
    }

    IElementPtr LinearTriangularCreator::buildElement()
    {
        return _element;
    }
}
