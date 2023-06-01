#pragma once
#ifndef _Dactyl_IElement_h_
#define _Dactyl_IElement_h_

#include "Nodes/Dactyl.INode.h"
#include <Core>
#include <Dense>
#include <vector>

namespace Dactyl::Model
{
    class IElement
    {
        public:
            virtual int getElementID() = 0;
            virtual int getPropertyID() = 0;
            virtual void calculateStiffnessMatrix() = 0;
            virtual int getNodesCount() = 0;
    };
}

#endif /* _Dactyl.IElement.h_ */