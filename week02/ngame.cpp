#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

char ALPHA[6] = {'A', 'B', 'C', 'D', 'E', 'F'};

string makeString(int n, int length)
{
  string str = "";

  for (int i = 0;; i++)
  {
    string tmpstr = "";
    //n진법으로 전환합니다.
    int rest = 0;
    int tmp = i;
    do
    {
      rest = tmp % n;
      if (rest > 9)
      {
        tmpstr += ALPHA[rest - 10];
      }
      else
      {
        tmpstr += to_string(rest);
      }
      tmp = tmp / n;
    } while (tmp != 0);
    reverse(tmpstr.begin(), tmpstr.end());
    str += tmpstr;
    if (str.length() >= length)
    {
      break;
    }
  }
  return str;
}

string solution(int n, int t, int m, int p)
{
  string answer = "";
  int length = m * (t - 1) + p;

  string full = "";
  full = makeString(n, length);

  for (int i = 0; answer.length() != t; i = i + m)
  {
    char tube = full[i + p - 1];
    answer += tube;
  }
  return answer;
}
