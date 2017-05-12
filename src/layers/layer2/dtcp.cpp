#include "dtcp.h"
#include <iostream>




Dtcp::Dtcp(const Data &data, const unsigned int type) : Layer2(Layer2::DTCP) {
  this->payload = data.serialize();
  this->type = type;
}
Dtcp::Dtcp(const Serial *bytes) : Layer2(Layer2::DTCP) {
  // parse
  this->payload = new Serial(bytes->get_bytes(), bytes->get_len());
  this->type = 1;
}
Dtcp::~Dtcp() {
  if (payload) {
    delete payload;
  }
}

Data *Dtcp::extract() const {
  return new Data(payload);
}
Serial *Dtcp::serialize() const {
  // concat header
  return new Serial(payload->get_bytes(), payload->get_len());
}
void Dtcp::preview() const {

}
