#pragma once
#ifndef _Dactyl_LinearTriangularElement_h_
#define _Dactyl_LinearTriangularElement_h_

#include <Core>
#include <Dense>
#include <vector>
#include "Nodes/Dactyl.Node.h"
#include "Nodes/Dactyl.INode.h"
#include "Dofs/Dactyl.IDof.h"
#include "Elements/Dactyl.IElement.h"
#include "Elements/Dactyl.IElementCreator.h"
#include "Dactyl.IModel.h"
#include <Sparse>

namespace Dactyl::Model
{
    class LinearTriangularElement : public IElement
    {
        public:
            LinearTriangularElement(int eid, int pid, const std::vector<int> _nodesIDs);

            virtual int GetElementID() override;
            virtual int GetPropertyID() override;
            virtual void CalculateStiffnessMatrix(std::vector<Eigen::Triplet<double>>& localStiffnessMatrixes) override;
            virtual int GetNodesCount() override;

            LinearTriangularElement(LinearTriangularElement const&) = delete;
            void operator=(LinearTriangularElement const&) = delete;

        private:
            int _elementID = -1;
            int _propertyID = -1;
            std::vector<int> _nodesIDs;
            Eigen::Matrix<double, 3, 6> _B;
    };

    class LinearTriangularCreator : public IElementCreator
    {
        public:
            LinearTriangularCreator(const KElement& kElement);
            IElementPtr buildElement();
        
        private:
            IElementPtr _element;
    };
}

#endif /* _Dactyl.LinearTriangularElement.h_ */
