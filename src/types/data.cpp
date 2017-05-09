#include <iostream>

#include "data.h"

using namespace std;

// -- public

const int Data::MAX_SIZE = 1024;

Data::Data(char *bytes, unsigned int len) {
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

void Data::preview() {
  cout << "len: " << this->len << endl;
  cout << this->bytes << endl;
}

void Data::serialize(char **bytes, int *len) {
  *bytes = this->bytes;
  *len = this->len;
}

Data Data::parse(char *bytes, int len) {
  Data data(bytes, len);
  return data;
}
