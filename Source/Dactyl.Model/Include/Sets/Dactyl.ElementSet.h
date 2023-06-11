#pragma once
#ifndef _Dactyl_ElementSet_h_
#define _Dactyl_ElementSet_h_

#include <map>
#include "Elements/Dactyl.IElement.h"

namespace Dactyl::Model
{
    class ElementSet
    {
        private:
            typedef std::map<int, std::shared_ptr<IElement>> Container;

        public:
            int size() { return _data.size(); };

            void Add(std::shared_ptr<IElement>& node) { _data.insert(std::make_pair(node->GetElementID(), node)); };

            std::shared_ptr<IElement>& GetByID(int id) { return _data[id]; };
            
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

#endif /* _Dactyl.ElementSet.h_ */