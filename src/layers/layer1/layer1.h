#pragma once

#include "common/serializable.h"
#include "layers/layer2/layer2.h"



class Layer1 : public Serializable {

public:
  virtual ~Layer1() {};
  virtual Layer2 *extract() const = 0;
  virtual void preview() const = 0;

  static Layer1 *build(const Layer2 &);

};
