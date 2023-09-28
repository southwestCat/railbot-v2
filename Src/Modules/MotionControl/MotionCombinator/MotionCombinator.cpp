/*
 * @Author: xuzihan xuzihan@tongji.edu.cn
 * @Date: 2023-09-27 16:17:25
 * @FilePath: /railbot-v2/Src/Modules/MotionControl/MotionCombinator/MotionCombinator.cpp
 * /railbot-v2/Src/Modules/MotionControl/MotionCombinator/MotionCombinator.cpp
 * @Description:
 *
 */
#include "MotionCombinator.h"

#include <iostream>

#include "Common/Motion/ForwardKinematic.h"

using std::cout;
using std::endl;

void MotionCombinator::exec() {
  RobotDimensions robotDimensions;
  JointAngles jointAngles;
  std::array<Pose3f, Limbs::numOfLimbs> limbs;
  ForwardKinematic::calculateLegChain(Legs::left, jointAngles, robotDimensions, limbs);
  ForwardKinematic::calculateLegChain(Legs::right, jointAngles, robotDimensions, limbs);
  
  Pose3f soleL = limbs[Limbs::footLeft] + Vector3f(0.f, 0.f, -robotDimensions.footHeight);
  Pose3f soleR = limbs[Limbs::footRight] + Vector3f(0.f, 0.f, -robotDimensions.footHeight);

  cout << "left:\n";
  cout << soleL.translation.transpose() << endl;
  cout << "right:\n";
  cout << soleR.translation.transpose() << endl;
}