#pragma once

#include "layer1.h"
#include "layer2.h"
#include "serial.h"


class Dip : public Layer1 {

public:
  Dip(const Layer2 &layer2, const unsigned int version = 20, const unsigned int ttl = 114514);
  Dip(Serial *bytes);
  ~Dip();

  Serial *serialize() const;
  Layer2 *extract() const;
  void preview() const;

private:
  Serial *payload;
  unsigned int type, version, ttl;

};
