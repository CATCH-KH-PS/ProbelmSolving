#include <iostream>
#include <vector>
#include <stdio.h>

using namespace std;
vector<vector<int>> sudoku(9, vector<int>(9, 0));
bool flag = false;

bool checkRow(int row, int idx)
{
  for (int i = 0; i < 9; i++)
  {
    if (sudoku[row][i] == 0)
      continue;
    if (sudoku[row][i] == idx)
      return false;
  }
  return true;
}

bool checkCol(int col, int idx)
{
  for (int i = 0; i < 9; i++)
  {
    if (sudoku[i][col] == 0)
      continue;
    if (sudoku[i][col] == idx)
      return false;
  }
  return true;
}

bool checkBox(int row, int col, int idx)
{
  int rowB = (row / 3) * 3;
  int colB = (col / 3) * 3;
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      if (sudoku[rowB + i][colB + j] == 0)
        continue;

      if (sudoku[rowB + i][colB + j] == idx)
        return false;
    }
  }
  return true;
}

void BackTracking(int row, int col)
{
  if (flag)
    return;

  if (col > 8)
  {
    if (row + 1 > 8)
    {
      for (int i = 0; i < 9; i++)
      {
        for (int j = 0; j < 9; j++)
        {
          printf("%d", sudoku[i][j]);
        }
        printf("\n");
      }
      flag = true;
    }
    BackTracking(row + 1, 0);
    return;
  }

  //printf("row: %d col: %d\n", row, col);
  if (sudoku[row][col] != 0)
  {
    BackTracking(row, col + 1);
    return;
  }

  for (int i = 1; i < 10; i++)
  {
    if (checkRow(row, i) && checkCol(col, i) && checkBox(row, col, i))
    {
      sudoku[row][col] = i;
      //printf("[%d][%d] = %d \n", row, col, i);
      BackTracking(row, col + 1);
      sudoku[row][col] = 0;
    }
  }
}
int main(void)
{

  char row[9];
  for (int i = 0; i < 9; i++)
  {
    scanf("%s", row);
    for (int j = 0; j < 9; j++)
    {
      int tmp = row[j] - '0';
      sudoku[i][j] = tmp;
    }
  }

  BackTracking(0, 0);

  return 0;
}