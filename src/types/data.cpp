#include <iostream>
#include <string>
#include "dtcp.h"

#include "data.h"

using namespace std;

// -- public

const int Data::MAX_SIZE = 1024;

Data::Data(const char *bytes, const unsigned int len) {
  if (len > Data::MAX_SIZE) {
    throw "over size";
  }
  this->payload = new Serial(bytes, len);
}

Data::Data(const Serial *bytes) {
  // parse
  if (bytes->get_len() > Data::MAX_SIZE) {
    throw "over size";
  }
  this->payload = new Serial(bytes->get_bytes(), bytes->get_len());
}

Data::~Data() {
  delete this->payload;
}

void Data::preview() const {
  cout << "len: " << this->payload->get_len() << endl;
  cout << this->payload->get_bytes() << endl;
}

Serial *Data::serialize() const {
  return new Serial(this->payload->get_bytes(), this->payload->get_len());
}

Layer2 *Data::pack(const Layer2::Type type) {
  switch (type) {
    case Layer2::DTCP: return new Dtcp(*this);
    case Layer2::DUDP: return new Dtcp(*this);
  }
}

string Data::to_str() {
  return string(this->payload->get_bytes(), this->payload->get_len());
}
