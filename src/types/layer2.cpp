#include "dtcp.h"

#include "layer2.h"



Layer2 *Layer2::build(const Data &data, const Layer2::Type type) {
  switch (type) {
    case DTCP: return new Dtcp(data);
    case DUDP: return new Dtcp(data);
  }
}
