#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string.h>

int board[1000][1000];
bool visit[1000][1000];
bool visitB[1000][1000];
using namespace std;

int move_row[4] = {0,0,-1,1}; //상,하, 좌, 우
int move_col[4] = {-1,1,0,0}; //상,하, 좌, 우

struct pos{
	int row;
	int col;
	bool break_wall;
	int dist;
};

int main(void){
	int N,M;
	cin>>N>>M;
	string line;
	for(int i = 0 ; i < N ; i++){
		cin>>line;
		for(int j = 0 ; j < M ; j++){
			board[i][j] = line[j] - '0';
		}
	}
	memset(visit,0,sizeof(visit));
	memset(visitB,0,sizeof(visit));
	pos start = {0,0,0,1};
	visit[0][0] = 1;
	visitB[0][0] = 1;
	queue<pos> q;
	q.push(start);
	while(!q.empty()){
		pos front = q.front();
		q.pop();
		if(front.row == N -1 && front.col == M -1){
			cout<<front.dist<<endl;
			return 0;
		}
		front.dist++;
		for(int i = 0 ; i < 4 ; i++){
			if(front.row + move_row[i] < 0 || front.col + move_col[i] < 0 || front.row + move_row[i] >= N || front.col + move_col[i] >= M) continue;
			pos next = front;
			next.row += move_row[i];
			next.col += move_col[i];
			
			if(next.break_wall == false){
				if(visit[next.row][next.col] != 0 ) continue;
				else visit[next.row][next.col] = 1;
			}
			else {
				if(visitB[next.row][next.col] != 0) continue;
				else visitB[next.row][next.col] = 1;
			}
						
			if(board[next.row][next.col] == 0) q.push(next);
			else if(board[next.row][next.col] == 1 && next.break_wall == false){
				next.break_wall = true;
				q.push(next);
			}
		}
	}
	cout<<"-1"<<endl;
}
