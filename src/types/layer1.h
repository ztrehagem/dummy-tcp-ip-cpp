#pragma once

#include "serializable.h"



class Layer1 : public Serializable {

public:
  virtual ~Layer1() {};
  virtual void preview() const = 0;

};
