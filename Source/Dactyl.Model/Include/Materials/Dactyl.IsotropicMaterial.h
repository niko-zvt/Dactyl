#pragma once
#ifndef _Dactyl_IsotropicMaterial_h_
#define _Dactyl_IsotropicMaterial_h_

#include <Core>
#include <Dense>
#include <vector>
#include "Nodes/Dactyl.INode.h"
#include "Dofs/Dactyl.IDof.h"
#include "Dactyl.IModel.h"

namespace Dactyl::Model
{
    class IsotropicMaterial : public IMaterial
    {
        public:
            IsotropicMaterial(int id, double E, double nu, std::string name = "");
            virtual int getMaterialID() override;
            virtual std::string getMaterialName();
            virtual Eigen::MatrixXd getElasticityMatrix() override;

            IsotropicMaterial(IsotropicMaterial const&) = delete;
            void operator=(IsotropicMaterial const&) = delete;

        private:
            virtual void calclulateElasticityMatrix() override;

        private:
            int _materialID = -1;
            double _E = 0;
            double _nu = 0;
            Eigen::Matrix3d _elasticityMatrix;
            std::string _materialName = "";
    };
}

#endif /* _Dactyl.IsotropicMaterial.h_ */
