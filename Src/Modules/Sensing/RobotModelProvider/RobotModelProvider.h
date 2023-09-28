/**
 * @file RobotModelProvider.h
 *
 * This file declares a module that provides information about the current state
 * of the robot's limbs.
 *
 * @author <a href="mailto:allli@informatik.uni-bremen.de">Alexander Härtl</a>
 */

#pragma once

#include "Common/Blackboard/Blackboard.h"

/**
 * @class RobotModelProvider
 *
 * A module for computing the current state of the robot's limbs
 */

class RobotModelProvider {
 private:
  _USE(JointAngles);
  _USE(RobotDimensions);
  _USE(MassCalibration);

 private:
  _MODIFY(RobotModel);

 public:
  void exec();

 private:
};