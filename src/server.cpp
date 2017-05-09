#include <iostream>
#include "receiver.h"



int main(int argc, char const *argv[]) {
  Receiver receiver;

  try {
    receiver.start();
  } catch (char *str) {
    perror(str);
    exit(EXIT_FAILURE);
  }

  return 0;
}
