/*
 * @Author: xuzihan xuzihan@tongji.edu.cn
 * @Date: 2023-07-19 18:55:10
 * @FilePath: /railbot-v2/Src/Common/Threads/Motion.cpp
 * @Description:
 *
 */
#include "Motion.h"
#include <iostream>

using std::cout;
using std::endl;

Motion::Motion(BlackboardThread *bbt) : ThreadBase(bbt) {
  naoProvider = std::make_unique<NaoProvider>();
  keyFrameMotionEngine = std::make_unique<KeyFrameMotionEngine>();
  motionCombinator = std::make_unique<MotionCombinator>();
}

void Motion::tick() {
  beforeFrame();
  beforeModules();
  updateModules();
  afterModules();
  afterFrame();
}

void Motion::updateModules() {
  naoProvider->exec();
  keyFrameMotionEngine->exec();
  motionCombinator->exec();
}

void Motion::beforeFrame() {
  *bb->getLEDRequest.get() = bbt->CWMR->theLEDRequest.read();
  *bb->getRobotStates.get() = bbt->CWMR->theRobotStates.read();
}

void Motion::afterFrame() {
  bbt->MWCR->theFrameInfo.write(*bb->getFrameInfo.get());
  bbt->MWCR->theTouchSensorData.write(*bb->getTouchSensorData.get());
  
}

void Motion::beforeModules() {}

void Motion::afterModules() {}