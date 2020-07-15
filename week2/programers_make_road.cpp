#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <string.h>
#include <queue>
#include <set>

using namespace std;
//상 하 좌 우
int move_row[4] = {1,-1,0,0};
int move_col[4] = {0,0,-1,1}; 

struct data{
	pair<int,int> pos;
	int before;
	int value;
};

int bfs(vector<vector<int>>& board){
	pair<int,int> pos;
	int N = board.size();
	queue<data> q;
	data cur ={make_pair(0,0), -1,0};
	q.push(cur);
	while(!q.empty()){
		cur = q.front();
		q.pop();
		for(int i = 0 ; i < 4; i++){
			pair<int,int> next = make_pair(cur.pos.first + move_row[i], cur.pos.second + move_col[i]);
			if(next.first < 0 || next.first >= N || next.second < 0 || next.second >= N || board[next.first][next.second] == 1) continue; //범위를 벗어나거나 벽인경우 
			if((cur.before == 0 && i ==1) || (cur.before == 1 && i ==0) || (cur.before == 2 && i ==3) || (cur.before == 3 && i ==2)) continue; // 왔던 길을 되돌아 가는 경우
			data n;
			n.before = i;
			n.value = cur.value;
			if(((cur.before == 0 || cur.before == 1) && (i == 2 || i == 3)) || ((cur.before == 2 || cur.before == 3) && (i == 0 || i == 1))) n.value +=600;
			else n.value += 100;
			if(board[next.first][next.second] != 0 && board[next.first][next.second] < n.value) continue; //다음 좌표의 최단경로가 이미 존재하는 경우
			board[next.first][next.second] = n.value;
			n.pos = next;
			q.push(n);
		}
	}
	return board[N-1][N-1];
}


int solution(vector<vector<int>> board) {
    int answer = bfs(board);
    return answer;
}
