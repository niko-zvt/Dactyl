#pragma once
#ifndef _Dactyl_FEModel_h_
#define _Dactyl_FEModel_h_

#include <Core>
#include <Dense>

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
       
        private:
            void print_matrix(Eigen::MatrixX3d m);
            void hello_model();

        public:
            FEModel(FEModel const&) = delete;
            void operator=(FEModel const&) = delete;
    };
}




#endif /* _Dactyl.FEModel.h_ */