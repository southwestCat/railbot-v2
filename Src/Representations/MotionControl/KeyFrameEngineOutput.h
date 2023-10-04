#pragma once

#include "Representations/Infrastructure/JointRequest.h"

struct KeyFrameEngineOutput {
  void reset() {
    activate = false;
    standMotionDone = false;
  }
  bool activate = false;
  bool standMotionDone = false;
  JointRequest j;
};