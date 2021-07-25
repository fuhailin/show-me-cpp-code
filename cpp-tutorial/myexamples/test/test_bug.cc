// https://www.cnblogs.com/joeblackzqq/archive/2011/04/11/2012318.html

#include <iostream>

void dummy_function() {
    unsigned char *ptr = 0x00;
    *ptr = 0x00;
    std::cout << "bug" << std::endl;
}

int main(void) {
    dummy_function();

    return 0;
}
