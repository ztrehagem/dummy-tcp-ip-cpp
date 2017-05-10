#include <iostream>
#include <string>
#include "layer2.h"
#include "dtcp.h"

#include "data.h"

using namespace std;

// -- public

const int Data::MAX_SIZE = 1024;

Data::Data(const char *bytes, const unsigned int len) {
  if (len > Data::MAX_SIZE) {
    throw "over size";
  }
  this->bytes = new char[len];
  memcpy(this->bytes, bytes, len);
  this->len = len;
}

Data::~Data() {
  if (this->bytes) {
    delete[] this->bytes;
  }
}

void Data::preview() const {
  cout << "len: " << this->len << endl;
  cout << this->bytes << endl;
}

Serial *Data::serialize() const {
  return new Serial(this->bytes, this->len);
}

Layer2 *Data::pack(const Layer2::Type type) {
  switch (type) {
    case Layer2::DTCP: return new Dtcp(*this);
    case Layer2::DUDP: return new Dtcp(*this);
  }
  // switch (type) {
  //   case Layer2::DTCP:
  //   Dtcp dtcp(*this);
  //   return dtcp;
  //
  //   case Layer2::DUDP:
  //   Dtcp dtcp(*this);
  //   return dtcp;
  // }
}

string Data::to_str() {
  return string(this->bytes, this->len);
}
