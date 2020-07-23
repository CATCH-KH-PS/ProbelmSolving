/*
- knapsack 알고리즘 사용
- cost 오름차순 cost가 같다면 mem 내림차순 정렬
- cost를 기준으로 최대 메모리를 계산합니다. (cost가 weight 역할을 합니다.)
- 최대 메모리가 주어진 메모리보다 같거나 크면 cost를 리턴합니다. 
*/

/*
(0,10) (3,30) (3,20) (4,40) (5,35) 
0   3   4   5   6   7   8 
10  10  10  10  10  10  10
10  40  40  40  40
10  40  40  40  60 ..
10  40  40  40  60  80
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>

using namespace std;
int n, m;
vector<pair<int, int>> knapsack;

int dp[100][10001] = {
    0,
};

bool cmp(const pair<int, int> &a, const pair<int, int> &b)
{
  if (a.second == b.second)
  {
    return a.first > b.first;
  }
  return a.second < b.second;
}

int main(void)
{
  scanf("%d %d", &n, &m);

  //입력
  int mem, cost;
  int answer = 100000001;
  for (int i = 0; i < n; i++)
  {
    scanf("%d", &mem);
    knapsack.push_back(make_pair(mem, 0));
  }

  for (int i = 0; i < n; i++)
  {
    scanf("%d", &cost);
    knapsack[i].second = cost;
  }

  sort(knapsack.begin(), knapsack.end(), cmp);

  int end = knapsack[n - 1].second;

  for (int i = 0; i < n; i++) // i is iteration
  {
    int tmp_mem = knapsack[i].first;
    int tmp_cost = knapsack[i].second;
    for (int j = 0; j < end * n + 1; j++) //j is cost
    {
      if (i == 0)
      {
        if (j >= tmp_cost)
        {
          dp[i][j] = tmp_mem;
        }
      }
      else
      {
        if (j < tmp_cost)
        {
          dp[i][j] = dp[i - 1][j];
        }
        else
        {
          dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - tmp_cost] + tmp_mem);
        }
      }

      if (dp[i][j] >= m && j < answer)
      {
        answer = j;
      }
    }
  }
  printf("%d\n", answer);
  return 0;
}