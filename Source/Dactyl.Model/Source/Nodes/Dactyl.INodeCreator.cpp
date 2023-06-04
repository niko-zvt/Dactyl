#include "Nodes/Dactyl.INodeCreator.h"
#include "Nodes/Dactyl.Node.h"

namespace Dactyl::Model
{
    INodeCreatorPtr INodeCreator::getNodeCreator(const KNode &kNode)
    {
        INodeCreatorPtr creator;
        
        creator = std::make_shared<NodeCreator>(kNode);

        return creator;
    }
}