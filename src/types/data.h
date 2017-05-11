#pragma once

#include <string>
#include "serial.h"
#include "serializable.h"
// class Layer2;
// #include "layer2.h"

using namespace std;



class Data : public Serializable {

public:
  static const int MAX_SIZE;

  Data(const char *bytes, const unsigned int len);
  Data(const Serial *bytes);
  ~Data();
  void preview() const;
  Serial *serialize() const;
  string to_str();

private:
  Serial *payload;

};
