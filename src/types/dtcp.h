#pragma once

#include "layer1.h"
#include "layer2.h"
#include "data.h"
#include "serial.h"


class Dtcp : public Layer2 {

public:
  Dtcp(const Data &data, const unsigned int type = 100);
  Dtcp(char *bytes, unsigned int len);
  ~Dtcp();

  Layer1 *pack() const;
  Serial *serialize() const;
  void preview() const;

private:
  Serial *payload;
  unsigned int type;
  // string digest;

};