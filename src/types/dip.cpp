#include "serial.h"

#include "dip.h"



Dip::Dip(const Layer2 &layer2, const unsigned int version, const unsigned int ttl) {
  this->payload = layer2.serialize();
  this->version = version;
  this->ttl = ttl;
}
Dip::Dip(char *bytes, unsigned int len) {

}
Dip::~Dip() {
  if (this->payload) {
    delete this->payload;
  }
}

Serial *Dip::serialize() const {
  // concat headers
  return new Serial(this->payload->get_bytes(), this->payload->get_len());
}
void Dip::preview() const {

}
