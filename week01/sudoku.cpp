#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <queue>
#include <tuple>
using namespace std;
int n = 9;
bool ok = false;
vector<vector<int>> a(9, vector<int>(9, 0));
vector<vector<int>> ans(9, vector<int>(9));

bool check(int cnt, int num) { // 놓아도 되는 수인지 확인하는 함수
	int x = cnt / 9;
	int y = cnt % 9;
	for (int i = 0; i < n; i++) {  // 행과 열에 같은 숫자가 있는지 확인
		if (a[x][i] == num || a[i][y] == num) return false;
	}
	int box_x = x / 3;
	int box_y = y / 3;
	for (int i = box_x*3; i <= box_x*3 + 2; i++) {  // 3*3 박스에 같은 숫자가 잇는지 확인
		for (int j = box_y*3; j <= box_y*3 + 2; j++) {
			if (a[i][j] == num) return false;
		}
	}
	a[x][y] = num;
	return true;
}

void go(int cnt) {  // dfs로 한칸씩 진행하면서 확인 
	if (cnt == 81) {
		for (int i = 0; i < n; i++) {
			ans[i] = a[i];
		}	
		ok = true;  // 한번 답을 구하면 다음은 진행하지 못하도록 하기 위해 
		return;
	}
	int x = cnt / 9;
	int y = cnt % 9;
	if (a[x][y] != 0 && !ok) {
		go(cnt + 1);
	}
	else if (a[x][y] == 0 && !ok) {
		for (int i = 1; i <= 9; i++) {
			if (check(cnt, i)) {
				go(cnt + 1);
				a[x][y] = 0;
			}
		}
	}
}

int main() {
	for (int i = 0; i < n; i++) {
		string s;
		cin >> s;
		for (int j = 0; j < n; j++) {
			a[i][j] = s[j] - '0';
		}
	}
	go(0);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << ans[i][j];
		}
		if (i == n - 1) return 0;
		cout << '\n';
	}

	return 0;
}
