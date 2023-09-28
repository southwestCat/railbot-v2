#pragma once

#include <array>

#include "Common/Math/Eigen.h"
#include "Common/RobotParts/Limbs.h"

class MassCalibration {
 public:
  MassCalibration();
  struct MassInfo {
    MassInfo() {}
    MassInfo(float mass, Vector3f offset) : mass(mass), offset(offset) {}
    MassInfo(float m, float x, float y, float z) {
      mass = m;
      offset = Vector3f(x, y, z);
    }
    float mass = 0.f;
    Vector3f offset = Vector3f::Zero();
  };

  float totalMass = 0.f;

  std::array<MassInfo, Limbs::numOfLimbs> masses;
};