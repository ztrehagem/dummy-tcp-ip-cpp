#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "common.h"
#include "sender.h"

using namespace std;

void printUsage() {
  cout << "usage: ./client <type> <filename>" << endl;
}

int main(int argc, char const *argv[]) {
  if (argc < 3) {
    printUsage();
    exit(EXIT_FAILURE);
  }

  Sender sender(argv[1], argv[2]);

  try {
    sender.start();
  } catch (char *str) {
    perror(str);
    exit(EXIT_FAILURE);
  }

  return 0;
}
