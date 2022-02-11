#include "glog/logging.h"
#include "gflags/gflags.h"
 
DEFINE_string(name, "alan", "your name");
DEFINE_int32(age, 0, "your age");
 
int main(int argc, char *argv[]) {
    // google::InitGoogleLogging(argv[0]);
    // FLAGS_logtostderr = 1;
    // FLAGS_colorlogtostderr = 1;
    gflags::ParseCommandLineFlags(&argc, &argv, true);
 
    LOG(INFO) << "hello " << FLAGS_name;
    LOG(INFO) << "age: " << FLAGS_age;
 
    return 0;
}