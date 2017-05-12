#include <iostream>

#include "serial.h"



Serial::Serial(const char *bytes, const unsigned int len) : len(len) {
  this->bytes = new char[len];
  memcpy(this->bytes, bytes, len);
}

Serial::~Serial() {
  if (bytes) {
    delete[] bytes;
  }
}

char *Serial::get_bytes() const {
  return bytes;
}

unsigned int Serial::get_len() const {
  return len;
}
