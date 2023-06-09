#pragma once
#ifndef _Dactyl_IModel_h_
#define _Dactyl_IModel_h_

#include <any>
#include <optional>
#include "Dactyl.KData.h"
#include "Nodes/Dactyl.INode.h"

namespace Dactyl::Model
{
    class INode;
    class IProperty;
    class IMaterial;

    class IModel
    {
        public:
            virtual bool Calculate() = 0;
            virtual bool LoadModel() = 0;
            virtual bool SaveModel() = 0;
            virtual bool LoadMesh(const std::optional<KData>& kData) = 0;
            virtual void Print() = 0;

            virtual bool SetConstraintsByCoords(std::any xCoord, std::any yCoord, ConstraintType type, double tolerance) = 0;
            virtual bool SetDistributedForceByCoords(std::any xCoord, std::any yCoord, double Fx, double Fy, double tolerance) = 0;

            virtual int GetNodesCount() = 0;
            virtual std::shared_ptr<INode> GetNodeByID(int id) = 0;
            virtual std::shared_ptr<IProperty> GetPropertyByID(int id) = 0;
            virtual std::shared_ptr<IMaterial> GetMaterialByID(int id) = 0;
    };
}

#endif /* _Dactyl.IModel.h_ */