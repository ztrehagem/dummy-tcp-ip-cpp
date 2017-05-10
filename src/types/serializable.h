#pragma once

#include "serial.h"



class Serializable {

public:
  virtual Serial *serialize() const = 0;

};
