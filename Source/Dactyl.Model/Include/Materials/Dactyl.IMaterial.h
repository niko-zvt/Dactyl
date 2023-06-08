#pragma once
#ifndef _Dactyl_IMaterial_h_
#define _Dactyl_IMaterial_h_

#include <Core>
#include <Dense>

namespace Dactyl::Model
{
    class IMaterial
    {
        public:
            virtual int GetMaterialID() = 0;
            virtual std::string GetMaterialName() = 0;
            virtual Eigen::MatrixXd GetElasticityMatrix() = 0;
        
        private:
            virtual void calclulateElasticityMatrix() = 0;
    };
}

#endif /* _Dactyl.IMaterial.h_ */