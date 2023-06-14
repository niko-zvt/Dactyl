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
#include "Elements/Dactyl.IElement.h"
#include "Dactyl.IModel.h"
#include "Sets/Dactyl.NodeSet.h"
#include "Sets/Dactyl.MaterialSet.h"
#include "Sets/Dactyl.PropertySet.h"
#include "Sets/Dactyl.ElementSet.h"

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

            virtual bool SetConstraintsByCoords(std::any xCoord, std::any yCoord, ConstraintType type, double tolerance) override;
            virtual bool SetDistributedForceByCoords(std::any xCoord, std::any yCoord, double Fx, double Fy, double tolerance) override;

            virtual int GetNodesCount() override;
            virtual std::shared_ptr<INode> GetNodeByID(int id) override;
            virtual std::shared_ptr<IProperty> GetPropertyByID(int id) override;
            virtual std::shared_ptr<IMaterial> GetMaterialByID(int id) override;
            virtual Eigen::VectorXd GetGlobalDisplacementVector() override;
        
        private:
            bool LinkParents();
            bool BuildGlobalEnsemble();
            bool ApplyConstraints();
            bool SolveLinearSystem();
            Eigen::VectorXd BuildExternalForcesVector();
            void SetConstraintsToGlobalStiffnessMatrix(Eigen::SparseMatrix<double>::InnerIterator& it, int globalID);
            bool CopyDisplacementsToNodes(const Eigen::VectorXd& displacements);
            bool BuildStrainsAndStressesForAllElements();

        public:
            FEModel(FEModel const&) = delete;
            void operator=(FEModel const&) = delete;

        private:
            NodeSet _nodes;
            MaterialSet _materials;
            PropertySet _properties;
            ElementSet _elements;

            std::unique_ptr<Eigen::SparseMatrix<double>> _globalStiffnessMatrix;
            std::unique_ptr<Eigen::VectorXd> _globalForceVector;
            std::unique_ptr<Eigen::VectorXd> _globalDisplacementVector;
            NodeSet _nodesWithConstraints;
    };
}




#endif /* _Dactyl.FEModel.h_ */