/*
설명
- fish에 물고기의 좌표, 방향을 저장 (순서대로)
- map에 물고기의 인덱스를 저장, 상어는 -1로 저장
- dfs로 상어가 각 지점으로 갔을 때를 나눠서 실행 

1. 물고기가 이동
2. 상어가 갈 수 있는 지점(먹을 수 있는 물고기가 있는 곳)들 별로 dfs 실행 
3. 먹으면 계속 dfs 실행 , 못먹으면 지금까지 먹은 물고기 cnt 리턴 

*/




#include <string>
#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>
#include <tuple>

using namespace std;
int n = 4;
int dx[] = { -1, -1, 0, 1, 1, 1, 0, -1 }; // 여덟방향 0~ 7까지 
int dy[] = { 0, -1, -1, -1, 0, 1, 1, 1 };

pair<vector<vector<int>>, vector<tuple<int, int, int>>> f_move(vector<vector<int>> map, vector<tuple<int, int, int>> fish) { // 물고기가 이동하는 함수, map과 fish 물고기의 정보를 리턴한다. 
	for (int i = 1; i <= 16; i++) {  // 1번 물고기부터 순서대로 움직임
		int x, y, dir;
		tie(x, y, dir) = fish[i];
		if (x == -1) continue;  // 잡아먹힌 물고기는 -1로 표현되어 continue;
		while (true) {
			int nx = x + dx[dir];
			int ny = y + dy[dir];
			if (nx >= 0 && nx < n && ny >= 0 && ny < n && map[nx][ny] != -1) { // 이동이 가능하면
				if (map[nx][ny] == 0) { // 빈칸으로 이동시
					map[nx][ny] = i;   // map 변경
					fish[i] = make_tuple(nx, ny, dir);  // 물고기 정보 변경
					map[x][y] = 0;
				}
				else {  // 다른 물고기와 자리 변경
					int ano_fish = map[nx][ny];
					int ano_dir;
					tie(nx, ny, ano_dir) = fish[ano_fish];
					map[nx][ny] = i;
					map[x][y] = ano_fish;
					fish[i] = make_tuple(nx, ny, dir);
					fish[ano_fish] = make_tuple(x, y, ano_dir);
				}
				break;
			}
			else {  // 이동 불가시 45도 회전
				dir += 1;
				if (dir == 8) dir = 0;
			}
		}
	}
	return make_pair(map, fish);
}

int dfs(int sh_x, int sh_y, int sh_dir, vector<tuple<int, int, int>> fish_xy, vector<vector<int>> map, int cnt) {  // 상어의 정보와 물고기 정보, 맵 정보, 현재까지 먹은 물고기들의 정보를 가지고 실행
	vector<vector<int>> map2;  // 물고기 이동 후의 맵 정보를 담기 위해
	vector<tuple<int, int, int>> fish_xy2;  // 물고기 이동 후의 물고기 정보를 담기 위해 
	tie(map2, fish_xy2) = f_move(map, fish_xy);   // 이동한 정보를 저장
	bool ok = false;  // 상어가 움직일 수 있는지 없는지 나타내는 (dfs 종료 조건)
	int ans = -1;
	int nx = sh_x;
	int ny = sh_y;
	while (true) {
		nx += dx[sh_dir];  // 이것때문에 많이 틀림 원래는 x = nx로 해서 햇는데 그럼 이전의 움직인 곳은 빈곳이 되기 때문에 
		ny += dy[sh_dir];  // 방향으로 움직이면서 먹을 수 있는 곳 탐색
		if (nx < 0 || nx >= n || ny < 0 || ny >= n) break;  
		if (map2[nx][ny] == 0) continue; 
		int f_num = map2[nx][ny];  // 물고기 index
		int f_dir;
		tie(nx, ny, f_dir) = fish_xy2[f_num];  // 물고기 정보
		map2[nx][ny] = -1;
		map2[sh_x][sh_y] = 0;
		fish_xy2[f_num] = make_tuple(-1, -1, -1);  // 잡아먹힌것으로 정보 갱신 
		int temp = dfs(nx, ny, f_dir, fish_xy2, map2, cnt + f_num); // dfs 다시 돔
		if (ans == -1 || ans < temp) ans = temp;
		map2[sh_x][sh_y] = -1;
		map2[nx][ny] = f_num;
		fish_xy2[f_num] = make_tuple(nx, ny, f_dir);  // 다시 원상태로 복구 
		ok = true;  // 상어가 물고기를 먹었기 때문에 true 로 변경
	}
	if (!ok) return cnt;  // 상어가 아무 물고기도 못먹었으면 return
	return ans;
}


int main() {
	vector<tuple<int, int, int>> f_info(17);
	vector<vector<int>> map(n, vector<int>(4, 0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int a, b;
			cin >> a >> b;
			f_info[a] = make_tuple(i, j, b - 1);
			map[i][j] = a;
		}
	}
	int first_fish = map[0][0];
	int x, y, s_dir;
	tie(x, y, s_dir) = f_info[first_fish];
	f_info[first_fish] = make_tuple(-1, -1, -1);
	map[0][0] = -1;


	cout << dfs(0, 0, s_dir, f_info, map, first_fish);

	return 0;

}