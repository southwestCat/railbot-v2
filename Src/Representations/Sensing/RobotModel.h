#pragma once

#include "Common/Math/Eigen.h"
#include "Common/Math/Pose3f.h"
#include "Common/RobotParts/Limbs.h"
#include "Representations/Configuration/MassCalibration.h"
#include "Representations/Configuration/RobotDimensions.h"
#include "Representations/SensorData/JointAngles.h"

class RobotModel {
 public:
  RobotModel() = default;

  RobotModel(const JointAngles& jointAngles,
             const RobotDimensions& robotDimensions,
             const MassCalibration& massCalibration);

  void setJointData(const JointAngles& jointAngles,
                    const RobotDimensions& robotDimensions,
                    const MassCalibration& massCalibration);

  void updateCenterOfMass(const MassCalibration& massCalibration);

  std::array<Pose3f, Limbs::numOfLimbs> limbs;
  Pose3f soleLeft;
  Pose3f soleRight;
  Vector3f centerOfMass = Vector3f::Zero();
};