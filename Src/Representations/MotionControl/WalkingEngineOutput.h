#include "Representations/Infrastructure/JointRequest.h"

struct WalkingEngineOutput {
  void reset() {
    active = false;
    inWalking = false;
  }
  JointRequest j;
  bool active;
  bool inWalking;
};