#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "common.h"

using namespace std;

void printUsage() {
  cout << "usage: ./client <type> <filename>" << endl;
}

int main(int argc, char const *argv[]) {
  cout << "client: Hello, World!" << endl;

  if (argc <= 2) {
    printUsage();
    return 1;
  }

  string layer2Type = argv[1];

  cout << layer2Type << endl;



  int sd;
  struct sockaddr_in addr;

  if ((sd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("socket");
    return -1;
  }

  addr.sin_family = AF_INET;
  addr.sin_port = htons(PORT);
  addr.sin_addr.s_addr = inet_addr("127.0.0.1");

  connect(sd, (struct sockaddr*)&addr, sizeof(struct sockaddr_in));

  string str;

  while (true) {
    str = "";

    cout << "> ";
    cin >> str;

    if (str.length() == 0) {
      break;
    }

    str += '\n';

    if (send(sd, str.c_str(), str.length(), 0) < 0) {
      perror("send");
      exit(EXIT_FAILURE);
    }
  }

  close(sd);

  cout << endl;

  return 0;
}
