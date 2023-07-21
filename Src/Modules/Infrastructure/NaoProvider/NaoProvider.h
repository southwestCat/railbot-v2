/*
 * @Author: xuzihan xuzihan@tongji.edu.cn
 * @Date: 2023-07-19 12:51:38
 * @FilePath: /railbot-v2/Src/Modules/Infrastructure/NaoProvider/NaoProvider.h
 * @Description:
 *
 */
#pragma once

#include <array>
#include <memory>

#include "Common/Blackboard/Blackboard.h"
#include "Common/RobotParts/Joints.h"
#include "LoLAMessage.h"

class NaoProvider {
 private:
  _MODIFY(FrameInfo);
  _MODIFY(JointSensorData);

 public:
  NaoProvider();
  ~NaoProvider();

  void exec();

 private:
  int socket;
  enum { LOLAMSGLEN = 896 };
  enum { MAXSENDMSGLEN = 1000 };
  LoLAMessage lolaMsg;
  std::unique_ptr<unsigned char[]> receivedPacket;
  std::unique_ptr<unsigned char[]> packetToSend;
  std::array<uint8_t, LOLAMSGLEN> receivedPacketArr;

 private:
  enum { NJoint = 25 };
  enum { NEar = 10 };
  enum { NChest = 3 };
  enum { NEye = 24 };
  enum { NFoot = 3 };
  enum { NSkull = 12 };
  enum { NSonar = 2 };

  // Data received by LoLA client (This program sent this data to LoLA).
  struct LoLAReceivedData {
    std::array<float, NJoint> Position;
    std::array<float, NJoint> Stiffness; // [0, 1]
    std::array<float, NEar> REar;
    std::array<float, NEar> LEar;
    std::array<float, NChest> Chest;
    std::array<float, NEye> LEye;
    std::array<float, NEye> REye;
    std::array<float, NFoot> LFoot;
    std::array<float, NFoot> RFoot;
    std::array<float, NSkull> Skull;
    std::array<bool, NSonar> Sonar;
  } pack;

  static const int
      jointMappings[Joints::numOfJoints]; /**< Mappings from LoLA's joint
                           indices to request joint indices. */
  unsigned timeWhenPacketReceived = 0;

 private:
  void update();
  void updateJointSensorData();
  void waitLoLA();
  void finishLoLA();
  void receivePacket();
  void sendPacket();
  void disableMotor();
  void disableActuator();
  void disableLED();

 private:
  void sitCrouch();
  void setJoints();
  void setLEDs();
};
