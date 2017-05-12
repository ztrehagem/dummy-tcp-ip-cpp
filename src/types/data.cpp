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
  delete payload;
}

void Data::preview() const {
  cout << "len: " << payload->get_len() << endl;
  cout << payload->get_bytes() << endl;
}

Serial *Data::serialize() const {
  return new Serial(payload->get_bytes(), payload->get_len());
}

string Data::to_str() {
  return string(payload->get_bytes(), payload->get_len());
}
