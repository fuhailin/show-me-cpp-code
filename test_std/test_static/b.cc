#include <iostream>
#include <sys/stat.h>

// 声明
void printHello();

int main(int argc, char* argv[])
{
    // 声明
    extern int a, b;
    static int c;
    std::cout << "a = " << a << "\nb = " << b << "\nc= " << c << std::endl;
    printHello();

    return 0;
}