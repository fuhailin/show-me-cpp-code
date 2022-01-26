#include <iostream>
#include <cstdlib>
 
int main()
{
    if(const char* env_p = std::getenv("MYENV"))
        std::cout << "Your PATH is: " << env_p << '\n';
}