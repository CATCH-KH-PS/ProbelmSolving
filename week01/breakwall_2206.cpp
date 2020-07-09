#include <stdio.h>
#include <vector>
#include <queue>

using namespace std;

int map[1000][1000] = {
    0,
};
int path[1000][1000][2] = {
    0,
}; //0은 뚫지 않는 루트, 1은 벽뚫는 루트

int n, m;
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

int BFS(int row, int col);
int main(void)
{
  char tmp[1001];

  scanf("%d %d", &n, &m);

  for (int i = 0; i < n; i++)
  {
    scanf("%s", tmp);
    for (int j = 0; j < m; j++)
    {
      int num = tmp[j] - '0';
      map[i][j] = num;
    }
  }

  int res = BFS(0, 0);

  printf("%d\n", res);

  return 0;
}

bool isValid(int row, int col)
{
  if (row >= n || row < 0 || col >= m || col < 0)
  {
    return false;
  }
  return true;
}

int BFS(int row, int col)
{
  queue<pair<pair<int, int>, int>> q;
  q.push(make_pair(make_pair(row, col), 0));
  path[row][col][0] = 1; //패스 체크

  while (!q.empty())
  {
    int front_x = q.front().first.first;
    int front_y = q.front().first.second;
    int flag = q.front().second;

    q.pop();

    if (front_x == n - 1 && front_y == m - 1)
    {

      for (int i = 0; i < n; i++)
      {
        for (int j = 0; j < m; j++)
        {
          printf("%d ", path[i][j][1]);
        }
        printf("\n");
      }
      return path[front_x][front_y][flag];
    }

    for (int i = 0; i < 4; i++)
    {

      if (isValid(front_x + dx[i], front_y + dy[i]))
      {
        //벽이 없다면
        if (map[front_x + dx[i]][front_y + dy[i]] == 0 && path[front_x + dx[i]][front_y + dy[i]][flag] == 0)
        {
          q.push(make_pair(make_pair(front_x + dx[i], front_y + dy[i]), flag));
          path[front_x + dx[i]][front_y + dy[i]][flag] = path[front_x][front_y][flag] + 1;
        }

        //벽이 있다면
        if (map[front_x + dx[i]][front_y + dy[i]] == 1 && flag == 0)
        {
          q.push(make_pair(make_pair(front_x + dx[i], front_y + dy[i]), 1));
          path[front_x + dx[i]][front_y + dy[i]][1] = path[front_x][front_y][flag] + 1;
        }
      }
    }
  }

  return -1;
}