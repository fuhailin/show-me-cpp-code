#include <iostream>
#include <string>

#include "myexamples/stage3/lib/hello-time.h"
#include "myexamples/stage3/main/hello-greet.h"

int main(int argc, char** argv) {
    std::string who = "world";
    if (argc > 1) {
        who = argv[1];
    }
    std::cout << get_greet(who) << std::endl;
    print_localtime();
    return 0;
}
