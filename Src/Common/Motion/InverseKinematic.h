#pragma once

#include "Common/Math/Pose3f.h"
#include "Common/Motion/ForwardKinematic.h"
#include "Common/RobotParts/Arms.h"
#include "Common/RobotParts/Legs.h"
#include "Representations/Configuration/JointLimits.h"
#include "Representations/Sensing/RobotModel.h"
#include "Representations/SensorData/JointAngles.h"

namespace InverseKinematic {
bool calcLegJoints(const Pose3f &positionLeft, const Pose3f &positionRight,
                   JointAngles &jointAngles,
                   const RobotDimensions &robotDimensions,
                   float ratio = 0.5f) WARN_UNUSED_RESULT;
bool isPosePossible(const Pose3f &footPos, const Pose3f &torso,
                    float HipYawPitch, const RobotDimensions &robotDimension,
                    const JointLimits jointLimits);
bool calcLegJoints(const Pose3f &positionLeft, const Pose3f &positionRight,
                   const Vector2f &bodyRotation, JointAngles &jointAngles,
                   const RobotDimensions &robotDimensions,
                   float ratio = 0.5f) WARN_UNUSED_RESULT;
bool calcLegJoints(const Pose3f &positionLeft, const Pose3f &positionRight,
                   const Quaternionf &bodyRotation, JointAngles &jointAngles,
                   const RobotDimensions &robotDimensions,
                   float ratio = 0.5f) WARN_UNUSED_RESULT;
}  // namespace InverseKinematic
