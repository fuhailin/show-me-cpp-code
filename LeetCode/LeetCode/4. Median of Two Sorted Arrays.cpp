#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

string longestPalindrome(string s) {
	int left = 0, right = 0, maxlen = 1, left_index = left;
	for (int i = 0; i < s.length(); i++)
	{
		//ż�����Ȼ��Ĵ�
		right = i;
		left = i - 1;
		while (left>=0&&right<s.length()&&s[left]==s[right])
		{
			if ((right - left + 1) > maxlen)
			{
				left_index = left;
				maxlen = right - left + 1;
			}
			--left;
			++right;
		}
		//�������Ȼ��Ĵ�
		right = i + 1;
		left = i - 1;
		while (left>=0 && right<s.length() && s[left] == s[right])
		{
			if ((right - left + 1) > maxlen)
			{
				left_index = left;
				maxlen = right - left + 1;
			}
			--left;
			++right;
		}
	}
	return s.substr(left_index, maxlen);
}

string Manacher(string s)
{
	/*�����ַ���*/
	string res = "$#";
	for (int i = 0; i<s.size(); ++i)
	{
		res += s[i];
		res += "#";
	}

	/*����*/
	vector<int> P(res.size(), 0);
	int mi = 0, right = 0;   //miΪ�����Ĵ���Ӧ�����ĵ㣬rightΪ�û��Ĵ��ܴﵽ�����Ҷ˵�ֵ
	int maxLen = 0, maxPoint = 0;    //maxLenΪ�����Ĵ��ĳ��ȣ�maxPointΪ��¼���ĵ�

	for (int i = 1; i < res.size(); ++i)
	{
		if (right > i)
		{
			P[i] = min(P[2 * mi - i], right - i);
		}
		else
		{
			P[i] = 1;
		}
		//P[i] = right>i ? min(P[2 * mi - i], right - i) : 1;     //�ؼ��䣬���ж��������ϸ����

		while (res[i + P[i]] == res[i - P[i]])
			++P[i];

		if (right < i + P[i])    //����֮ǰ�����Ҷˣ���ı����ĵ�Ͷ�Ӧ�����Ҷ�
		{
			right = i + P[i];
			mi = i;
		}

		if (maxLen < P[i])     //���������Ĵ��ĳ��ȣ������´�ʱ�ĵ�
		{
			maxLen = P[i];
			maxPoint = i;
		}
	}
	return s.substr((maxPoint - maxLen) / 2, maxLen - 1);
}

double median(vector<int> nums)
{
	int flag = nums.size() % 2;
	int mid;
	if (flag == 0)
	{
		mid = nums.size() / 2;
		return (nums[mid] + nums[mid - 1]) / 2.0;
	}
	else
	{
		mid = nums.size() / 2;
		return nums[mid];
	}
}

double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
	if (nums1.size() == 0)
		return median(nums2);
	if (nums2.size() == 0)
		return median(nums1);
	vector<int> num3;
	int size = (nums1.size() + nums2.size());
	int mid = size / 2;
	int flag = !(size % 2);
	int i, m1, m2, cur;
	double a, b;
	for (i = m1 = m2 = 0; i < size; i++)
	{
		a = m1 < nums1.size() ? nums1[m1] : INT_MAX;//���紦��
		b = m2 < nums2.size() ? nums2[m2] : INT_MAX;//���紦��
													//cout<<i<<" a "<<a<<" b "<<b<<endl;
		if (a < b)
		{
			num3.push_back(nums1[m1]);
			m1++;
		}
		else
		{
			num3.push_back(nums2[m2]);
			m2++;
		}
		if (i == mid)
			break;
	}
	return (num3[mid] + num3[mid - flag]) / 2.0;
}



int main()
{
	int a[] = { 1,2,5,8 }, b[] = { 0,1,3,4,6 };
	vector<int> A(begin(a), end(a)), B(begin(b), end(b));

	cout << findMedianSortedArrays(A, B);
	//cout << Manacher("abcba") << endl;
	system("pause");
	return 0;
}