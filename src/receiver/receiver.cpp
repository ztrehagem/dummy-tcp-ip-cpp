#include "receiver.h"
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "common/common.h"
#include "layers/layer3/data.h"
#include "layers/layer2/layer2.h"
#include "layers/layer1/dip.h"

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
  listen();
  cout << "listening..." << endl;
  while (true) {
    accept();
  }
}

// -- private

void Receiver::listen() {
  sd = ::socket(AF_INET, SOCK_STREAM, 0);

  if (sd < 0) {
    throw "socket";
  }

  if (::bind(sd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
    throw "bind";
  }

  if (::listen(sd, 10) < 0) {
    throw "listen";
  }
}

void Receiver::accept() {
  struct sockaddr_in addr;
  socklen_t socklen = sizeof(addr);
  int acc_sd = ::accept(sd, (struct sockaddr*)&addr, &socklen);

  if (acc_sd < 0) {
    throw "accept";
  }

  const pid_t pid = fork();

  if (pid < 0) {
    throw "fork";
  }

  if (pid == 0) {
    recv(acc_sd);
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

    Layer1 *layer1 = new Dip(buf, len);
    Layer2 *layer2 = layer1->extract();
    Data *data = layer2->extract();

    cout << data->to_str() << endl;

    delete data;
    delete layer2;
    delete layer1;
  }

  cout << "*** closed ***" << endl;
}
