#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

using namespace std;

int main(int argc, char const *argv[]) {
  cout << "server: Hello, World!" << endl;


  int sd, acc_sd;
  struct sockaddr_in addr;

  socklen_t sin_size = sizeof(struct sockaddr_in);
  struct sockaddr_in from_addr;

  char buf[2048];

  memset(buf, 0, sizeof(buf));

  if ((sd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("socket");
    exit(EXIT_FAILURE);
  }

  addr.sin_family = AF_INET;
  addr.sin_port = htons(22222);
  addr.sin_addr.s_addr = INADDR_ANY;

  if (bind(sd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
    perror("bind");
    exit(EXIT_FAILURE);
  }

  if (listen(sd, 10) < 0) {
    perror("listen");
    exit(EXIT_FAILURE);
  }

  bool end = false;

  do {
    puts("listening...");

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
      // child
      if (recv(acc_sd, buf, sizeof(buf), 0) < 0) {
        perror("recv");
        exit(EXIT_FAILURE);
      }

      cout << buf << endl;

      close(acc_sd);

      exit(EXIT_SUCCESS);
    }
  } while(!end);

  close(sd);

  return 0;
}
