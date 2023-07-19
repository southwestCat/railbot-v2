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

const Joints::Joint NaoProvider::jointMappings[Joints::numOfJoints - 1] = {
    Joints::headYaw,        Joints::headPitch,

    Joints::lShoulderPitch, Joints::lShoulderRoll, Joints::lElbowYaw,
    Joints::lElbowRoll,     Joints::lWristYaw,

    Joints::lHipYawPitch,   Joints::lHipRoll,      Joints::lHipPitch,
    Joints::lKneePitch,     Joints::lAnklePitch,   Joints::lAnkleRoll,

    Joints::rHipRoll,       Joints::rHipPitch,     Joints::rKneePitch,
    Joints::rAnklePitch,    Joints::rAnkleRoll,

    Joints::rShoulderPitch, Joints::rShoulderRoll, Joints::rElbowYaw,
    Joints::rElbowRoll,     Joints::rWristYaw,

    Joints::lHand,          Joints::rHand};

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

  sFrame["Position"] = position;
  sFrame["Stiffness"] = stiffness;
  sFrame["Chest"] = chest;

  vector<uint8_t> sbuffer = json::to_msgpack(sFrame);

  assert(sbuffer.size() < MAXSENDMSGLEN);
  for (size_t i = 0; i < sbuffer.size(); i++) {
    packetToSend[i] = (unsigned char)sbuffer[i];
  }

  size_t send_stat = send(socket, reinterpret_cast<char *>(packetToSend.get()),
                          sbuffer.size(), 0);
  assert(send_stat == sbuffer.size());
}

void NaoProvider::setJoints() { stiffness.fill(0); }

void NaoProvider::setLEDs() {
  chest[0] = 0;
  chest[1] = 1;
  chest[2] = 0;
}

void NaoProvider::disableMotor() {
  json sFrame;

  stiffness.fill(0.0);
  sFrame["Stiffness"] = stiffness;

  vector<uint8_t> sbuffer = json::to_msgpack(sFrame);

  assert(sbuffer.size() < MAXSENDMSGLEN);
  for (size_t i = 0; i < sbuffer.size(); i++) {
    packetToSend[i] = (unsigned char)sbuffer[i];
  }

  size_t send_stat = send(socket, reinterpret_cast<char *>(packetToSend.get()),
                          sbuffer.size(), 0);
  assert(send_stat == sbuffer.size());
}

void NaoProvider::disableLED() {
  json sFrame;

  chest.fill(0);
  sFrame["Chest"] = chest;

  vector<uint8_t> sbuffer = json::to_msgpack(sFrame);

  assert(sbuffer.size() < MAXSENDMSGLEN);
  for (size_t i = 0; i < sbuffer.size(); i++) {
    packetToSend[i] = (unsigned char)sbuffer[i];
  }

  size_t send_stat = send(socket, reinterpret_cast<char *>(packetToSend.get()),
                          sbuffer.size(), 0);
  assert(send_stat == sbuffer.size());
}

void NaoProvider::disableActuator() {
  disableMotor();
  disableLED();
}
