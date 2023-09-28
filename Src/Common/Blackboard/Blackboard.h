/*
 * @Author: xuzihan xuzihan@tongji.edu.cn
 * @Date: 2023-07-19 13:07:26
 * @FilePath: /railbot-v2/Src/Common/Blackboard/Blackboard.h
 * @Description:
 *
 */
#pragma once

#include <memory>

#include "Representations/Configuration/MassCalibration.h"
#include "Representations/Configuration/RobotDimensions.h"
#include "Representations/Infrastructure/FrameInfo.h"
#include "Representations/Infrastructure/JointRequest.h"
#include "Representations/Infrastructure/LEDRequest.h"
#include "Representations/Infrastructure/RobotStates.h"
#include "Representations/MotionControl/KeyFrameEngineOutput.h"
#include "Representations/Sensing/RobotModel.h"
#include "Representations/SensorData/BatterySensorData.h"
#include "Representations/SensorData/FsrSensorData.h"
#include "Representations/SensorData/InertialSensorData.h"
#include "Representations/SensorData/JointAngles.h"
#include "Representations/SensorData/JointSensorData.h"
#include "Representations/SensorData/TouchSensorData.h"

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
  _DECLARE(FsrSensorData);
  _DECLARE(TouchSensorData);
  _DECLARE(JointRequest);
  _DECLARE(LEDRequest);
  _DECLARE(RobotStates);
  _DECLARE(KeyFrameEngineOutput);
  _DECLARE(LogJointRequest);
  _DECLARE(RobotDimensions);
  _DECLARE(MassCalibration);
  _DECLARE(JointAngles);
  _DECLARE(RobotModel);

 private:
  void makeR();
};
