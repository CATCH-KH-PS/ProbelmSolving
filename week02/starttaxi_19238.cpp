/*
최단 경로 사용하기 bfs
1. 승객수 m만큼 루프를 돕니다.
2. 각 루프마다 택시와 승객 사이의 최단 거리를 체크해서 승객을 선택합니다.
3. 선택한 승객까지 연료양을 체크합니다.
4. 도착지까지 연료양을 체크합니다.
5. 도착지까지 연료양이 충분하다면 택시의 위치 = 승객 도착 위치
2 로 가서 반복
*/
#include <iostream>
#include <vector>
#include <queue>
#include <stdio.h>
#include <string.h>

using namespace std;
int n, m, fuel; // n*n map, m명의 승객
int taxi_x, taxi_y;

int map[20][20] = {
    0,
};
int copy_map[20][20] = {
    0,
};

vector<pair<int, int>> one_vector; //copy_map을 복사하기 위한 일시적인 정보
int list[400][4];                  //손님 정보
bool check_list[400];              //이미 태운 손님인지

int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

bool isValid(int row, int col)
{
  if (row < 0 || col < 0 || row >= n || col >= n)
  {
    return false;
  }
  return true;
}

//최단거리를 리턴합니다. limit거리안에 가지 못하면 -1을 return 합니다.
//아예 도달하지 못할 경우 -2 return
int BFS(int s_x, int s_y, int e_x, int e_y, int limit)
{
  queue<pair<int, int>> q;

  q.push(make_pair(s_x, s_y));

  //출발지와 목적지가 동일하다.
  if (s_x == e_x && s_y == e_y)
  {
    return 0;
  }

  while (!q.empty())
  {
    int cur_x = q.front().first;
    int cur_y = q.front().second;
    q.pop();

    for (int i = 0; i < 4; i++)
    {
      int next_x = cur_x + dx[i];
      int next_y = cur_y + dy[i];

      if (isValid(next_x, next_y) && copy_map[next_x][next_y] == 0 &&
          !(next_x == s_x && next_y == s_y))
      {
        q.push(make_pair(next_x, next_y));
        copy_map[next_x][next_y] = copy_map[cur_x][cur_y] + 1;

        if (copy_map[next_x][next_y] > limit)
        {
          return -1;
        }

        if (next_x == e_x && next_y == e_y)
        {
          return copy_map[next_x][next_y];
        }
      }
    }
  }
  return -2;
}

int main(void)
{
  scanf("%d %d %d", &n, &m, &fuel);

  int tmp_one;
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      scanf("%d", &tmp_one);
      if (tmp_one == 1)
      {
        one_vector.push_back(make_pair(i, j));
      }
    }
  }
  scanf("%d %d", &taxi_x, &taxi_y);
  for (int i = 0; i < m; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      scanf("%d", &list[i][j]);
    }
    check_list[i] = false;
  }

  for (int i = 0; i < m; i++)
  {
    int start_i = 0, tmp_x = m, tmp_y = m;
    //최소 거리 초기화
    int min_len = 500;

    for (int j = 0; j < m; j++)
    {

      if (check_list[j] == true)
      {
        continue;
      }
      //map복사본 만들기
      memset(copy_map, 0, sizeof(copy_map));
      for (int k = 0; k < one_vector.size(); k++)
      {
        copy_map[one_vector[k].first][one_vector[k].second] = -1;
      }

      //택시에서 승객까지 최단 거리 구하기
      int tmp = BFS(taxi_x - 1, taxi_y - 1, list[j][0] - 1, list[j][1] - 1, fuel);

      //갈수 없음
      if (tmp == -2)
      {
        min_len = 500;
        break;
      }

      //최단 거리를 업데이트 합니다.
      if (tmp < min_len && tmp > -1)
      {
        min_len = tmp;
        start_i = j;
        tmp_x = list[j][0];
        tmp_y = list[j][1];
      }

      //거리가 동일하다면
      //1. row를 비교합니다.
      //2. row가 동일하다면 col을 비교합니다.
      if (tmp == min_len)
      {
        if (tmp_x > list[j][0] || (tmp_x == list[j][0] && tmp_y > list[j][1]))
        {
          start_i = j;
          tmp_x = list[j][0];
          tmp_y = list[j][1];
        }
      }
    }

    //승객을 전부 태우기 불가능이라면 -1 리턴
    if (min_len == 500)
    {
      printf("-1\n");
      return 0;
    }

    //누군가를 태웠다.
    check_list[start_i] = true;
    printf("%dth person is taking taxi\n", start_i + 1);
    //맵초기화
    memset(copy_map, 0, sizeof(copy_map));
    for (int k = 0; k < one_vector.size(); k++)
    {
      copy_map[one_vector[k].first][one_vector[k].second] = 1;
    }
    fuel -= min_len;

    printf("taxi run %d left fuel %d\n", min_len, fuel);
    int dist = BFS(list[start_i][0] - 1, list[start_i][1] - 1, list[start_i][2] - 1, list[start_i][3] - 1, fuel);

    //연료가 모자르거나 도착 불가능이면
    if (dist < 0)
    {
      printf("-1\n");
      return 0;
    }
    printf("(%d, %d) to (%d, %d)\n", list[start_i][0], list[start_i][1], list[start_i][2], list[start_i][3]);

    for (int k = 0; k < n; k++)
    {
      for (int q = 0; q < n; q++)
      {
        printf("%d ", copy_map[k][q]);
      }
      printf("\n");
    }
    printf("distance is %d\n", dist);

    //목적지까지 가능하다면 2배
    fuel += dist;

    //택시는 승객의 도착지점
    taxi_x = list[start_i][2];
    taxi_y = list[start_i][3];
  }

  printf("%d\n", fuel);
  return 0;
}