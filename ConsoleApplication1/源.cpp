#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#include<set>
#include<vector>
#include<stdlib.h>
#include <string.h> 
using namespace std;
char ch[1050];
int num[1050];
int flag[10];
int cmp(const void *a, const void *b)
{
	return *(int *)b - *(int *)a;
}
void printone()
{
	cout << "impossible" << endl;
	memset(ch, '0', sizeof(strlen(ch)));
	memset(num, 0, sizeof(num));
}
void print(int num[], int len)
{
	int number = 0;
	for (int i = 0; i < len; i++)
	{
		cout << num[i];
	}
	cout << endl;

}
void del(int num[], int i, int len)
{
	int j;
	for (j = i; j < len - 1; j++)
	{
		num[j] = num[j + 1];
	}
	num[j] = 0;
}
int delonetwochar(int num[], int i, int len, int flag[])
{
	if (flag[2] != 0 && num[i] == 2)
	{
		del(num, i, len);
		flag[2]--;
		return 0;
	}
	else if (flag[5] != 0 && num[i] == 5)
	{
		del(num, i, len);
		flag[5]--;
		return 0;
	}
	else if (flag[8] != 0 && num[i] == 8)
	{
		del(num, i, len);
		flag[8]--;
		return 0;
	}
	return 1;
}
int deltwotwochar(int num[], int i, int len, int flag[])
{
	if (flag[1] != 0 && num[i] == 1)
	{
		del(num, i, len);
		flag[1]--;
		return 0;
	}
	else if (flag[4] != 0 && num[i] == 4)
	{
		del(num, i, len);
		flag[4]--;
		return 0;
	}
	else if (flag[7] != 0 && num[i] == 7)
	{
		del(num, i, len);
		flag[7]--;
		return 0;
	}
	return 1;
}
int main()
{
	memset(ch, '0', sizeof(ch));
	memset(num, 0, sizeof(num));
	while (scanf("%s", ch) != EOF)
	{
		int i, j, sum = 0, tag = 0, count = 0;
		memset(flag, 0, sizeof(flag));
		int len = strlen(ch);
		for (i = 0; i < len; i++)
		{
			num[i] = ch[i] - '0';
		}
		qsort(num, len, sizeof(num[0]), cmp);
		for (i = 0; i < len; i++)
		{
			if (num[i] == 0)flag[0]++;
			else if (num[i] == 5)flag[5]++;
			else if (num[i] == 1)flag[1]++;
			else if (num[i] == 2)flag[2]++;
			else if (num[i] == 4)flag[4]++;
			else if (num[i] == 7)flag[7]++;
			else if (num[i] == 8)flag[8]++;
		}
		if (flag[0] == 0 && flag[5] == 0)
		{
			printone();
			continue;
		}
		for (i = 0; i < len; i++)
		{
			sum += num[i];
		}

		if (num[len - 1] == 0)//尾数为0
		{
			if (sum % 3 == 0)//刚好整除
			{
				if (sum == 0) { cout << "0" << endl; continue; }
				print(num, len);
				memset(ch, '0', sizeof(strlen(ch)));
				memset(num, 0, sizeof(num));
				continue;
			}
			else if (sum % 3 == 1)//和整除3余1有1，4，7三种可能情况
			{
				for (i = len - 2; i >= 0; i--)
				{
					if (flag[1] != 0 && num[i] == 1)//删除1
					{
						del(num, i, len);
						break;
					}
					else if (flag[4] != 0 && num[i] == 4)//删除4
					{
						del(num, i, len);
						break;
					}
					else if (flag[7] != 0 && num[i] == 7)//删除7
					{
						del(num, i, len);
						break;
					}
					if (flag[1] == 0 && flag[4] == 0 && flag[7] == 0)
					{
						if (delonetwochar(num, i, len, flag) == 1)
						{
							if (num[0] == 0) { num[0] = 0; break; }
							else if (i == 0)
							{
								printone(); tag = 1; break;
							}
						}
						else
						{
							count++; if (count == 2) { len--; break; }
						}
					}
				}
			}
			else if (sum % 3 == 2)
			{
				for (i = len - 2; i >= 0; i--)
				{
					if (flag[2] != 0 && num[i] == 2)//删除2
					{
						del(num, i, len);
						break;
					}
					else if (flag[5] != 0 && num[i] == 5)//删除5
					{
						del(num, i, len);
						break;
					}
					else if (flag[8] != 0 && num[i] == 8)//删除8
					{
						del(num, i, len);
						break;
					}
					else if (flag[2] == 0 && flag[5] == 0 && flag[8] == 0)
					{
						if (deltwotwochar(num, i, len, flag) == 1)
						{
							if (i == 0) { printone(); tag = 1; break; }
						}
						else
						{
							count++; if (count == 2) { len--; break; }
						}
					}
				}
			}
			//num[len - 2] = num[len - 1];
			if (tag == 1)continue;
			len--;
			if (num[0] == 0) { cout << "0" << endl; continue; }
			if (len < 2) { printone(); continue; }
			print(num, len);
		}
		else//尾数可能为5,可能不为5，
		{
			if (num[len - 1] != 5)//如果不为5就从右到左找到5然后移位让尾数为5；
			{
				for (i = len - 2; i >= 0; i--)
				{
					if (flag[5] != 0)
					{
						if (num[i] == 5)
						{
							del(num, i, len);
							num[len - 1] = 5;
							break;
						}
					}
				}
			}
			if (sum % 3 == 0)
			{
				print(num, len);
				memset(ch, '0', sizeof(strlen(ch)));
				memset(num, 0, sizeof(num));
				continue;
			}
			else if (sum % 3 == 1)//和整除3余1有1，4，7三种可能情况
			{
				for (i = len - 2; i >= 0; i--)
				{
					if (flag[1] != 0 && num[i] == 1)//删除1
					{
						del(num, i, len);
						break;
					}
					else if (flag[4] != 0 && num[i] == 4)//删除4
					{
						del(num, i, len);
						break;
					}
					else if (flag[7] != 0 && num[i] == 7)//删除7
					{
						del(num, i, len);
						break;
					}
					else if (flag[1] == 0 && flag[4] == 0 && flag[7] == 0)
					{
						if (delonetwochar(num, i, len, flag) == 1)
						{
							if (num[0] == 0) { num[0] = 0; break; }
							else if (i == 0)
							{
								printone(); tag = 1; break;
							}

						}
						else
						{
							count++; if (count == 2) { len--; break; }
						}
					}
				}
			}
			else if (sum % 3 == 2)
			{
				for (i = len - 2; i >= 0; i--)
				{
					if (flag[2] != 0 && num[i] == 2)//删除2
					{
						del(num, i, len);
						break;
					}
					else if (flag[5] != 0 && num[i] == 5)//删除5
					{
						del(num, i, len);
						break;
					}
					else if (flag[8] != 0 && num[i] == 8)//删除8
					{
						del(num, i, len);
						break;
					}
					else if (flag[2] == 0 && flag[5] == 1 && flag[8] == 0)
					{
						if (deltwotwochar(num, i, len, flag) == 1)
						{
							if (i == 0) { printone(); tag = 1; break; }
						}
						else
						{
							count++; if (count == 2) { len--; break; }
						}
					}
				}
			}
			if (tag == 1)continue;
			len--;
			if (num[0] == 0) { cout << "0" << endl; continue; }
			if (len < 2) { printone(); continue; }
			print(num, len);
		}
		memset(ch, '0', sizeof(strlen(ch)));
		memset(num, 0, sizeof(num));
	}
	system("pause");
	return 0;
}