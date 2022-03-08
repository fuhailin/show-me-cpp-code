#include <iostream>
#include <cuda_runtime.h>

using namespace std;

__global__ void demo(void)
{
}

int main()
{
	demo<<<1,1>>>();
	cout << "hello, world!" << endl;
	
	return 0;
}