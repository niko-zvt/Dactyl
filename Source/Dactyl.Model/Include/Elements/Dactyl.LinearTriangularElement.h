#pragma once
#ifndef _Dactyl_LinearTriangularElement_h_
#define _Dactyl_LinearTriangularElement_h_

#include <Core>
#include <Dense>
#include <vector>
#include "Nodes/Dactyl.INode.h"
#include "Dofs/Dactyl.IDof.h"
#include "Elements/Dactyl.IElement.h"
#include "Dactyl.IModel.h"

namespace Dactyl::Model
{
    class LinearTriangularElement : public IElement
    {
        public:
            LinearTriangularElement();

            virtual void calculateStiffnessMatrix() override;
            virtual int getNodesCount() override;

            LinearTriangularElement(LinearTriangularElement const&) = delete;
            void operator=(LinearTriangularElement const&) = delete;

        private:
            std::vector<std::shared_ptr<INode>> _nodes;
            Eigen::Matrix<double, 3, 6> _B;
    };
}

#endif /* _Dactyl.LinearTriangularElement.h_ */
