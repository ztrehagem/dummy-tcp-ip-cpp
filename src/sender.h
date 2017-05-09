#pragma once

#include <string>
#include <netinet/in.h>
#include "common.h"

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

  void send(char *data, int len);
};
