#pragma once
#ifndef _Dactyl_FEModel_h_
#define _Dactyl_FEModel_h_

#include <Core>
#include <Dense>
#include <vector>
#include "Nodes/Dactyl.INode.h"
#include "Dofs/Dactyl.IDof.h"
#include "Elements/Dactyl.IElement.h"
#include "Dactyl.IModel.h"

namespace Dactyl::Model
{
    
    class FEModel : public IModel
    {
        public:
            FEModel()
            {
            }
    
            virtual bool loadModel() override;
            virtual bool saveModel() override;
            virtual void print() override;
            virtual int getNodesCount() override;
       
        private:
            void print_matrix(Eigen::MatrixX3d m);
            void hello_model();

        public:
            FEModel(FEModel const&) = delete;
            void operator=(FEModel const&) = delete;

        private:
            std::vector<std::shared_ptr<IElement>> _elements;
            std::vector<IDof> _dofs;
    };
}




#endif /* _Dactyl.FEModel.h_ */