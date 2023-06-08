#pragma once
#ifndef _Dactyl_MaterialSet_h_
#define _Dactyl_MaterialSet_h_

#include <map>
#include "Materials/Dactyl.IMaterial.h"

namespace Dactyl::Model
{
    class MaterialSet
    {
        private:
            typedef std::map<int, std::shared_ptr<IMaterial>> Container;

        public:
            int size() { return _data.size(); };

            void Add(std::shared_ptr<IMaterial>& material) { _data.insert(std::make_pair(material->GetMaterialID(), material)); };

            std::shared_ptr<IMaterial>& GetByID(int id) { return _data[id]; };
            
            // Iterators
            typedef Container::iterator iterator;
            typedef Container::const_iterator const_iterator;

            iterator begin() { return _data.begin(); };
            const_iterator begin() const { return _data.begin(); };

            iterator end() { return _data.end(); };
            const_iterator end() const { return _data.end(); };

        private:
            Container _data;
    };
}

#endif /* _Dactyl.MaterialSet.h_ */