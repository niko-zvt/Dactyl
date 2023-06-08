#pragma once
#ifndef _Dactyl_FEModel_h_
#define _Dactyl_FEModel_h_
#include "Dactyl.ModelAliases.h"
#include <Sparse>
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
            virtual bool Calculate() override;
            virtual bool LoadMesh(const std::optional<KData>& kData) override;
            virtual bool LoadModel() override;
            virtual bool SaveModel() override;
            virtual void Print() override;
            virtual int GetNodesCount() override;
       
        private:
            bool BuildGlobalEnsemble();
            // TODO: Delete
            void print_matrix(Eigen::MatrixX3d m);
            void hello_model();

        public:
            FEModel(FEModel const&) = delete;
            void operator=(FEModel const&) = delete;

        private:
            std::vector<std::shared_ptr<IMaterial>> _materials;
            std::vector<std::shared_ptr<INode>> _nodes;
            std::vector<std::shared_ptr<IProperty>> _properties;
            std::vector<std::shared_ptr<IElement>> _elements;

            std::unique_ptr<Eigen::SparseMatrix<double>> _globalStiffnessMatrix;
    };
}




#endif /* _Dactyl.FEModel.h_ */