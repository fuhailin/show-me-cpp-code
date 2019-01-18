#include <iostream>
#include <vector>
#include <string>
using namespace std;
class Solution
{
  public:
    string countAndSay(int n)
    {
        if (n == 0)
            return "";

        string res = "1";
        for (int i = 1; i < n; i++)
        {
            res = getNext(res);
        }
        // int myint = stoi();
        return res;
    }

  private:
    string getNext(string last)
    {
        string result = "";
        int count = 1;
        for (int i = 0; i < last.size(); i++)
        {
            if (i == last.length() - 1)
            {
                result.append(to_string(count)) += last.at(i);
                break;
            }
            while (last.at(i) == last.at(i + 1))
            {
                count++;
                i++;
                if (i + 1 == last.length())
                    break;
            }
            result.append(to_string(count)) += last.at(i);
            count = 1;
        }
        return result;
    }
};

int main(int argc, char const *argv[])
{
    Solution solu;
    int test = 4;
    string res = solu.countAndSay(test);
    cout << res << endl;
    return 0;
}
