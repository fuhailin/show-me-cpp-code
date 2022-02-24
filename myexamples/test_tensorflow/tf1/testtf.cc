#include <iostream>

#include "tensorflow/cc/client/client_session.h"
#include <tensorflow/core/platform/env.h>
#include <tensorflow/core/public/session.h>

using namespace std;
using namespace tensorflow;

int main() {
    tensorflow::Scope scope = tensorflow::Scope::NewRootScope();

    if (!scope.ok()) {
        cout << scope.status().ToString() << "\n";
        return 1;
    }
    cout << "Session successfully created.\n";
}

// bazel build -c opt — verbose_failures //tensorflow:libtensorflow_framework.so