#include <iostream>
#include <fstream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "common.h"
#include "types/serial.h"
#include "types/data.h"
#include "types/layer1.h"
#include "types/layer2.h"

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

  char buf[Data::MAX_SIZE];

  file.seekg(0, ifstream::end);
  const int end_pos = file.tellg();
  file.seekg(0, ifstream::beg);

  int pos = file.tellg();

  while(!file.eof()) {
    memset(buf, '\0', sizeof(buf));

    file.read(buf, sizeof(buf));

    int after_pos = file.tellg();
    if (after_pos < 0) {
      after_pos = end_pos;
    }

    const unsigned int read_len = after_pos - pos;

    // -- make packet
    Serial *packet = this->create_packet(buf, read_len, Layer2::DTCP);
    this->send(packet);
    delete packet;

    pos = after_pos;
  }
}


// -- private

Serial *Sender::create_packet(const char* bytes, const unsigned int len, const Layer2::Type type) {
  Data data(bytes, len);
  Layer2 *layer2 = Layer2::build(data, type);
  Layer1 *layer1 = Layer1::build(*layer2);
  Serial *serial = layer1->serialize();

  delete layer2;
  delete layer1;

  return serial;
}

void Sender::send(const Serial *packet) {
  this->send(packet->get_bytes(), packet->get_len());
}

void Sender::send(const char *bytes, const size_t len) {
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
