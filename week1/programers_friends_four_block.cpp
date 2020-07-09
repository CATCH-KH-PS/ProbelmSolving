#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int move_row[4] = {0,0,1,1}; //자신 우 하 대각선
int move_col[4] = {0,1,0,1}; //자신 우 하 대각선

//블록 검사, 4개가 같은경우 ture 그 외 false
bool isright(int row, int col, int m, int n, vector<string>& board){
	int block[4];
	for(int i = 0 ; i < 4 ; i++){
		int r = row + move_row[i];
		int c = col + move_col[i];
		if(r < 0 || r >= m || c < 0 || c >= n) return false;
		if(board[r][c] == -1) return false;
		block[i] = board[r][c];
	}
	//4개 블록 각각 비교 대신 sort 사용
	sort(block, block+4);
	if(block[0] == block[3]) return true;
	return false;
}

//row,col을 기준으로 4블록 제거, 제거한 블록 수 return
int clear_block(int row, int col, vector<string>& board){
	int count = 0;
	for(int i = 0 ; i < 4 ; i++){
		int r = row + move_row[i];
		int c = col + move_col[i];
		if(board[r][c] != -1) count++;
		board[r][c] = -1;
	}
	return count;
}

//모든 블록 검사 및 같은 4블록 제거, 제거한 블록 수 return
int serch(int m, int n, vector<string>& board){
	int sum = 0;
	vector<pair<int,int>> blocks;
	for(int i = 0 ; i < m ; i++){
		for(int j = 0 ; j < n ; j++){
			if(isright(i, j, m, n, board)) blocks.push_back(make_pair(i, j));
		}
	}
	for(pair<int,int> p : blocks) sum += clear_block(p.first, p.second, board);
	return sum;
}

//제거한 블럭 보강
void fill(int m, int n, vector<string>& board){
	for(int col = 0 ; col < n ; col++){
		for(int row = m - 1 ; row >= 0 ; row--){
			int cnt = row;
			if(board[row][col] == -1){
				while(cnt > 0){
					cnt--;
					if(board[cnt][col] != -1) {
						board[row][col] = board[cnt][col]; 
						board[cnt][col] = -1; 
						break;
					}
				}
			}
		}
	}
}

int solution(int m, int n, vector<string> board) {
    int answer = 0;
    int cblock = 0;
    while((cblock = serch(m, n, board)) != 0){
		answer += cblock;
		fill(m, n, board);
	}
    return answer;
}

int main(void){
	vector<string> s = {"CCBDE", "AAADE", "AAABF", "CCBBF"};
	cout<<solution(4, 5,s);
}
