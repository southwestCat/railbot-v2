#pragma once

#include "Representations/Infrastructure/JointRequest.h"

struct KeyFrameEngineOutput {
  void reset() {
    activate = false;
    standMotionDone = false;
    standHighMotionDone = false;
  }
  bool activate = false;
  bool standMotionDone = false;
  bool standHighMotionDone = false;
  JointRequest j;
};