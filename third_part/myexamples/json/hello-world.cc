#include <fstream>
#include <iostream>
#include <string>

#include "include/nlohmann/json.hpp"

using json = nlohmann::json;

int main(int argc, char **argv) {
    json j;  // 创建 json 对象
    std::ifstream jfile("test.json");
    jfile >> j;  // 以文件流形式读取 json 文件
    auto uid = j.at("labels");
    std::cout << uid << std::endl;

    return 0;
}
