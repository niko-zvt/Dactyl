#include "Elements/Dactyl.IElementCreator.h"
#include "Elements/Dactyl.LinearTriangularElement.h"

namespace Dactyl::Model
{
    IElementCreatorPtr IElementCreator::getElementCreator(const KElement &kElement)
    {
        IElementCreatorPtr creator;
        auto type = kElement.Type;

        if (type == "linear_triangular" || kElement.N3 == kElement.N4)
        {
            creator = std::make_shared<LinearTriangularCreator>(kElement);
        }
        else if (type == "CQUAD4")
        {
            // Do nothing
        }
        else
        {
            throw std::invalid_argument("Unknown type of KElement.");
        }

        return creator;
    }
}
