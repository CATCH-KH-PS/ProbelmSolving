#include <string>
#include <vector>
#include <queue>

using namespace std;

struct info {
	int x;
	int y;
	int dir;
	int cost;
};

int dx[4] = { -1,1,0,0 };
int dy[4] = { 0,0,-1,1 };

int solution(vector<vector<int>> board) {
	int cost[30][30] = { 0, };
	int max_size = board.size();
	for (int i = 0; i < max_size; i++) {
		for (int j = 0; j < max_size; j++)
			cost[i][j] = 1999999999; //INF INITIALIZE
	}

	queue<info> Q;
	Q.push({ 0,0,0,0 });
	Q.push({ 0,0,1,0 });
	Q.push({ 0,0,2,0 });
	Q.push({ 0,0,3,0 });
	cost[0][0] = 0;

	while (!Q.empty()) {
		int now_x = Q.front().x;
		int now_y = Q.front().y;
		int now_dir = Q.front().dir;
		int now_cost = Q.front().cost;
		Q.pop();

		for (int d = 0; d < 4; d++) {
			int next_x = now_x + dx[d];
			int next_y = now_y + dy[d];
			int next_dir = d;
			int next_cost;
			now_dir == next_dir ? next_cost = now_cost + 100 : next_cost = now_cost + 600;


			if (next_x < 0 || next_x >= max_size || next_y < 0 || next_y >= max_size) { continue; }
			if (board[next_x][next_y] == 1) { continue; }
			if (cost[next_x][next_y] < next_cost) { continue; }

			cost[next_x][next_y] = next_cost;
			Q.push({ next_x,next_y,next_dir,next_cost });
		}
	}

	int answer = cost[max_size - 1][max_size - 1];
	return answer;
}