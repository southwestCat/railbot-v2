#include "JointAnglesProvider.h"

void JointAnglesProvider::exec() {
  getJointAngles = getJointSensorData;
}