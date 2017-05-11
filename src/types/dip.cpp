#include "serial.h"

#include "dip.h"
#include "dtcp.h"



Dip::Dip(const Layer2 &layer2, const unsigned int version, const unsigned int ttl) {
  // build
  this->payload = layer2.serialize();
  this->type = Layer2::DTCP; // TODO detect from layer2
  this->version = version;
  this->ttl = ttl;
}
Dip::Dip(Serial *bytes) {
  // parse
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
Layer2 *Dip::extract() const {
  // switch type dtcp/dudp
  return new Dtcp(this->payload);
}
void Dip::preview() const {

}
