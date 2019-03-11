#include <iostream>
#include <vector>
using namespace std;
void count(vector<int> &nums)
{
    // TODO Auto-generated method stub
    int n = nums.size();
    int i = 0;
    //采用while循环
    while (i < n)
    {
        //由于元素取值范围为[1,N]，因此，可以将（当前元素值-1）作为下标值，找到相应位置处的元素，将其存储的值作为-times，因为原来存储值都为正值，为防止混淆，用负值存储
        int temp = nums[i] - 1;
        if (temp < 0)
        { //表示该元素已经处理过了，跳过
            i++;
            continue;
        }
        else if (nums[temp] > 0)
        {                         //第一次处理一个值
            nums[i] = nums[temp]; //暂存新元素
            nums[temp] = -1;
        }
        else
        { //已经不是第一次处理该值了

            nums[i] = 0; //没有新的元素要处理，置0
            nums[temp]--;
        }
    }

    for (int j = 0; j < n; ++j)
    {
        cout << j + 1 << "," + -nums[j] << "\t";
    }
}

int main(int argc, char const *argv[])
{
    vector<int> test{6, 2, 4, 1, 2, 5};
    count(test);
    return 0;
}