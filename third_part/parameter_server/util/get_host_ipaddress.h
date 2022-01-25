#ifndef GET_HOST_APADDRESS_H
#define GET_HOST_APADDRESS_H

#include <arpa/inet.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

#include <iostream>
#include <string>

bool get_host_ipAddress(std::string& ip);
void print_test_bazel_update();
#endif