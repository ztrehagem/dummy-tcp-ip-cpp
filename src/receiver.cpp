#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "common.h"
#include "types/data.h"
#include "types/layer2.h"
#include "types/dip.h"
#include "types/layer1.h"

#include "receiver.h"

using namespace std;

// -- public

Receiver::Receiver() {
  this->addr.sin_family = AF_INET;
  this->addr.sin_port = htons(PORT);
  this->addr.sin_addr.s_addr = INADDR_ANY;
}

Receiver::~Receiver() {
  if (this->sd) {
    close(this->sd);
  }
}

void Receiver::start() {
  this->listen();
  cout << "listening..." << endl;
  while (true) {
    this->accept();
  }
}

// -- private

void Receiver::listen() {
  this->sd = socket(AF_INET, SOCK_STREAM, 0);

  if (this->sd < 0) {
    throw "socket";
  }

  if (bind(this->sd, (struct sockaddr*)&this->addr, sizeof(this->addr)) < 0) {
    throw "bind";
  }

  if (::listen(this->sd, 10) < 0) {
    throw "listen";
  }
}

void Receiver::accept() {
  struct sockaddr_in addr;
  socklen_t socklen = sizeof(addr);
  int acc_sd = ::accept(this->sd, (struct sockaddr*)&addr, &socklen);

  if (acc_sd < 0) {
    throw "accept";
  }

  const pid_t pid = fork();

  if (pid < 0) {
    throw "fork";
  }

  if (pid == 0) {
    this->recv(acc_sd);
    close(acc_sd);
  }
}

void Receiver::recv(const int sd) {
  char buf[2048];

  cout << "*** connected ***" << endl;

  while(true) {
    memset(buf, '\0', sizeof(buf));

    ssize_t len = ::recv(sd, buf, sizeof(buf), 0);

    if (len < 0) {
      throw "recv";
    }

    if (len == 0) {
      break;
    }

    cout << buf << endl;

    // Dip dip(buf, len);
    // Layer2 layer2 = dip.unpack();
    // Data data(layer2);
    //
    // cout << data
    //
    // delete layer2;
  }

  cout << "*** closed ***" << endl;
}
