#include <iostream>

#include "librdkafka/rdkafkacpp.h"
using namespace std;

int main(int argc, char const *argv[]) {
    /* code */
    string version = RdKafka::version_str();
    cout << "version: " << version << endl;
    return 0;
}
