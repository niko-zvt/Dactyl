#pragma once
#ifndef _Dactyl_Node_h_
#define _Dactyl_Node_h_

#include <Core>
#include <Dense>
#include <vector>
#include "Nodes/Dactyl.INode.h"
#include "Dofs/Dactyl.IDof.h"
#include "Dactyl.IModel.h"

namespace Dactyl::Model
{
    class Node : public INode
    {
        public:
            Node(int id, Eigen::Vector<double, 3> coords)
            {
                _id = id;
                _coords = coords;
            }

            virtual int getNodeID() override
            {
                return _nodeID;
            };

            virtual void setNodeID(int id) override
            {
                _nodeID = id;
            }

            virtual Eigen::Vector<double, 3> getCoords() override
            {
                return _coords;
            }

            virtual void setNodeCoords(Eigen::Vector<double, 3> coords) override
            {
                _coords = coords;
            }

            Node(Node const&) = delete;
            void operator=(Node const&) = delete;

        private:
            int _nodeID;
            Eigen::Vector<double, 3> _coords;
    };
}

#endif /* _Dactyl.Node.h_ */
