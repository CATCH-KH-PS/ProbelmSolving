//floyd-warshall algorithm

#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;
int n, m;
int network[101][101] = {
    0,
};

int main(void)
{
  scanf("%d %d", &n, &m);

  for (int i = 0; i < m; i++)
  {
    int x, y;
    scanf("%d %d", &x, &y);
    network[x][y] = 1;
    network[y][x] = 1;
  }

  for (int i = 1; i < n + 1; i++)
  {
    for (int j = 1; j < n + 1; j++)
    {
      for (int k = 1; k < n + 1; k++)
      {
        if (i == j || i == k || j == k)
        {
          continue;
        }

        if (network[i][j] == 0)
        {
          if (network[i][k] == 1 && network[k][j] == 1)
          {
            network[i][j] = 1;
            network[j][i] = 1;
          }

          //1번컴퓨터에 대한 정보를 업데이트 합니다.
          if (network[1][k] && network[k][j])
          {
            network[1][j] = 1;
            network[j][1] = 1;
          }
        }
      }
    }
  }

  int answer = 0;
  for (int i = 2; i < n + 1; i++)
  {
    if (network[1][i] == 1)
    {
      answer++;
    }
  }
  printf("%d\n", answer);
  return 0;
}