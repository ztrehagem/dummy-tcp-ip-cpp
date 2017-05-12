#pragma once

#include <string>
#include <netinet/in.h>
#include "common/serial.h"
#include "layers/layer2/layer2.h"

using namespace std;

class Sender {

public:
  Sender(const char *type, const char *filename);
  ~Sender();

  void start();

private:
  string type, filename;
  struct sockaddr_in addr;
  int sd;

  Serial *create_packet(const char *data, const unsigned int len, const Layer2::Type type);
  void send(const Serial *packet);
  void send(const char *data, const size_t len);
};
