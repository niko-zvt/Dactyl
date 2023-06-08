#pragma once
#ifndef _Dactyl_PropertySet_h_
#define _Dactyl_PropertySet_h_

#include <map>
#include "Properties/Dactyl.IProperty.h"

namespace Dactyl::Model
{
    class PropertySet
    {
        private:
            typedef std::map<int, std::shared_ptr<IProperty>> Container;

        public:
            int size() { return _data.size(); };

            void Add(std::shared_ptr<IProperty>& property) { _data.insert(std::make_pair(property->GetPropertyID(), property)); };

            std::shared_ptr<IProperty>& GetByID(int id) { return _data[id]; };
            
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

#endif /* _Dactyl.PropertySet.h_ */