/*
 * @Author: xuzihan xuzihan@tongji.edu.cn
 * @Date: 2023-09-20 17:42:12
 * @FilePath: /railbot-v2/Src/Representations/Infrastructure/JointRequest.h
 * @Description: 
 * 
 */
#pragma once

#include "Representations/SensorData/JointAngles.h"

struct JointRequest : JointAngles {
  
};

struct LogJointRequest : JointRequest {};