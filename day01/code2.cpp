#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <vector>
#include <queue>
#include <memory.h>
#include <algorithm>
#include <iostream>
#include <stack>
#include <unordered_set>
#include <math.h>

using namespace std;

string board[9];

int dx[] = { 1,1,0,-1,-1,-1,0,1 }; //squre 검사용
int dy[] = { 0,1,1,1,0,-1,-1,-1 };

int check_h_line(int idx) // 수평선 체크
{
	int check[10] = { 0 };
	for (int i = 0; i < 9; i++)
	{
		if (check[(int)board[idx][i]] == 1)
			return (-1);
		if ((int)board[idx][i] != 0)
			check[(int)board[idx][i]] = 1;
	}
	return (0);
}

int check_v_line(int idx) // 수직선 체크
{
		int check[10] = { 0 };
		for (int j = 0; j < 9; j++)
		{
			if (check[(int)board[j][idx]] == 1)
				return (-1);
			if ((int)board[j][idx] != 0)
				check[(int)board[j][idx]] = 1;
		}	
	return (0);
}

void board_print()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
			cout << (int)board[i][j];
		if (i != 8)
		cout << "\n";
	}
}

int check_squre(int i_, int j_) // 3x3 사각형 체크
{

	int base_i = (i_ / 3) * 3 + 1; // y축 base (0,1,2  > 1), (3,4,5 > 4 ) , (6,7,8 > 7);
	int base_j = (j_ / 3) * 3 + 1; // x축 base (0,1,2  > 1), (3,4,5 > 4 ) , (6,7,8 > 7);
	int check[10] = { 0 };

	if ((int)board[base_i][base_j] != 0)
		check[(int)board[base_i][base_j]] = 1;
	for (int i = 0; i < 8; i++)
	{
		int ny = base_i + dy[i];
		int nx = base_j + dx[i];
		if (check[(int)board[ny][nx]] == 1)
			return (-1);
		if ((int)board[ny][nx] != 0)
			check[(int)board[ny][nx]] = 1;
	}
	return (0);
}

void find(int i_, int j_)
{
	if (j_ == 9)
	{
		if (i_ == 8) //전부 채워졌을경우
		{
			board_print();				//조건 부합시 출력후
			exit(0);	//프로그램 종료
		}
		j_ = 0;
		i_ += 1;
	}
	if (board[i_][j_] == 0) // 값이 주어지지 않은 경우
	{
		for (int n = 1; n <= 9; n++)
		{
			board[i_][j_] = n;
			if (check_v_line(j_) == -1 || check_h_line(i_) == -1 || check_squre(i_, j_) == -1) // 수직선 체크 ) // 수평선 체크// 2x2사각형 체크
			{
				board[i_][j_] = 0;
				continue;
			}
			find(i_, j_ + 1);
			board[i_][j_] = 0;
		}
	}
	else // 값이 주어진 경우
		find(i_, j_ + 1);
}
int	main(void)
{
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	freopen("input.txt", "r", stdin);
	
	for (int i = 0; i < 9; i++)
	{
		cin >> board[i];
		for (int j = 0; j < board[i].size(); j++)
			board[i][j] -= '0'; // 아스키코드 <> int값 보정
	}
	find(0, 0);
	return (0);
}