//코너와 직선 도로 정보를 저장하는 bfs
#include <string>
#include <vector>
#include <queue>
#include <tuple>
#include <limits.h>

using namespace std;

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
int n;
int min_pay = INT_MAX;

int copy_board[25][25][2] = {
    0,
}; // 0은 직선도로, 1은 코너

bool isValid(int row, int col)
{
  if (row < 0 || col < 0 || row > n - 1 || col > n - 1)
  {
    return false;
  }
  return true;
}

void print(void)
{
  printf("zero\n");
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      printf("%5d  ", copy_board[i][j][0]);
    }
    printf("\n");
  }
  printf("one\n");
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      printf("%5d  ", copy_board[i][j][0]);
    }
    printf("\n");
  }
  printf("\n");
}

void BFS(vector<vector<int>> board)
{
  queue<tuple<int, int, int, int>> q;
  //row, col, 방향 저장: 상하 0 좌우 1
  q.push(make_tuple(0, 0, 3, 0));
  int tmp_pay = 0;

  while (!q.empty())
  {
    int cur_x = get<0>(q.front());
    int cur_y = get<1>(q.front());
    int cur_dir = get<2>(q.front());
    int cur_state = get<3>(q.front());
    q.pop();

    for (int i = 0; i < 4; i++)
    {
      int next_x = cur_x + dx[i];
      int next_y = cur_y + dy[i];
      int next_dir;
      int next_state;

      if (!isValid(next_x, next_y) || (next_x == 0 && next_y == 0))
      {
        continue;
      }
      next_dir = i / 2; //방향 설정
      if (cur_dir == 3)
      {
        next_state = 0;
      }
      else
      {
        if (cur_dir == next_dir)
        {
          next_state = 0;
        }
        else
        {
          next_state = 1;
        }
      }

      if (board[next_x][next_y] == 0)
      {
        int tmp;
        if (next_state == 1)
        {
          tmp = copy_board[cur_x][cur_y][cur_state] + 600;
        }
        else
        {
          tmp = copy_board[cur_x][cur_y][cur_state] + 100;
        }

        if (copy_board[next_x][next_y][next_state] > tmp || copy_board[next_x][next_y][next_state] == 0)
        {
          copy_board[next_x][next_y][next_state] = tmp;
          q.push(make_tuple(next_x, next_y, next_dir, next_state));
        }
      }

      if (next_x == n - 1 && next_y == n - 1)
      {
        if (copy_board[next_x][next_y][next_state] < min_pay)
        {
          min_pay = copy_board[next_x][next_y][next_state];
          print(); //debugging
          return;
        }
      }
    }
  }
}

int solution(vector<vector<int>> board)
{
  int answer = 0;
  n = board.size();

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      if (board[i][j] == 1)
      {
        copy_board[i][j][0] = -1;
        copy_board[i][j][1] = -1;
      }
    }
  }

  BFS(board);
  answer = min_pay;
  return answer;
}

int main(void)
{

  vector<vector<int>> board = {{0, 0, 0, 0, 0, 0},
                               {0, 1, 1, 1, 1, 0},
                               {0, 0, 1, 0, 0, 0},
                               {1, 0, 0, 1, 0, 1},
                               {0, 1, 0, 0, 0, 1},
                               {0, 0, 0, 0, 0, 0}};
  solution(board);

  return 0;
}