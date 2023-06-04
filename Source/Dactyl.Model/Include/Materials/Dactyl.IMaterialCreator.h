#pragma once
#ifndef _Dactyl_IMaterialCreator_h_
#define _Dactyl_IMaterialCreator_h_

#include "Materials/Dactyl.IMaterial.h"
#include "Dactyl.KData.h"
#include "Dactyl.ModelAliases.h"

namespace Dactyl::Model
{
    class IMaterialCreator
    {
        protected:
            IMaterialCreator(const KMaterial& kMaterial) {};
        
        public:
            virtual IMaterialPtr buildMaterial() = 0;
            static IMaterialCreator* getMaterialCreator(const KMaterial& kMaterial);
    };
}

#endif /* _Dactyl.IMaterialCreator.h_ */