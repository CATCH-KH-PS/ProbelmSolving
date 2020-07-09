#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int solution(vector<string> words);
int main(void)
{
  vector<string> words;
  string tmp;
  int num;
  scanf("%d", &num);

  for (int i = 0; i < num; i++)
  {
    cin >> tmp;
    words.push_back(tmp);
  }
  cout << solution(words) << "\n";
  return 0;
}

int solution(vector<string> words)
{
  int answer = 0;
  bool flag;
  vector<int> dp(words.size()); //다른 문자열과 겹치는 길이를 저장합니다.

  sort(words.begin(), words.end());
  for (int i = 0; i < words.size(); i++)
  {
    int maxLen = dp[i];
    cout << "initial maxLen is " << maxLen << "\n";
    for (int j = dp[i] + 1; j < words[i].length() + 1; j++)
    {
      string sub = words[i].substr(0, j); //substring

      flag = false;
      for (int k = 0; k < words.size(); k++)
      {
        if (k == i)
        {
          continue;
        }

        string cmp = words[k].substr(0, j);

        if (sub.compare(cmp) == 0)
        {
          maxLen = j;
          dp[k] = j;
          flag = flag || true;
        }
      }

      //flag가 false면 최장 문자열. 더 이상 찾지 않는다.
      if (flag == false)
      {
        break;
      }
    }

    dp[i] = maxLen;
    if (flag == false)
    {
      maxLen++;
    }

    cout << "max len is " << maxLen << "\n";
    answer += maxLen;

    for (int k = 0; k < words.size(); k++)
    {
      cout << k << "th : " << dp[k] << "\n";
    }
  }
  return answer;
}