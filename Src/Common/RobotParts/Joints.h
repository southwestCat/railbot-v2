/*
 * @Author: xuzihan xuzihan@tongji.edu.cn
 * @Date: 2023-07-19 12:58:31
 * @FilePath: /railbot-v2/Src/Common/RobotParts/Joints.h
 * @Description:
 *
 */
#pragma once

namespace Joints {
enum Joint {
  headYaw,
  headPitch,

  firstArmJoint,
  firstLeftArmJoint = firstArmJoint,

  lShoulderPitch = firstLeftArmJoint,
  lShoulderRoll,
  lElbowYaw,
  lElbowRoll,
  lWristYaw,
  lHand,  //< not an Angle, instead %

  firstRightArmJoint,

  rShoulderPitch = firstRightArmJoint,
  rShoulderRoll,
  rElbowYaw,
  rElbowRoll,
  rWristYaw,
  rHand,  //< not an Angle, instead %

  firstLegJoint,
  firstLeftLegJoint = firstLegJoint,

  lHipYawPitch = firstLeftLegJoint,
  lHipRoll,
  lHipPitch,
  lKneePitch,
  lAnklePitch,
  lAnkleRoll,

  firstRightLegJoint,

  rHipYawPitch = firstRightLegJoint,  //< not a joint in the real NAO
  rHipRoll,
  rHipPitch,
  rKneePitch,
  rAnklePitch,
  rAnkleRoll,

  numOfJoints
};
}