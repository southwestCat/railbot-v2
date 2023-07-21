/*
 * @Author: xuzihan xuzihan@tongji.edu.cn
 * @Date: 2023-07-21 09:59:12
 * @FilePath: /railbot-v2/Src/Common/Math/Constants.h
 * @Description:
 *
 */
#pragma once

namespace Constants {

  // https://en.wikipedia.org/wiki/Gravitational_acceleration
  constexpr float g = 9.80665f; // conventional standard value
  constexpr float g1000 = 1000.f * g;
 
  //-> Value copy from cmath
  //-> More accuracy value can refer to std::numbers::pi_v<long double>
  constexpr float e = 2.7182818284590452354f;	/* e */
  constexpr float pi = 3.14159265358979323846f;	/* pi */
  constexpr float pi2 = 2.f * pi;

  //-> Measured from LoLA's communication frequency
  // Mostly 12ms, occasionally 13ms.
  constexpr float motionCycleTime = 0.012f; // second
}

using Constants::pi;
using Constants::pi2;