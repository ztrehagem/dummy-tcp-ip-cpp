#include "sender.h"
#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "common/common.h"
#include "layers/layer3/data.h"
#include "layers/layer1/layer1.h"

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
  if (sd) {
    close(sd);
  }
}

void Sender::start() {
  ifstream file(filename, ifstream::in);

  if (!file.is_open()) {
    cout << "file not found '" << filename << "'" << endl;
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
    Serial *packet = create_packet(buf, read_len, Layer2::DTCP);
    send(packet);
    delete packet;

    pos = after_pos;
  }
}


// -- private

Serial *Sender::create_packet(const char* bytes, const unsigned int len, const Layer2::Type type) {
  Data *data = new Data(bytes, len);
  Layer2 *layer2 = Layer2::build(*data, type);
  Layer1 *layer1 = Layer1::build(*layer2);
  Serial *serial = layer1->serialize();
  delete layer1;
  delete layer2;
  delete data;
  return serial;
}

void Sender::send(const Serial *packet) {
  send(packet->get_bytes(), packet->get_len());
}

void Sender::send(const char *bytes, const size_t len) {
  sd = ::socket(AF_INET, SOCK_STREAM, 0);

  if (sd < 0) {
    throw "socket";
  }


  if (::connect(sd, (struct sockaddr*)&addr, sizeof(addr))) {
    throw "connect";
  }

  if (::send(sd, bytes, len, 0) < 0) {
    throw "send";
  }
}
