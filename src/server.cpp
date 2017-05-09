#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "common.h"

using namespace std;

int main(int argc, char const *argv[]) {
  cout << "server: Hello, World!" << endl;


  int sd, acc_sd;
  struct sockaddr_in addr;

  socklen_t sin_size = sizeof(struct sockaddr_in);
  struct sockaddr_in from_addr;

  if ((sd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("socket");
    exit(EXIT_FAILURE);
  }

  addr.sin_family = AF_INET;
  addr.sin_port = htons(PORT);
  addr.sin_addr.s_addr = INADDR_ANY;

  if (bind(sd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
    perror("bind");
    exit(EXIT_FAILURE);
  }

  if (listen(sd, 10) < 0) {
    perror("listen");
    exit(EXIT_FAILURE);
  }

  while(true) {
    if ((acc_sd = accept(sd, (struct sockaddr*)&from_addr, &sin_size)) < 0) {
      perror("accept");
      exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if (pid < 0) {
      perror("fork");
      exit(EXIT_FAILURE);
    }

    if (pid == 0) {
      char buf[1024];

      while (true) {
        memset(buf, 0, sizeof(buf));

        ssize_t len = recv(acc_sd, buf, sizeof(buf), 0);

        if (len < 0) {
          perror("recv");
          exit(EXIT_FAILURE);
        }

        if (len == 0) {
          break;
        }

        cout << buf;
      }

      close(acc_sd);
      cout << "closed." << endl;;

      exit(EXIT_SUCCESS);
    }
  };

  close(sd);

  return 0;
}
