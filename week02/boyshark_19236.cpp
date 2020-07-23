//backtracking
//1. 상어가 들어와서 물고기를 먹는다. (0,0)
//2. 물고기가 이동한다.
//3. 상어가 물고기를 먹는다. -> 이동한다. -> 물고기 복구
//2,3 반복

#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>

using namespace std;

vector<vector<pair<int, int>>> space;

int max_answer = 0;
int dx[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dy[8] = {0, -1, -1, -1, 0, 1, 1, 1};

int live_fish[16] = {
    0,
};

bool is_outside(int row, int col)
{
  if (row < 0 || col < 0 || row > 3 || col > 3)
  {
    return true;
  }
  return false;
}

//물고기가 살아있다면 위치를 return
void find_fish(int num, int *x, int *y)
{
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      if (space[i][j].first == num)
      {
        *x = i;
        *y = j;
      }
    }
  }
}

void move_fish(int row, int col)
{
  for (int cnt = 1; cnt < 17; cnt++)
  {
    //물고기가 살아있나 체크
    if (live_fish[cnt - 1] == 1)
    {
      continue; //죽어 있으면 다음 물고기로
    }
    //물고기 위치 찾기
    int start_x = 0, start_y = 0;
    find_fish(cnt, &start_x, &start_y);

    //방향을 따라가서 자리 바꿀 물고기 위치 찾기
    int dir = space[start_x][start_y].second;

    int change_x, change_y;
    bool flag = false;
    for (int i = 0; i < 8; i++)
    {
      if (dir > 8)
        dir %= 8;
      change_x = start_x + dx[dir - 1];
      change_y = start_y + dy[dir - 1];

      //바깥으로 나가지 않고 상어가 없으면
      if (is_outside(change_x, change_y) || (change_x == row && change_y == col))
      {
        dir++;
      }
      else
      {
        flag = true;
        space[start_x][start_y].second = dir;
        break;
      }
    }

    //자리를 바꾼다.
    if (flag == true)
    {
      swap(space[start_x][start_y].first, space[change_x][change_y].first);
      swap(space[start_x][start_y].second, space[change_x][change_y].second);
    }
  }
}

void move_shark(int row, int col, int cnt, int answer)
{
  vector<vector<pair<int, int>>> copy;
  bool copy_live[16];

  //물고기를 전부 잡아 먹으면
  if (cnt >= 16)
  {
    max_answer = answer;
    return;
  }

  //물고기 이동
  move_fish(row, col);

  //물고기 이동 후 상태 저장
  for (int i = 0; i < 4; i++)
  {
    vector<pair<int, int>> tmp;
    for (int j = 0; j < 4; j++)
    {
      tmp.push_back(make_pair(space[i][j].first, space[i][j].second));
      copy_live[4 * i + j] = live_fish[4 * i + j];
    }
    copy.push_back(tmp);
  }

  //상어의 이동
  int shark_dir = space[row][col].second;
  bool flag = false;

  for (int i = 1; i < 4; i++)
  {
    int new_row = row + dx[shark_dir - 1] * i;
    int new_col = col + dy[shark_dir - 1] * i;

    //상어가 이동가능한 범위 안이면
    if (!is_outside(new_row, new_col))
    {
      int fish = space[new_row][new_col].first;

      //물고기가 없다면 정지
      if (fish == -1)
      {
        continue;
      }

      //물고기를 먹는다.
      space[new_row][new_col].first = -1;
      live_fish[fish - 1] = 1;
      //상어 위치 이동
      move_shark(new_row, new_col, cnt + 1, answer + fish);

      //백트레킹

      //물고기 이동 취소
      for (int j = 0; j < 4; j++)
      {
        for (int k = 0; k < 4; k++)
        {
          space[j][k].first = copy[j][k].first;
          space[j][k].second = copy[j][k].second;

          //물고기 살리기
          live_fish[4 * j + k] = copy_live[4 * j + k];
        }
      }

      flag = true;
    }
  }

  if (flag == false)
  {
    if (max_answer < answer)
    {
      max_answer = answer;
    }

    return;
  }
}

int main(void)
{
  int loc, dir;
  for (int i = 0; i < 4; i++)
  {
    vector<pair<int, int>> tmp;
    for (int j = 0; j < 4; j++)
    {
      scanf("%d %d", &loc, &dir);
      tmp.push_back(make_pair(loc, dir));
    }
    space.push_back(tmp);
  }

  //상어가 물고기를 먹는다.
  live_fish[space[0][0].first - 1] = 1;
  int answer = space[0][0].first;
  space[0][0].first = -1;

  move_shark(0, 0, 1, answer);

  printf("%d\n", max_answer);
  return 0;
}