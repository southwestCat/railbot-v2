/*
 * @Author: xuzihan xuzihan@tongji.edu.cn
 * @Date: 2023-07-19 13:07:26
 * @FilePath: /railbot-v2/Src/Common/Blackboard/Blackboard.h
 * @Description:
 *
 */
#pragma once

#include <memory>

#include "Representations/Infrastructure/FrameInfo.h"
#include "Representations/SensorData/BatterySensorData.h"
#include "Representations/SensorData/FSRSensorData.h"
#include "Representations/SensorData/InertialSensorData.h"
#include "Representations/SensorData/JointSensorData.h"
#include "Representations/SensorData/TouchSensorData.h"
#include "Representations/Infrastructure/JointRequest.h"
#include "Representations/Infrastructure/LEDRequest.h"

#define _USE(R) const R &get##R = *(Bb::instance().get##R.get())
#define _MODIFY(R) R &get##R = *(Bb::instance().get##R.get())

#define _DECLARE(R) std::unique_ptr<R> get##R;
#define _MAKE(R) get##R = std::make_unique<R>();

class Bb {
 public:
  Bb();
  ~Bb();
  static Bb &instance();

 public:
  _DECLARE(FrameInfo);
  _DECLARE(JointSensorData);
  _DECLARE(BatterySensorData);
  _DECLARE(InertialSensorData);
  _DECLARE(FSRSensorData);
  _DECLARE(TouchSensorData);
  _DECLARE(JointRequest);
  _DECLARE(LEDRequest);

 private:
  void makeR();
};
