#include <iostream>

#include "serial.h"



Serial::Serial(const char *bytes, const unsigned int len) : len(len) {
  this->bytes = new char[len];
  memcpy(this->bytes, bytes, len);
}

Serial::~Serial() {
  if (this->bytes) {
    delete[] this->bytes;
  }
}

char *Serial::get_bytes() const {
  return this->bytes;
}

unsigned int Serial::get_len() const {
  return this->len;
}
