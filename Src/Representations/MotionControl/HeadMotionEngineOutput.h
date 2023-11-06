#pragma once

#include "Representations/Infrastructure/JointRequest.h"

struct HeadMotionEngineOutput {
  void reset() {
    active = false;
  }
  bool active = false;
  JointRequest j;
};