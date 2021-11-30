// CPP program to illustrate
// std :: lower_bound
#include "bits/stdc++.h"

// Driver code
int main() {
    // Input vector
    std::vector<int> v{10, 20, 30, 30, 30, 40, 50};

    // Print vector
    std::cout << "Vector contains :";
    for (unsigned int i = 0; i < v.size(); i++)
        std::cout << " " << v[i];
    std::cout << "\n";

    std::vector<int>::iterator low1, low2, low3;

    // std :: lower_bound
    low1 = std::lower_bound(v.begin(), v.end(), 30);
    low2 = std::lower_bound(v.begin(), v.end(), 35);
    low3 = std::lower_bound(v.begin(), v.end(), 55);

    // Printing the lower bounds
    std::cout
        << "\nlower_bound for element 30 at position : "
        << (low1 - v.begin());
    std::cout
        << "\nlower_bound for element 35 at position : "
        << (low2 - v.begin());
    std::cout
        << "\nlower_bound for element 55 at position : "
        << (low3 - v.begin());

    std::vector<int>::iterator upper1, upper2;

    // std :: upper_bound
    upper1 = std::upper_bound(v.begin(), v.end(), 35);
    upper2 = std::upper_bound(v.begin(), v.end(), 45);

    std::cout << "\nupper_bound for element 35 is at position : "
              << (upper1 - v.begin());
    std::cout << "\nupper_bound for element 45 is at position : "
              << (upper2 - v.begin());

    std::cout << std::endl;

    vector<int>::iterator lower, upper;
    lower = lower_bound(v.begin(), v.end(), 30);
    upper = upper_bound(v.begin(), v.end(), 30);

    cout << "lower_bound for 30 at position "
         << (lower - v.begin()) << '\n';
    cout << "upper_bound for 30 at position "
         << (upper - v.begin()) << '\n';

    return 0;
}
