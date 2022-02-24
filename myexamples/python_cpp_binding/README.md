# pb11_bazel_example

This example extends python with a function that prints through std::cout

```
bazel run //main:main
INFO: Analyzed target //main:main (23 packages loaded, 207 targets configured).
INFO: Found 1 target...
Target //main:main up-to-date:
  bazel-bin/main/main
INFO: Elapsed time: 6.032s, Critical Path: 2.85s
INFO: 5 processes: 5 darwin-sandbox.
INFO: Build completed successfully, 12 total actions
INFO: Build completed successfully, 12 total actions
Printing from CPP extension
Successful pybind11_bazel build! 
Press Return
```

https://github.com/M-Kerr/pb11_bazel_example