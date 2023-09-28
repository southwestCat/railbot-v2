#pragma once

namespace Limbs {
enum Limb {
  neck,
  head,

  firstLeftArmLimb,

  shoulderLeft = firstLeftArmLimb,
  bicepsLeft,
  elbowLeft,
  foreArmLeft,
  wristLeft,

  firstRightArmLimb,

  shoulderRight = firstRightArmLimb,
  bicepsRight,
  elbowRight,
  foreArmRight,
  wristRight,

  firstLeftLegLimb,

  pelvisLeft = firstLeftLegLimb,
  hipLeft,
  thighLeft,
  tibiaLeft,
  ankleLeft,
  footLeft,

  firstRightLegLimb,

  pelvisRight = firstRightLegLimb,
  hipRight,
  thighRight,
  tibiaRight,
  ankleRight,
  footRight,

  torso,
  numOfLimbs
};
}