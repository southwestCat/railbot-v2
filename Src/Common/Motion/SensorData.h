/*
 * @Author: xuzihan xuzihan@tongji.edu.cn
 * @Date: 2023-07-21 13:19:48
 * @FilePath: /railbot-v2/Src/Common/Motion/SensorData.h
 * @Description:
 *
 */
#pragma once

namespace SensorData {
constexpr float off = 10000.f;  /**< Special value that indicates the sensor is tuned off. */
constexpr float ignore = 20000.f;  /**< Special value that indicates the sensor uses the previous value. */
}  // namespace SensorData