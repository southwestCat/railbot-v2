/*
 * @Author: xuzihan xuzihan@tongji.edu.cn
 * @Date: 2023-09-27 16:12:39
 * @FilePath: /railbot-v2/Src/Modules/MotionControl/KeyFrameMotionEngine/KeyFrameMotionEngine.cpp
 * /railbot-v2/Src/Modules/MotionControl/KeyFrameMotionEngine/KeyFrameMotionEngine.cpp
 * @Description:
 *
 */
#include "KeyFrameMotionEngine.h"
#include <iostream>

using std::cout;
using std::endl;

void KeyFrameMotionEngine::exec() {
  cout << getRobotStates.state << endl;
}