#pragma once
#ifndef _Dactyl_NodeSet_h_
#define _Dactyl_NodeSet_h_

#include <map>
#include "Nodes/Dactyl.INode.h"

namespace Dactyl::Model
{
    class NodeSet
    {
        private:
            typedef std::map<int, std::shared_ptr<INode>> Container;

        public:
            int size() { return _data.size(); };

            void Add(std::shared_ptr<INode>& node) { _data.insert(std::make_pair(node->GetNodeID(), node)); };

            std::shared_ptr<INode>& GetByID(int id) { return _data[id]; };
            
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

#endif /* _Dactyl.NodeSet.h_ */