#include "layer1.h"
#include "dip.h"



Layer1 *Layer1::build(const Layer2 &layer2) {
  return new Dip(layer2);
}
