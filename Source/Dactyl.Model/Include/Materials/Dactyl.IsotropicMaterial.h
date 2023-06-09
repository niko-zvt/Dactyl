#pragma once
#ifndef _Dactyl_IsotropicMaterial_h_
#define _Dactyl_IsotropicMaterial_h_

#include <Core>
#include <Dense>
#include <vector>
#include "Nodes/Dactyl.INode.h"
#include "Materials/Dactyl.IMaterial.h"
#include "Materials/Dactyl.IMaterialCreator.h"
#include "Dactyl.IModel.h"
#include "Dactyl.ModelAliases.h"

namespace Dactyl::Model
{
    class IsotropicMaterial : public IMaterial
    {
        public:
            IsotropicMaterial(int id, double elasticModulus, double poissonRatio, double density, std::string name = "");
            virtual int GetMaterialID() override;
            virtual std::string GetMaterialName();
            virtual Eigen::MatrixXd GetElasticityMatrix() override;
    
            IsotropicMaterial(IsotropicMaterial const &) = delete;
            void operator=(IsotropicMaterial const &) = delete;
    
        private:
            virtual void calclulateElasticityMatrix() override;
    
        private:
            int _materialID = -1;
            double _elasticModulus = 0;
            double _poissonRatio = 0;
            double _density = 0;
            Eigen::Matrix3d _elasticityMatrix;
            std::string _materialName = "";
    };

    class IsotropicMaterialCreator : public IMaterialCreator
    {
        public:
            IsotropicMaterialCreator(const KMaterial& kMaterial);
            IMaterialPtr buildMaterial();
        
        private:
            IMaterialPtr _material;
    };
}

#endif /* _Dactyl.IsotropicMaterial.h_ */
