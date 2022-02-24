// C++ program to split
// string into substrings
// which are separated by
// separater using boost::split

// this header file contains boost::split function

// #include <bits/stdc++.h>

#include <boost/algorithm/string.hpp>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

int main() {
    string input("geeksforgeeks");
    vector<string> result;
    boost::split(result, input, boost::is_any_of("\t"));

    for (size_t i = 0; i < result.size(); i++) {
        std::cout << result[i] << std::endl;
    }
    return 0;
}
