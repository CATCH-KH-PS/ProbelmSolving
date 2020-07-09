#include <string>
#include <vector>
#include <queue>
#include <string>
#include <iostream>
#include <set>
#include <tuple>
using namespace std;
vector<string> a; // map을 전역변수로 쓰기위해
int r, c;
int ans = 0;
bool check(int x, int y) { // 4칸 확인하는 것
    char temp = a[x][y];
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            if (temp != a[x + i][y + j]) {
                return false;
            }
        }
    }
    return true;
}
?
void down() { // 빈 곳을 내리는 함수
    for (int j = 0; j < c; j++) {
        int empty_st = -1; // 빈곳이 발생하는 시작점, 빈곳이 발생했는지 확인하는 용도
        queue<char> q; // 빈곳이 발생한 때부터 이곳에 넣는다.
        for (int i = r - 1; i >= 0; i--) {
            if (empty_st == -1 && a[i][j] == '.') {
                empty_st = i;
                continue;
            }
            if (empty_st != -1 && a[i][j] != '.') {
                q.push(a[i][j]);
                a[i][j] = '.';
                continue;
            }
        }
        while (!q.empty()) { // 큐에 있는 것들을 빈곳이 시작된 점부터 하나하나 넣어줌
            char temp = q.front();
            q.pop();
            a[empty_st][j] = temp;
            empty_st -= 1;
        }
    }
}
?
?
bool go() { // 2*2 를 . 으로 만들기
    bool ok = false;
    set<pair<int, int>> s;
    for (int i = 0; i < r - 1; i++) {
        for (int j = 0; j < c - 1; j++) {
            if (a[i][j] == '.') continue;
            if (check(i, j)) {
                ok = true;
                s.insert(make_pair(i, j));
                s.insert(make_pair(i + 1, j));
                s.insert(make_pair(i + 1, j + 1));
                s.insert(make_pair(i, j + 1));
            }
        }
    }
    if (!ok) return ok;
    ans += s.size();
    set<pair<int, int>>::iterator it;
    for (it = s.begin(); it != s.end(); it++) {        
        int x, y;
        tie(x, y) = *it;
        a[x][y] = '.';        
    }
    down();
    return ok;
}
?
?
?
?
int solution(int n, int m, vector<string> board) {
    a = board;
    r = n;
    c = m;
    int answer = 0; // 각 열별로 맨 위의 값만 넣는 배열을 만들어 시간을 줄일 수 있음
    bool ok = true;
    while (ok) {
        ok = go();
    }
    answer = ans;
?
    return answer;
}
