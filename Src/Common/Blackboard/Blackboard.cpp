/*
 * @Author: xuzihan xuzihan@tongji.edu.cn
 * @Date: 2023-07-19 17:13:43
 * @FilePath: /railbot-v2/Src/Common/Blackboard/Blackboard.cpp
 * @Description:
 *
 */
#include "Blackboard.h"

static thread_local Bb *theInstance = nullptr;

Bb::Bb() {
  if (theInstance != nullptr) return;
  theInstance = this;

  makeR();
}

Bb::~Bb() { theInstance = nullptr; }

Bb &Bb::instance() { return *theInstance; }

void Bb::makeR() {
  _MAKE(FrameInfo);
  _MAKE(JointSensorData);
  _MAKE(BatterySensorData);
  _MAKE(InertialSensorData);
  _MAKE(FSRSensorData);
  _MAKE(TouchSensorData);
  _MAKE(JointRequest);
  _MAKE(LEDRequest);
  _MAKE(RobotStates);
}
