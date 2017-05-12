#pragma once

#include <string>
#include "common/serial.h"
#include "common/serializable.h"

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
