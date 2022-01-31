bazel build --config=opt \
    //tensorflow:tensorflow_cc \
    //tensorflow:libtensorflow.so \
    //tensorflow:libtensorflow_cc.so \
    //tensorflow:libtensorflow_framework.so \
    //tensorflow:install_headers \
    //tensorflow/tools/pip_package:build_pip_package
