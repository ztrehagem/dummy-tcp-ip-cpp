#pragma once

#include <netinet/in.h>



class Receiver {

public:
  Receiver();
  ~Receiver();

  void start();

private:
  struct sockaddr_in addr;
  int sd;

  void listen();
  void accept();
  void recv(const int);

};
