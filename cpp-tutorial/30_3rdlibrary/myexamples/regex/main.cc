#include <iostream>
#include <regex>
#include <string>
#include <vector>

// #include "regex.hpp"

int main() {
    std::string pattern{"click"};  // fixed telephone
    std::regex re(pattern);

    std::vector<std::string> str{"click", "play", "oracle_pred_click", "oracle_pred_play", "CTR", "CVR"};

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