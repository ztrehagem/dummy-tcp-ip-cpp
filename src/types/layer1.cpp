#include "dip.h"

#include "layer1.h"



Layer1 *Layer1::build(const Layer2 &layer2) {
  return new Dip(layer2);
}
