#ifndef MAIN_HELLO_GREET_H_
#define MAIN_HELLO_GREET_H_

#include <string>

// template <typename T>
// T get_greet(const T& thing);
template <typename T>
T get_greet(const T& who) {
    return "Hello " + who;
}

#endif
