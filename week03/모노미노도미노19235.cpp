/*
구현문제인데 시간이 정말 많이 걸렸습니다.....
맵을 6*4로 통일 해주는 것이 키포인트 인것 같습니다. 64, 46으로 따로 짜면 코드가 
정말 복잡해 집니다...
이렇게 구현하는 것이 많을 때는 함수 하나 구현하고 실행해서 오류 제대로 시행되는지 확인하면서 진행하는 것이 좋은것 같습니다. 

자료형 
- mono[][][] 첫번째 인자가 0이면 아래 맵, 1이면 오른쪽 맵, 그리고 pair로 처음은 ind라는 수로 블럭에 index를 붙여 줬습니다. 
그리고 두번째 수는 같은 블럭에서 첫번째와 두번째블럭을 구분할 수 있도록 했습니다. 그리고 그것으로 이것이 t= 2인지 t=3인지 구분할 수 있도록 했습니다. 
- top[][] 각 맵에서 제일 위에 있는 블럭의 위치를 넣어놓았습니다. 
- score 점수 

함수 
1. rc_move : 블럭을 놓습니다. mono[0]은 그래도 놓으면 되고, mono[1]은 x와 y의 좌표를 바꿔주고, t =2이면 3으로 바꿔주면 동일한 로직으로 실행할 수 있습니다. 
2. remove : 행에 4개의 블럭이 있으면 지워주는 함수 입니다. return 값이 0이면 지워지는 것이 없는 것입니다. 
3. down : 블럭들을 내려주는 함수 입니다. (구현에 제일 오래 걸렸습니다. ), 자세한 설명은 함수에 주석으로...
4. check : 연한 칸에 블럭이 있는지 확인하는 함수입니다. 있으면 그 칸의 x좌표를 없으면 -1을 리턴합니다. 
5. check_t : 위의 4번 함수가 -1이 아닌 수를 반환하면 연한칸의 행 수 만큼 내려주는 함수입니다. 


*/

#include <string>
#include <vector>
#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>
#include <set>
#include <tuple>
using namespace std;
int n;
pair<int, int> mono[2][6][4];
int top[2][4];  // 열별로 가장 높은 블럭
int score = 0;
int ind = 1;

void rc_move(int k, int t, int x, int y) { // 블럭을 처음에 놓아주는 함수 
	for (int j = 0; j < 4; j++) {  // 맨 위의 블럭이 어디 있는지 찾는 부분
		top[k][j] = 6;  
		for (int i = 0; i < 6; i++) {
			if (mono[k][i][j].first != 0) {
				top[k][j] = i;
				break;
			}
		}
	}

	if (k == 1) {  // 맵이 오른쪽의 맵이면 x와 y를 바꿔주고, t =2이면 3으로 3이면 2로 바꿔주면 됩니다. 
		swap(x, y);
		if (t != 1) {
			t = 5 - t;
		}
	}
	if (t == 1) {  // 한칸짜리이면 
		int top_num = top[k][y]-1; // 가장 높이 있는 블럭 바로 위에 쌓는다. 
		mono[k][top_num][y] = make_pair(ind, 0);  // 0은 1개짜리 블럭을 나타냅니다. 
		top[k][y] -= 1;   // 가장 높이 있는 블럭정보를  갱신
	}
	else if (t == 2) {  // 두개짜리이면   map에 두번째 인자에 1과 2로 저장합니다. 
		int top_num = min(top[k][y], top[k][y + 1]) - 1;  // 두 열의 가장 높이 있는 블럭을 비교해 더 높은 곳의 위에 블럭을 쌓는다. 
		mono[k][top_num][y] = make_pair(ind, 1);  
		mono[k][top_num][y + 1] = make_pair(ind, 2);
		top[k][y] = top_num;
		top[k][y + 1] = top_num;
	}
	else if (t == 3) {  // map의 2번째 인자에 3과 4로 표시하여 세로로 쌓여있음을 나타냅니다. 
		int top_num = top[k][y] - 1;
		mono[k][top_num][y] = make_pair(ind, 3);
		mono[k][top_num - 1][y] = make_pair(ind, 4);
		top[k][y] = top_num - 1;
	}
	ind += 1;  // ind는 블럭들을 구분해주는 인자입니다. 
}

int remove(int k) {  // 4개가 쌓인 행이 있으면 제거해주는 함수 
	int ans = 0;
	for (int i = 2; i < 6; i++) {
		int cnt = 0;
		for (int j = 0; j < 4; j++) {
			if (mono[k][i][j].first != 0) cnt += 1;
		}
		if (cnt == 4) {
			ans += 1;
			for (int j = 0; j < 4; j++) {
				mono[k][i][j] = make_pair(0, 0);
			}
		}
	}
	score += ans;  // 제거된 행만큼 점수에 더해줍니다. 
	return ans;
}

void down(int k) {  // 맨 아래 부터 검사합니다. 
	int temp[4] = { 5, 5, 5, 5 };   // 놓을 수 있는 x 좌표
	for (int i = 5; i >= 0; i--) {
		for (int j = 0; j < 4; j++) {
			if (mono[k][i][j].first == 0) { // 블럭이 없으면 지나칩니다. 
				continue;
			}
			else {
				int x, y;
				tie(x, y) = mono[k][i][j];  // x 는 블럭 index, y 는 블럭의 정보 0 : 1칸짜리, 1은 가로로 쌓인거 중 첫번째(그러나 2는 없을지도 모름)
											// 2 : 가로로 쌓인것중 2번째 (1있는지 확인하고 있으면 처리 x ), 없으면 처리하고 y를 0으로 저장  3, 4 도 같은 원리
				if (y == 2 ) {
					if (j-1 >=0 && mono[k][i][j - 1].first == x) continue;  // 1인 것이 잇으면 1에서 내려주는 처리 하기 때문에 굳이 필요 x
					
					y = 0;  // 1인 블럭이 지워졌으면 1칸짜리처럼 처리해야함 
				}
				if (y == 4) {   // 2일때와 마찬가지 
					if (i+1 < 6 && mono[k][i+1][j].first == x) continue;
					
					y = 0;
				}
				
				if (y == 0) {  // 1칸짜리면 temp(샇을 수 있는 곳에 쌓는다. 
					
					mono[k][i][j] = make_pair(0, 0);
					mono[k][temp[j]][j] = make_pair(x, 0);
					temp[j] -= 1;
				}
				else if (y == 1) {
					if (mono[k][i][j].first == mono[k][i][j + 1].first) {  // 1인데 2인 칸이 있을 때
						int top_lo = min(temp[j], temp[j + 1]);
						mono[k][i][j] = make_pair(0, 0);
						mono[k][i][j + 1] = make_pair(0, 0);
						mono[k][top_lo][j] = make_pair(x, 1);
						mono[k][top_lo][j + 1] = make_pair(x, 2);
						temp[j] = top_lo - 1;
						temp[j + 1] = top_lo - 1;
					}
					else {											// 1인데 2인 칸이 없을 때 (remove나 여러가지 과정에서 지워질 수 있음
						mono[k][i][j] = make_pair(0, 0);
						mono[k][temp[j]][j] = make_pair(x, 0);
						temp[j] -= 1;
					}
				}
				else if (y == 3) {												// 3일 때도 1일 때와 동일
					if (mono[k][i][j].first == mono[k][i - 1][j].first) {
						mono[k][i][j] = make_pair(0, 0);
						mono[k][i - 1][j] = make_pair(0, 0);
						mono[k][temp[j]][j] = make_pair(x, 3);
						mono[k][temp[j] - 1][j] = make_pair(x, 4);
						temp[j] -= 2;
					}
					else {
						mono[k][i][j] = make_pair(0, 0);
						mono[k][temp[j]][j] = make_pair(x, 0);
						temp[j] -= 1;
					}
				}
			}
		}
	}
	return;
}

int check(int k) {								// 연한 칸에 있으면 그 최상단 좌표를 리턴
	int ans = -1;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			if (mono[k][i][j].first != 0) {
				return i;
			}
		}
	}
	return ans;
}

void check_t(int k, int num) {					// 좌표가 0이면 2칸 내리기, 2이면 1칸 내리기 
	int do_num = 2 - num;
	for (int i = 5 - do_num; i >= num; i--) {
		for (int j = 0; j < 4; j++) {
			mono[k][i + do_num][j] = mono[k][i][j];
			mono[k][i][j] = make_pair(0, 0);
		}
	}
}


void solution() {						// 블럭을 쌓고 나서 처리하는 과정
	while (true) {
		int rr = remove(0);			// 지울게 있는지 확인하고 처리 
		if (rr != 0) {				// 지워졌으면 블럭 한번 내리고, 다시 처음부터 
			down(0);
			continue;
		}
		int tem = check(0);				// 연한칸에 있는지 확인
		if (tem != -1) {				// 있으면 밑에 칸들 지우고, down하고 다시 처음부터 
			check_t(0, tem);
			down(0);
			continue;
		}
		break;		
	}
	while (true) {
		int rr = remove(1);
		if (rr != 0) {
			down(1);
			continue;
		}
		int tem = check(1);
		if (tem != -1) {
			check_t(1, tem);
			down(1);
			continue;
		}
		break;
	}
}


int main() {
	cin >> n;
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 4; j++){
			mono[0][i][j] = make_pair(0, 0);
			mono[1][i][j] = make_pair(0, 0);
		}
	}
	for (int i = 0; i < 4; i++) {
		top[0][i] = 6;
		top[1][i] = 6;
	}
	for (int i = 0; i < n; i++) {
		int t, x, y;
		cin >> t >> x >> y;
		rc_move(0, t, x, y);			// 블럭 쌓고, 처리 
		rc_move(1, t, x, y);
		solution();
		
	}
	cout << score << '\n';
	int answer = 0;
	for (int k = 0; k < 2; k++) {
		for (int i = 2; i < 6; i++) {
			for (int j = 0; j < 4; j++) {
				if (mono[k][i][j].first != 0) answer += 1;
			}
		}
	}
	cout << answer;
	

	return 0;
}