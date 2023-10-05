/*
 * @Author: xuzihan xuzihan@tongji.edu.cn
 * @Date: 2023-09-22 10:00:13
 * @FilePath: /railbot-v2/Src/Modules/BehaviorControl/LEDHandler/LEDHandler.cpp
 * @Description:
 *
 */
#include "LEDHandler.h"

#include <iostream>

using std::cout;
using std::endl;

void LEDHandler::exec() {
  // Head
  handleHeadLED();
  // Chest
  handleChestLED();
}

void LEDHandler::headLEDOffAll() {
  for (int i = LEDRequest::firstHeadLED; i <= LEDRequest::lastHeadLED; i++) {
    getLEDRequest.ledStates[i] = LEDRequest::off;
  }
}

void LEDHandler::headLEDCharging() {
  headLEDOffAll();
  getLEDRequest.ledStates[HeadLEDLoop] = LEDRequest::on;
  if (getFrameInfo.getTimeSince(HeadLEDLoopTime) > HeadChargingLoopTime) {
    HeadLEDLoopTime = getFrameInfo.time;
    HeadLEDLoop++;
  }
  if (HeadLEDLoop > LEDRequest::lastHeadLED)
    HeadLEDLoop = LEDRequest::firstHeadLED;
}

void LEDHandler::handleHeadLED() {
  if (getBatterySensorData.charging)
    headLEDCharging();
  else
    headLEDOffAll();
}

void LEDHandler::chestLEDOffAll() {
  getLEDRequest.ledStates[LEDRequest::chestBlue] = LEDRequest::off;
  getLEDRequest.ledStates[LEDRequest::chestGreen] = LEDRequest::off;
  getLEDRequest.ledStates[LEDRequest::chestRed] = LEDRequest::off;
}

void LEDHandler::handleChestLED() {
  if (getRobotStates.state == RobotStates::stand ||
      getRobotStates.state == RobotStates::standhigh) {
    getLEDRequest.ledStates[LEDRequest::chestBlue] = LEDRequest::on;
  } else {
    chestLEDOffAll();
  }
}
