
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>
#include <random>

#define MAXLINE 4096

static int holdPort(uint16_t port) {
  int listenfd;
  struct sockaddr_in servaddr;

  if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    return -2;
  }

  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(port);

  if (bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1) {
    return -1;
  }

  if (listen(listenfd, 10) == -1) {
    return -1;
  }

  return listenfd;
}

static uint16_t getRandomPort() {
  using namespace std;
  random_device rd;
  uniform_int_distribution<int> u(10000, 60000);
  int port = u(rd);
  return (uint16_t)port;
}

static void getHoldRandomPort(int& hfd, int& hport) {
  uint16_t p = getRandomPort();
  int fd;
  while (true) {
    std::cout << p << std::endl;
    fd = holdPort(p);
    if (fd == -2) {
      sleep(2);
      continue;
    } else if (fd == -1) {
      p = getRandomPort();
      continue;
    } else {
      break;
    }
  }
  hfd = fd;
  hport = p;
}
