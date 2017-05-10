#pragma once

#include "serializable.h"
#include "layer1.h"



class Layer2 : public Serializable {

public:
  virtual ~Layer2() {};
  virtual Layer1 *pack() const = 0;
  virtual void preview() const = 0;

  enum Type {
    DTCP,
    DUDP,
  };

};
