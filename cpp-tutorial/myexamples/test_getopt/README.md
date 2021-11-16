(base) root@recall-gpu-01:~/fuhailin/projects/cpp_tutorial/myexamples/test_getopt# bazel run main
INFO: Analyzed target //myexamples/test_getopt:main (0 packages loaded, 0 targets configured).
INFO: Found 1 target...
Target //myexamples/test_getopt:main up-to-date:
  bazel-bin/myexamples/test_getopt/main
INFO: Elapsed time: 0.072s, Critical Path: 0.00s
INFO: 1 process: 1 internal.
INFO: Build completed successfully, 1 total action
INFO: Build completed successfully, 1 total action
aflag = 0, bflag = 0, cvalue = (null)

(base) root@recall-gpu-01:~/fuhailin/projects/cpp_tutorial/myexamples/test_getopt# bazel run main -a -b
ERROR: -a :: Unrecognized option: -a

(base) root@recall-gpu-01:~/fuhailin/projects/cpp_tutorial# ./bazel-bin/myexamples/test_getopt/main
aflag = 0, bflag = 0, cvalue = (null)


(base) root@recall-gpu-01:~/fuhailin/projects/cpp_tutorial# ./bazel-bin/myexamples/test_getopt/main -a -b
aflag = 1, bflag = 1, cvalue = (null)


