#include <iostream>
#include "layer1.h"
#include "dip.h"
#include "serial.h"

#include "dtcp.h"



Dtcp::Dtcp(const Data &data, const unsigned int type) {
  this->payload = data.serialize();
  this->type = type;
}
Dtcp::Dtcp(char *bytes, unsigned int len) {
  // parse
}
Dtcp::~Dtcp() {
  if (this->payload) {
    delete this->payload;
  }
}

Layer1 *Dtcp::pack() const {
  return new Dip(*this);
}
Serial *Dtcp::serialize() const {
  // concat header
  return new Serial(this->payload->get_bytes(), this->payload->get_len());
}
void Dtcp::preview() const {

}
