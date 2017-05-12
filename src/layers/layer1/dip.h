#pragma once

#include "layer1.h"
#include "layers/layer2/layer2.h"
#include "common/serial.h"


class Dip : public Layer1 {

public:
  Dip(const Layer2 &layer2, const unsigned int version = 20, const unsigned int ttl = 114514);
  Dip(Serial *bytes);
  Dip(const char *bytes, const unsigned int len);
  ~Dip();

  Serial *serialize() const;
  Layer2 *extract() const;
  void preview() const;

private:
  Serial *payload;
  Layer2::Type type;
  unsigned int version, ttl;

};
