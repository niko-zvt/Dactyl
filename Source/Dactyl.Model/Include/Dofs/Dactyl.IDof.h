#pragma once
#ifndef _Dactyl_IDof_h_
#define _Dactyl_IDof_h_

namespace Dactyl::Model
{
    class IDof
    {
        public:
            enum Type
            {
                UX = 1 << 0,
                UY = 1 << 1,
                UXY = UX | UY
            };

            int getNodeID()
            {
                return _nodeID;
            };

            void setNodeID(int id)
            {
                _nodeID = id;
            };

            Type getType()
            {
                return _type;
            };

            void setType(Type type)
            {
                _type = type;
            };

        private:
            int _nodeID;
            Type _type;
    };
}

#endif /* _Dactyl.IDof.h_ */