#include <iostream>
#include <fstream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "common.h"
#include "types/data.h"

#include "sender.h"

using namespace std;

// -- public

Sender::Sender(const char *type, const char *filename) {
  this->type = type;
  this->filename = filename;

  this->addr.sin_family = AF_INET;
  this->addr.sin_port = htons(PORT);
  this->addr.sin_addr.s_addr = inet_addr("127.0.0.1");
}

Sender::~Sender() {
  if (this->sd) {
    close(this->sd);
  }
}

void Sender::start() {
  ifstream file(this->filename, ifstream::in);

  if (!file.is_open()) {
    cout << "file not found '" << this->filename << "'" << endl;
    return;
  }

  char buf[1024];

  file.seekg(0, ifstream::end);
  const int end_pos = file.tellg();
  file.seekg(0, ifstream::beg);

  int pos = file.tellg();

  while(!file.eof()) {
    memset(buf, '\0', sizeof(buf));

    file.read(buf, sizeof(buf));

    int after_pos = file.tellg();
    if (after_pos == -1) {
      after_pos = end_pos;
    }

    int read_len = after_pos - pos;

    // -- make packet
    Data data(buf, read_len);
    // -- make packet

    char *bytes;
    int len;
    data.serialize(&bytes, &len);

    this->send(bytes, len);

    pos = after_pos;
  }
}


// -- private

void Sender::send(char *bytes, int len) {
  this->sd = ::socket(AF_INET, SOCK_STREAM, 0);

  if (this->sd < 0) {
    throw "socket";
  }


  if (::connect(this->sd, (struct sockaddr*)&this->addr, sizeof(this->addr))) {
    throw "connect";
  }

  if (::send(this->sd, bytes, len, 0) < 0) {
    throw "send";
  }
}
