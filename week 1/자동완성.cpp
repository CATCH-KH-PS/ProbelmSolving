#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

const int MAX = 100010;
int cost[MAX];

void cmpString(const string &a, const string &b, int idx) {
	int matched = 0;
	int max_len;
	a.length() > b.length() ? max_len = b.length() : max_len = a.length();

	for (int i = 0; i < max_len; i++) {
		if (a[i] == b[i]) matched++;
		else break;
	}

	//문자열 a의 cost 갱신
	if (cost[idx] < matched + 1) {
		if (a.length() < matched + 1) cost[idx] = a.length();
		else cost[idx] = matched + 1;
	}

	//문자열 b의 cost 갱신
	if (cost[idx + 1] < matched + 1) {
		if (b.length() < matched + 1) cost[idx + 1] = b.length();
		else cost[idx + 1] = matched + 1;
	}
}

int solution(vector<string> words) {
	int answer = 0;

	sort(words.begin(), words.end());
	for (int i = 0; i < words.size() - 1; i++) {
		cmpString(words[i], words[i + 1], i);
	}

	for (int i = 0; i < words.size(); i++) { answer += cost[i]; }
	return answer;
}