#pragma once
#ifndef _Dactyl_FEModel_h_
#define _Dactyl_FEModel_h_
#include <Sparse>
#include <Core>
#include <Dense>
#include <vector>
#include <optional>
#include "Dactyl.ModelAliases.h"
#include "Materials/Dactyl.IMaterial.h"
#include "Properties/Dactyl.IProperty.h"
#include "Nodes/Dactyl.INode.h"
#include "Dofs/Dactyl.IDof.h"
#include "Elements/Dactyl.IElement.h"
#include "Dactyl.IModel.h"
#include "Sets/Dactyl.NodeSet.h"
#include "Sets/Dactyl.MaterialSet.h"
#include "Sets/Dactyl.PropertySet.h"


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

            virtual std::shared_ptr<INode> GetNodeByID(int id) override;
            virtual std::shared_ptr<IProperty> GetPropertyByID(int id) override;
            virtual std::shared_ptr<IMaterial> GetMaterialByID(int id) override;
       
        private:
            bool BuildGlobalEnsemble();
            // TODO: Delete
            void print_matrix(Eigen::MatrixX3d m);
            void hello_model();

        public:
            FEModel(FEModel const&) = delete;
            void operator=(FEModel const&) = delete;

        private:
            NodeSet _nodes;
            MaterialSet _materials;
            PropertySet _properties;
            std::vector<std::shared_ptr<IElement>> _elements;

            std::unique_ptr<Eigen::SparseMatrix<double>> _globalStiffnessMatrix;
    };
}




#endif /* _Dactyl.FEModel.h_ */