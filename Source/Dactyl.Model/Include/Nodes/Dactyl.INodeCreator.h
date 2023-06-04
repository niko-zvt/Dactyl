#pragma once
#ifndef _Dactyl_INodeCreator_h_
#define _Dactyl_INodeCreator_h_

#include "Nodes/Dactyl.INode.h"
#include "Dactyl.KData.h"
#include "Dactyl.ModelAliases.h"

namespace Dactyl::Model
{
    class INodeCreator
    {
        protected:
            INodeCreator(const KNode& kNode) {};
        
        public:
            virtual INodePtr buildNode() = 0;
            static INodeCreatorPtr getNodeCreator(const KNode& kNode);
    };
}

#endif /* _Dactyl.INodeCreator.h_ */