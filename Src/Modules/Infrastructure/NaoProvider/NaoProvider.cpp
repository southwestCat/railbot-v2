/*
 * @Author: xuzihan xuzihan@tongji.edu.cn
 * @Date: 2023-07-19 12:54:23
 * @FilePath: /railbot-v2/Src/Modules/Infrastructure/NaoProvider/NaoProvider.cpp
 * @Description:
 *
 */
#include "NaoProvider.h"

#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#include <iostream>

#include "Common/Time/Time.h"

using std::cout;
using std::endl;
using json = nlohmann::json;

// Joint order in LoLA data
enum JointOrdLoLA {
  HeadYaw,
  HeadPitch,
  LShoulderPitch,
  LShoulderRoll,
  LElbowYaw,
  LElbowRoll,
  LWristYaw,
  LHipYawPitch,
  RHipYawPitch = LHipYawPitch,
  LHipRoll,
  LHipPitch,
  LKneePitch,
  LAnklePitch,
  LAnkleRoll,
  RHipRoll,
  RHipPitch,
  RKneePitch,
  RAnklePitch,
  RAnkleRoll,
  RShoulderPitch,
  RShoulderRoll,
  RElbowYaw,
  RElbowRoll,
  RWristYaw,
  LHand,
  RHand
};

enum TouchOrdLoLA {
  Chest,
  HeadFront,
  HeadMiddle,
  HeadRear,
  LFootLeft,
  LFootRight,
  LHandBack,
  LHandLeft,
  LHandRight,
  RFootLeft,
  RFootRight,
  RHandBack,
  RHandLeft,
  RHandRight
};

const int NaoProvider::jointMappings[Joints::numOfJoints] = {
    HeadYaw,      HeadPitch,  LShoulderPitch, LShoulderRoll,  LElbowYaw,
    LElbowRoll,   LWristYaw,  LHand,          RShoulderPitch, RShoulderRoll,
    RElbowYaw,    RElbowRoll, RWristYaw,      RHand,          LHipYawPitch,
    LHipRoll,     LHipPitch,  LKneePitch,     LAnklePitch,    LAnkleRoll,
    RHipYawPitch, RHipRoll,   RHipPitch,      RKneePitch,     RAnklePitch,
    RAnkleRoll};

const int NaoProvider::touchMappings[TouchSensorData::numOfTouchs] = {
    Chest,      HeadFront, HeadMiddle, HeadRear,   LFootLeft,
    LFootRight, LHandBack, LHandLeft,  LHandRight, RFootLeft,
    RFootRight, RHandBack, RHandLeft,  RHandRight};

const int NaoProvider::skullMappings[] = {
  LEDRequest::headFrontLeft1,
  LEDRequest::headFrontLeft0,
  LEDRequest::headMiddleLeft0,
  LEDRequest::headRearLeft0,
  LEDRequest::headRearLeft1,
  LEDRequest::headRearLeft2,
  LEDRequest::headRearRight2,
  LEDRequest::headRearRight1,
  LEDRequest::headRearRight0,
  LEDRequest::headMiddleRight0,
  LEDRequest::headFrontRight0,
  LEDRequest::headFrontRight1,
};

NaoProvider::NaoProvider() {
  receivedPacket = std::make_unique<unsigned char[]>(LOLAMSGLEN);
  packetToSend = std::make_unique<unsigned char[]>(MAXSENDMSGLEN);

  socket = ::socket(AF_UNIX, SOCK_STREAM, 0);
  sockaddr_un address;
  address.sun_family = AF_UNIX;
  strcpy(address.sun_path, "/tmp/robocup");

  connect(socket, reinterpret_cast<sockaddr *>(&address), sizeof(address));
}

NaoProvider::~NaoProvider() {
  printf("~NaoProvider.\n");
  disableActuator();
  close(socket);
}

void NaoProvider::exec() {
  waitLoLA();
  update();
  finishLoLA();
}

void NaoProvider::update() {
  getFrameInfo.time = timeWhenPacketReceived;
  updateJointSensorData();
  updateBatterySensorData();
  updateInertialSensorData();
  updateFSRSensorData();
  updateTouchSensorData();
}

void NaoProvider::updateJointSensorData() {
  for (int i = 0; i < Joints::numOfJoints; i++) {
    getJointSensorData.angles[i] = lolaMsg.Position[jointMappings[i]];
    getJointSensorData.current[i] = lolaMsg.Current[jointMappings[i]];
    getJointSensorData.temperature[i] = lolaMsg.Temperature[jointMappings[i]];
    getJointSensorData.status[i] =
        lolaMsg.Status[jointMappings[i]] < JointSensorData::unknown
            ? static_cast<JointSensorData::TemperatureStatus>(
                  lolaMsg.Status[jointMappings[i]])
            : JointSensorData::unknown;
  }
}

void NaoProvider::updateBatterySensorData() {
  getBatterySensorData.level = lolaMsg.Battery[0];
  getBatterySensorData.status = lolaMsg.Battery[1];
  getBatterySensorData.charging = (static_cast<short>(lolaMsg.Battery[1]) & 0x80) != 0;
  getBatterySensorData.current = lolaMsg.Battery[2];
  getBatterySensorData.temperature = lolaMsg.Battery[3];
  
}

void NaoProvider::updateInertialSensorData() {
  getInertialSensorData.acc << lolaMsg.Accelerometer[0],
      lolaMsg.Accelerometer[1], lolaMsg.Accelerometer[2];
  getInertialSensorData.gyro << lolaMsg.Gyroscope[0], lolaMsg.Gyroscope[1],
      lolaMsg.Gyroscope[2];
  getInertialSensorData.angle << lolaMsg.Angles[0], lolaMsg.Angles[1];
}

void NaoProvider::updateFSRSensorData() {
  float totalL = 0.f;
  float totalR = 0.f;
  for (int leg = 0; leg < Legs::numOfLegs; leg++) {
    for (int fsr = 0; fsr < FsrSensors::numOfFsrSensors; fsr++) {
      getFsrSensorData.pressure[leg][fsr] = lolaMsg.FSR[leg * 4 + fsr];
    }
  }
  for (int i = 0; i < FsrSensors::numOfFsrSensors; i++) {
    totalL += getFsrSensorData.pressure[Legs::left][i];
    totalR += getFsrSensorData.pressure[Legs::right][i];
  }
  getFsrSensorData.total[Legs::left] = totalL;
  getFsrSensorData.total[Legs::right] = totalR;
}

void NaoProvider::updateTouchSensorData() {
  for (int i = 0; i < TouchSensorData::numOfTouchs; i++) {
    getTouchSensorData.pressed[i] = lolaMsg.Touch[touchMappings[i]] > 0.5f;
  }
}

void NaoProvider::waitLoLA() { receivePacket(); }

void NaoProvider::finishLoLA() { sendPacket(); }

void NaoProvider::receivePacket() {
  const size_t bytesRead = recv(
      socket, reinterpret_cast<char *>(receivedPacket.get()), LOLAMSGLEN, 0);
  assert(bytesRead == LOLAMSGLEN);

  if (bytesRead < 0) {
    std::cerr << "Could not receive packet from NAO.\n";
    return;
  }

  for (size_t i = 0; i < LOLAMSGLEN; i++) {
    receivedPacketArr[i] = static_cast<uint8_t>(receivedPacket[i]);
  }
  json j = json::from_msgpack(receivedPacketArr);
  lolaMsg = j.get<LoLAMessage>();

  timeWhenPacketReceived =
      std::max(Time::getSystemTime(), timeWhenPacketReceived + 1);
}

void NaoProvider::sendPacket() {
  json sFrame;

  setJoints();
  setLEDs();

  sFrame["Position"] = pack.Position;
  sFrame["Stiffness"] = pack.Stiffness;
  sFrame["REar"] = pack.REar;
  sFrame["LEar"] = pack.LEar;
  sFrame["Chest"] = pack.Chest;
  sFrame["LEye"] = pack.LEye;
  sFrame["REye"] = pack.REye;
  sFrame["LFoot"] = pack.LFoot;
  sFrame["RFoot"] = pack.RFoot;
  sFrame["Skull"] = pack.Skull;

  std::vector<uint8_t> sbuffer = json::to_msgpack(sFrame);

  assert(sbuffer.size() < MAXSENDMSGLEN);
  for (size_t i = 0; i < sbuffer.size(); i++) {
    packetToSend[i] = (unsigned char)sbuffer[i];
  }

  size_t send_stat = send(socket, reinterpret_cast<char *>(packetToSend.get()),
                          sbuffer.size(), 0);
  assert(send_stat == sbuffer.size());
}

void NaoProvider::setJoints() {
  for (int i = 0; i < Joints::numOfJoints; i++) {
    if (getJointRequest.angles[i] == JointSensorData::ignore) continue;
    if (getJointRequest.angles[i] == JointSensorData::off) {
      pack.Stiffness[jointMappings[i]] = 0.0;
    } else {
      // pack.Position[jointMappings[i]] = getJointRequest.angles[i];
      pack.Position[jointMappings[i]] = getJointLimits.limits[i].clamped(getJointRequest.angles[i]);
      float stiff = static_cast<float>(getJointRequest.stiffnessData.stiffnesses[i]) / 100.0;
      assert(stiff >= 0.0 && stiff <= 1.0);
      pack.Stiffness[jointMappings[i]] = stiff;
    }
  }
}

void NaoProvider::setLEDs() {
  bool blink = false;
  bool fastblink = false;

  if (getFrameInfo.getTimeSince(LoopLEDBlink) > LEDBlinkTime) {
    LoopLEDBlink = getFrameInfo.time;
    blink = true;
  }
  if (getFrameInfo.getTimeSince(LoopLEDFastBLink) > LEDFastBlinkTime) {
    LoopLEDFastBLink = getFrameInfo.time;
    fastblink = true;
  }

  pack.Chest[0] = getLEDRequest.ledStates[LEDRequest::chestRed];    // red
  pack.Chest[1] = getLEDRequest.ledStates[LEDRequest::chestGreen];  // green
  pack.Chest[2] = getLEDRequest.ledStates[LEDRequest::chestBlue];   // blue

  // Skull
  for (int i = 0; i < NSkull; i++) {
    pack.Skull[i] = getLEDRequest.ledStates[skullMappings[i]] == LEDRequest::on ? 1.0 : 
      getLEDRequest.ledStates[skullMappings[i]] == LEDRequest::blinking && blink ? 1.0 : 
      getLEDRequest.ledStates[skullMappings[i]] == LEDRequest::fastBlinking && fastblink ? 1.0 : 0.0;
  }
}

void NaoProvider::disableMotor() { pack.Stiffness.fill(0); }

void NaoProvider::disableLED() {
  pack.REar.fill(0);
  pack.LEar.fill(0);
  pack.Chest.fill(0);
  pack.LEye.fill(0);
  pack.REye.fill(0);
  pack.LFoot.fill(0);
  pack.RFoot.fill(0);
  pack.Skull.fill(0);
}

void NaoProvider::disableActuator() {
  disableMotor();
  disableLED();

  json sFrame;

  sFrame["Position"] = pack.Position;
  sFrame["Stiffness"] = pack.Stiffness;
  sFrame["REar"] = pack.REar;
  sFrame["LEar"] = pack.LEar;
  sFrame["Chest"] = pack.Chest;
  sFrame["LEye"] = pack.LEye;
  sFrame["REye"] = pack.REye;
  sFrame["LFoot"] = pack.LFoot;
  sFrame["RFoot"] = pack.RFoot;
  sFrame["Skull"] = pack.Skull;

  std::vector<uint8_t> sbuffer = json::to_msgpack(sFrame);

  assert(sbuffer.size() < MAXSENDMSGLEN);
  for (size_t i = 0; i < sbuffer.size(); i++) {
    packetToSend[i] = (unsigned char)sbuffer[i];
  }

  size_t send_stat = send(socket, reinterpret_cast<char *>(packetToSend.get()),
                          sbuffer.size(), 0);
  assert(send_stat == sbuffer.size());
}
