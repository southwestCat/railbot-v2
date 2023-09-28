#include "RobotModelProvider.h"

void RobotModelProvider::exec() {
 getRobotModel.setJointData(getJointAngles, getRobotDimensions, getMassCalibration); 
}