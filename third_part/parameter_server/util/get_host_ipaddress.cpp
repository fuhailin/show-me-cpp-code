#include "get_host_ipaddress.h"

bool get_host_ipAddress(std::string &ip) {
  struct ifaddrs *ifAddrStruct = NULL;
  void *tmpAddrPtr = NULL;

  getifaddrs(&ifAddrStruct);

  while (ifAddrStruct != NULL) {
    if (ifAddrStruct->ifa_addr->sa_family == AF_INET) {  // check it is IP4
      // is a valid IP4 Address
      tmpAddrPtr = &((struct sockaddr_in *)ifAddrStruct->ifa_addr)->sin_addr;
      char addressBuffer[INET_ADDRSTRLEN];
      inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
      ip = addressBuffer;
      if (ip == "127.0.0.1") {
        std::cout << "this is loal host" << std::endl;
      } else {
        std::cout << ip << std::endl;
        return true;
      }
    }
    //  printf("%s IP Address %s/n", ifAddrStruct->ifa_name, addressBuffer);
    // } else if (ifAddrStruct->ifa_addr->sa_family==AF_INET6) { // check it is
    // IP6
    //     // is a valid IP6 Address
    //     tmpAddrPtr=&((struct sockaddr_in *)ifAddrStruct->ifa_addr)->sin_addr;
    //     char addressBuffer[INET6_ADDRSTRLEN];
    //     inet_ntop(AF_INET6, tmpAddrPtr, addressBuffer, INET6_ADDRSTRLEN);
    //     printf("%s IP Address %s/n", ifAddrStruct->ifa_name, addressBuffer);
    // }
    ifAddrStruct = ifAddrStruct->ifa_next;
  }
  return false;
}

void print_test_bazel_update() {
  std::cout << "this is first time test" << std::endl;
}