#pragma once

#include "common/serializable.h"
#include "layers/layer3/data.h"



class Layer2 : public Serializable {

public:
  enum Type {
    DTCP = 0,
    DUDP,
  };

  Layer2(const Type type) : type(type) {};
  virtual ~Layer2() {};
  virtual Data *extract() const = 0;
  virtual void preview() const = 0;

  static Layer2 *build(const Data &, const Type);

  const Type type;

};
