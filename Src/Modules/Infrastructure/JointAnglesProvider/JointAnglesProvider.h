#pragma once

#include "Common/Blackboard/Blackboard.h"

class JointAnglesProvider {
 private:
  _USE(JointSensorData);

 private:
  _MODIFY(JointAngles);

 public:
  void exec();
};