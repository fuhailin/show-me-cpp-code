#include <iostream>
#include <regex>
#include <string>
#include <vector>

// #include "regex.hpp"

int main() {
    std::string pattern{"ctr0|ctr1|ctr2|ctr3|ctr4|ctr5|ctr6|ctr7|ctr8|ctr9"};  // fixed telephone
    std::regex re(pattern);

    std::vector<std::string> str{"ctr0", "ctr1", "ctr2", "ctr3", "ctr4", "ctr5"};

    /* std::regex_match:
		判断一个正则表达式(参数re)是否匹配整个字符序列str,它主要用于验证文本
		注意，这个正则表达式必须匹配被分析串的全部，否则返回false;如果整个序列被成功匹配，返回true
	*/

    for (auto tmp : str) {
        bool ret = std::regex_match(tmp, re);
        if (ret)
            fprintf(stderr, "%s, can match\n", tmp.c_str());
        else
            fprintf(stderr, "%s, can not match\n", tmp.c_str());
    }

    return 0;
}