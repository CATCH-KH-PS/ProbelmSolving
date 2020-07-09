#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <string>
#include <set>

using namespace std;

int board[9][9];
bool isend;

void print(){
	for(int i = 0 ; i < 9 ; i++){
		for(int j = 0 ; j < 9 ; j++){
			cout<<board[i][j];
		}
		cout<<"\n";
	}
}


bool check_row(int row){
	int check[10] = {0,};
	for(int i = 0 ; i < 9 ; i++){
		if(board[row][i] == 0) continue;
		if(check[board[row][i]] == 0) check[board[row][i]] = 1;
		else return false;
	}
	return true;
}
bool check_col(int col){
	int check[10] = {0,};
	for(int i = 0 ; i < 9 ; i++){
		if(board[i][col] == 0) continue;
		if(check[board[i][col]] == 0) check[board[i][col]] = 1;
		else return false;
	}
	return true;	
}
bool check_squre(int row,int col){
	int check[10] = {0,};
	int row_start = row - row % 3;
	int col_start = col - col % 3;
	for(int i = 0 ; i < 3 ; i++){
		for(int j = 0 ; j < 3 ; j++){
			if(board[row_start + i][col_start + j] == 0) continue;
			if(check[board[row_start + i][col_start + j]] == 0) check[board[row_start + i][col_start + j]] = 1;
			else return false;
		}
	}
	return true;
}

void dfs(deque<pair<int,int>> &pos){
	if(pos.size() == 0){
		isend = true;
		print();
		return;
	}
	for(int i = 1 ; i <= 9 ; i++){
		int row = pos.front().first;
		int col = pos.front().second;
		pos.pop_front();
		board[row][col] = i;
		if(check_row(row) && check_col(col) && check_squre(row,col)) dfs(pos);
		if(isend == true) return;
		board[row][col] = 0;
		pos.push_front(make_pair(row,col));
	}
}

int main(void){
	string line;
	isend = false;
	deque<pair<int,int>> pos;
	for(int i = 0 ; i < 9 ; i++){
		cin>>line;
		for(int j = 0 ; j < 9 ; j++){
			board[i][j] = line[j] - '0';
			if(board[i][j] == 0) pos.push_back(make_pair(i,j));
		}
	}
	dfs(pos);
}


