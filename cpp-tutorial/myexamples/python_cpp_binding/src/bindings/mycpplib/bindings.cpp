#include "mycpplib/mycpplib.hpp"
#include "pybind11/embed.h"

namespace py = pybind11;

PYBIND11_MODULE(mycpplib, m) {
    // insert myPrint binding here
    m.doc() = "myPrint python extension";

    m.def("myPrint", &myPrint, "Prints a line of cpp code");
}