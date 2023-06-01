#pragma once
#ifndef _Dactyl_ShellProperty_h_
#define _Dactyl_ShellProperty_h_

#include "Properties/Dactyl.IProperty.h"

namespace Dactyl::Model
{
    class ShellProperty : public IProperty
    {
        public:
            ShellProperty(int pid, int mid);
            virtual int getPropertyID() override;
            virtual int getMaterialID() override;

            ShellProperty(ShellProperty const&) = delete;
            void operator=(ShellProperty const&) = delete;

        private:
            int _propertyID;
            int _materialID;
    };
}

#endif /* _Dactyl.ShellProperty.h_ */
