#pragma once

#include "layer2.h"
#include "layers/layer3/data.h"
#include "common/serial.h"


class Dtcp : public Layer2 {

public:
  Dtcp(const Data &data, const unsigned int type = 100);
  Dtcp(const Serial *bytes);
  ~Dtcp();

  Data *extract() const;
  Serial *serialize() const;
  void preview() const;

private:
  Serial *payload;
  unsigned int type;
  // string digest;

};
