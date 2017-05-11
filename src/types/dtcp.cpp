#include <iostream>
#include "dip.h"
#include "serial.h"

#include "dtcp.h"



Dtcp::Dtcp(const Data &data, const unsigned int type) : Layer2(Layer2::DTCP) {
  this->payload = data.serialize();
  this->type = type;
}
Dtcp::Dtcp(const Serial *bytes) {
  // parse
  this->payload = new Serial(bytes->get_bytes(), bytes->get_len());
  this->type = 1;
}
Dtcp::~Dtcp() {
  if (this->payload) {
    delete this->payload;
  }
}

Layer1 *Dtcp::pack() const {
  return new Dip(*this);
}
Data *Dtcp::extract() const {
  return new Data(this->payload);
}
Serial *Dtcp::serialize() const {
  // concat header
  return new Serial(this->payload->get_bytes(), this->payload->get_len());
}
void Dtcp::preview() const {

}
