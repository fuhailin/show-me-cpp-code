#include <glog/logging.h>
#include <glog/stl_logging.h>

#include <iostream>
#include <iterator>
// #include <map>
#include <unordered_map>


using namespace std;

int main() {
    // empty map container
    map<int, int> gquiz1;

    // insert elements in random order
    gquiz1.insert(pair<int, int>(4, 20));
    gquiz1.insert(pair<int, int>(5, 50));
    gquiz1.insert(pair<int, int>(1, 40));
    gquiz1.insert(pair<int, int>(7, 10));
    gquiz1.insert(pair<int, int>(2, 30));
    gquiz1.insert(pair<int, int>(3, 60));
    gquiz1.insert(pair<int, int>(6, 50));

    // printing map gquiz1
    map<int, int>::iterator itr;
    LOG(INFO) << "The map gquiz1 is : \n";
    LOG(INFO) << "\tKEY\tELEMENT\n";
    for (itr = gquiz1.begin(); itr != gquiz1.end(); ++itr) {
        LOG(INFO) << '\t' << itr->first
                  << '\t' << itr->second;
    }

    // assigning the elements from gquiz1 to gquiz2
    map<int, int> gquiz2(gquiz1.begin(), gquiz1.end());

    // print all elements of the map gquiz2
    LOG(INFO) << "The map gquiz2 after"
              << " assign from gquiz1 is : \n";
    LOG(INFO) << "\tKEY\tELEMENT\n";
    for (itr = gquiz2.begin(); itr != gquiz2.end(); ++itr) {
        LOG(INFO) << '\t' << itr->first
                  << '\t' << itr->second;
    }

    // remove all elements up to
    // element with key=3 in gquiz2
    LOG(INFO) << "gquiz2 after removal of"
                 " elements less than key=3 :";
    LOG(INFO) << "\tKEY\tELEMENT\n";
    gquiz2.erase(gquiz2.begin(), gquiz2.find(3));
    for (itr = gquiz2.begin(); itr != gquiz2.end(); ++itr) {
        LOG(INFO) << '\t' << itr->first
                  << '\t' << itr->second;
    }

    // remove all elements with key = 4
    int num;
    num = gquiz2.erase(4);
    LOG(INFO) << "gquiz2.erase(4) : ";
    LOG(INFO) << num << " removed ";
    LOG(INFO) << "\tKEY\tELEMENT";
    for (itr = gquiz2.begin(); itr != gquiz2.end(); ++itr) {
        LOG(INFO) << '\t' << itr->first
                  << '\t' << itr->second;
    }

/*
    // lower bound and upper bound for map gquiz1 key = 5
    LOG(INFO) << "gquiz1.lower_bound(5) : "
              << "\tKEY = ";
    LOG(INFO) << gquiz1.lower_bound(5)->first << '\t';
    LOG(INFO) << "\tELEMENT = "
              << gquiz1.lower_bound(5)->second;
    LOG(INFO) << "gquiz1.upper_bound(5) : "
              << "\tKEY = ";
    LOG(INFO) << gquiz1.upper_bound(5)->first << '\t';
    LOG(INFO) << "\tELEMENT = "
              << gquiz1.upper_bound(5)->second;
              */

    return 0;
}
