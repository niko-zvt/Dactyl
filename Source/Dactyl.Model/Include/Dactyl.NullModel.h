#pragma once
#ifndef _Dactyl_NullModel_h_
#define _Dactyl_NullModel_h_

#include "Nodes/Dactyl.INode.h"
#include "Dactyl.IModel.h"
#include "Dactyl.ModelAliases.h"

namespace Dactyl::Model
{
    class NullModel : public IModel
    {
        public:
            NullModel()
            {
            };

            virtual bool Calculate() override
            {
                return false;
            };

            virtual bool LoadMesh(const std::optional<KData>& kData) override
            {
                return false;
            };

            virtual bool LoadModel() override
            {
                return false;
            };

            virtual bool SaveModel() override
            {
                return false;
            };

            virtual void Print() override
            {
            };

            virtual bool SetConstraintsByCoords(std::any xCoord, std::any yCoord, ConstraintType type, double tolerance) override
            {
                return false;
            };

            virtual bool SetDistributedForceByCoords(std::any xCoord, std::any yCoord, double Fx, double Fy, double tolerance) override
            {
                return false;
            };

            virtual int GetNodesCount() override
            {
                return -1;
            };
       
            virtual std::shared_ptr<INode> GetNodeByID(int id) override
            {
                return nullptr;
            };

            virtual std::shared_ptr<IMaterial> GetMaterialByID(int id) override
            {
                return nullptr;
            };

            virtual std::shared_ptr<IProperty> GetPropertyByID(int id) override
            {
                return nullptr;
            };

            NullModel(NullModel const&) = delete;
            void operator=(NullModel const&) = delete;
    };
}

#endif /* _Dactyl.NullModel.h_ */
