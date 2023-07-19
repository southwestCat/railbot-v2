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
  enum { NJoints = Joints::numOfJoints - 1 };

  std::array<float, NJoints> position;
  std::array<float, NJoints> stiffness;
  std::array<float, 3> chest;
  static const Joints::Joint
      jointMappings[Joints::numOfJoints -
                    1]; /**< Mappings from LoLA's joint indices to request
                           joint indices. */
  unsigned timeWhenPacketReceived = 0;

 private:
  void update();
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
