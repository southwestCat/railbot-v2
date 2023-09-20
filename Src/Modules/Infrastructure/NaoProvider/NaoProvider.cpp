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

using json = nlohmann::json;
using namespace std;

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

NaoProvider::NaoProvider() {
  receivedPacket = make_unique<unsigned char[]>(LOLAMSGLEN);
  packetToSend = make_unique<unsigned char[]>(MAXSENDMSGLEN);

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
    getJointSensorData.angle[i] = lolaMsg.Position[jointMappings[i]];
    getJointSensorData.current[i] = lolaMsg.Current[jointMappings[i]];
    getJointSensorData.temperature[i] = lolaMsg.Temperature[jointMappings[i]];
    getJointSensorData.status[i] =
        lolaMsg.Status[jointMappings[i]] < JointSensorData::unknown
            ? static_cast<JointSensorData::TemperatureStatus>(lolaMsg.Status[jointMappings[i]])
            : JointSensorData::unknown;
  }
}

void NaoProvider::updateBatterySensorData() {
  getBatterySensorData.charge = lolaMsg.Battery[0];
  getBatterySensorData.current = lolaMsg.Battery[1];
  getBatterySensorData.status = lolaMsg.Battery[2];
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
    for (int fsr = 0; fsr < FSRSensors::numOfFSRSensors; fsr++) {
      getFSRSensorData.pressure[leg][fsr] = lolaMsg.FSR[leg * 4 + fsr];
    }
  }
  for (int i = 0; i < FSRSensors::numOfFSRSensors; i++) {
    totalL += getFSRSensorData.pressure[Legs::left][i];
    totalR += getFSRSensorData.pressure[Legs::right][i];
  }
  getFSRSensorData.total[Legs::left] = totalL;
  getFSRSensorData.total[Legs::right] = totalR;
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

  vector<uint8_t> sbuffer = json::to_msgpack(sFrame);

  assert(sbuffer.size() < MAXSENDMSGLEN);
  for (size_t i = 0; i < sbuffer.size(); i++) {
    packetToSend[i] = (unsigned char)sbuffer[i];
  }

  size_t send_stat = send(socket, reinterpret_cast<char *>(packetToSend.get()),
                          sbuffer.size(), 0);
  assert(send_stat == sbuffer.size());
}

void NaoProvider::setJoints() {
  pack.Stiffness.fill(0);

  pack.Stiffness[0] = 0.1;
  pack.Position[0] = 0.0;
}

void NaoProvider::setLEDs() {
  pack.Chest[0] = 0;
  pack.Chest[1] = 1;
  pack.Chest[2] = 0;

  pack.LEar.fill(1);
  pack.REar.fill(1);
  pack.LEye.fill(1);
  pack.REye.fill(1);
  pack.Skull.fill(1);
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

  vector<uint8_t> sbuffer = json::to_msgpack(sFrame);

  assert(sbuffer.size() < MAXSENDMSGLEN);
  for (size_t i = 0; i < sbuffer.size(); i++) {
    packetToSend[i] = (unsigned char)sbuffer[i];
  }

  size_t send_stat = send(socket, reinterpret_cast<char *>(packetToSend.get()),
                          sbuffer.size(), 0);
  assert(send_stat == sbuffer.size());
}
