#pragma once

#include "Common/Math/Pose3f.h"
#include "Common/RobotParts/Arms.h"
#include "Common/RobotParts/Legs.h"
#include "Common/RobotParts/Limbs.h"
#include "Representations/SensorData/JointAngles.h"
#include "Representations/Configuration/RobotDimensions.h"

namespace ForwardKinematic
{
    void calculateArmChain(Arms::Arm arm, const JointAngles& joints, const RobotDimensions& robotDimensions, std::array<Pose3f, Limbs::numOfLimbs>& limbs);
    void calculateLegChain(Legs::Leg leg, const JointAngles& joints, const RobotDimensions& robotDimensions, std::array<Pose3f, Limbs::numOfLimbs>& limbs);
    void calculateHeadChain(const JointAngles& joints, const RobotDimensions& robotDimensions, std::array<Pose3f, Limbs::numOfLimbs>& limbs);
}