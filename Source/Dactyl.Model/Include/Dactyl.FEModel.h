#pragma once
#ifndef _Dactyl_FEModel_h_
#define _Dactyl_FEModel_h_
#include "Dactyl.ModelAliases.h"
#include <Core>
#include <Dense>
#include <vector>
#include <optional>
#include "Materials/Dactyl.IMaterial.h"
#include "Properties/Dactyl.IProperty.h"
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
            };

            virtual bool loadModel(const std::optional<KData>& kData) override;
            virtual bool saveModel() override;
            virtual void print() override;
            virtual int getNodesCount() override;
       
        private:
            // TODO: Delete
            void print_matrix(Eigen::MatrixX3d m);
            void hello_model();

        public:
            FEModel(FEModel const&) = delete;
            void operator=(FEModel const&) = delete;

        private:
            std::vector<std::shared_ptr<IMaterial>> _materials;
            std::vector< std::shared_ptr<INode>> _nodes;
            std::vector< std::shared_ptr<IProperty>> _properties;
            std::vector< std::shared_ptr<IElement>> _elements;
            std::vector<IDof> _dofs;
    };
}




#endif /* _Dactyl.FEModel.h_ */