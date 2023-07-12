#pragma once
#ifndef _Dactyl_IElement_h_
#define _Dactyl_IElement_h_

#include "Nodes/Dactyl.INode.h"
#include <Eigen/Sparse>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <vector>

namespace Dactyl::Model
{
    class IElement
    {
        public:
            virtual int GetElementID() = 0;
            virtual int GetPropertyID() = 0;
            virtual int GetNodesCount() = 0;
            virtual std::vector<int> GetNodeIDs() = 0;
            virtual void CalculateLocalStiffnessMatrix(std::vector<Eigen::Triplet<double>>& subEnsembles) = 0;
            virtual void CalculateLocalStrainAndStressMatrix() = 0;
            virtual Eigen::Matrix3d GetStrainMatrix() = 0;
            virtual Eigen::Matrix3d GetStressMatrix() = 0;
            virtual Eigen::Vector3d GetCoordCenter() = 0;
            virtual double GetVonMisesStress() = 0;
    };
}

#endif /* _Dactyl.IElement.h_ */