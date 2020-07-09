#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int check[30][30] = {
    0,
};

int BFS(vector<string> board, int row, int col, char first)
{

  int answer = 0;

  int x[3] = {1, 0, 1};
  int y[3] = {0, 1, 1};

  for (int i = 0; i < 3; i++)
  {

    if (row + x[i] >= board.size() || col + y[i] >= board[0].size())
    {
      return 0;
    }

    if (board[row + x[i]][col + y[i]] != first)
    {
      return 0;
    }
  }

  if (check[row][col] == 0)
  {
    check[row][col] = 1;
    answer++;
  }

  for (int i = 0; i < 3; i++)
  {
    if (check[row + x[i]][col + y[i]] == 0)
    {
      check[row + x[i]][col + y[i]] = 1;
      answer++;
    }
  }
  return answer;
}

int solution(int m, int n, vector<string> board)
{
  int answer = 0;
  int i, j, tmp_flag;

  while (1)
  {
    tmp_flag = 0;
    memset(check, 0, sizeof(check));
    for (i = 0; i < board.size(); i++)
    {
      for (j = 0; j < board[0].size(); j++)
      {
        char first;
        first = board[i][j];
        if (first == ' ')
        {
          continue;
        }
        tmp_flag += BFS(board, i, j, first);
      }
    }

    if (tmp_flag == 0)
    {
      break;
    }
    answer += tmp_flag;

    for (i = 0; i < board.size(); i++)
    {
      for (j = 0; j < board[0].size(); j++)
      {

        if (check[i][j] == 1)
        {
          board[i][j] = ' ';
        }
      }
    }

    for (i = board.size() - 1; i > 0; i--)
    {
      for (j = 0; j < board[0].size(); j++)
      {
        if (board[i][j] == ' ')
        {
          for (int row = i - 1; row > -1; row--)
          {
            if (board[row][j] != ' ')
            {
              swap(board[row][j], board[i][j]);
              break;
            }
          }
        }
      }
    }
  }

  return answer;
}

int main(void)
{
  int n, m;
  vector<string> board;

  //cin >> m >> n;

  for (int i = 0; i < 30; i++)
  {
    string row = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
    board.push_back(row);
  }

  cout << solution(m, n, board);

  return 0;
}