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
    
            virtual bool loadModel() override
            {
                return false;
            }
    
            virtual bool saveModel() override
            {
                return false;
            }

            virtual void print() override
            {
                hello_model();
            }
       
            void print_matrix(Eigen::MatrixX3d m);
            void hello_model();

            FEModel(FEModel const&) = delete;
            void operator=(FEModel const&) = delete;
    };
}




#endif /* _Dactyl.FEModel.h_ */