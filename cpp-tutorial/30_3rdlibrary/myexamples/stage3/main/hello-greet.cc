#include "myexamples/stage3/main/hello-greet.h"

#include <string>

template <typename T>
T get_greet(const T& who) {
    return "Hello " + who;
}
