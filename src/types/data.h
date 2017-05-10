#pragma once

#include <string>
#include "layer2.h"
#include "serializable.h"

using namespace std;



class Data : public Serializable {

public:
  static const int MAX_SIZE;

  Data(const char *bytes, const unsigned int len);
  Data(Layer2 layer2);
  ~Data();
  void preview() const;
  Serial *serialize() const;
  Layer2 *pack(const Layer2::Type type);
  string to_str();

private:
  char *bytes;
  unsigned int len;

};
