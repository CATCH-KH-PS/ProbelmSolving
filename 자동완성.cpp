#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;
int d[100001];
int n;
vector<string> a[27];

int solution(vector<string> words) {
    int answer = 0;
    n = words.size();
    memset(d, 0, sizeof(d));
    for (int i = 0; i < n; i++) {  // 각 단어의 첫글자로 나 눔  
        a[words[i][0] - 'a'].push_back(words[i]);
    }
    for (int i = 0; i < 26; i++) {  // 각 알파벳 별로 정렬함  
        if (a[i].size() == 0) continue;
        sort(a[i].begin(), a[i].end());
    }

    for (int i = 0; i < 26; i++) {
        if (a[i].size() == 0) continue; // 사이즈가 0이면 continue; 
        if (a[i].size() == 1) {  // 1이면 한글자만 치면 됨  
            answer += 1;
            continue;
        }
        int temp = 1;
        int temp_last = -1;  // 이웃한 단어들끼리만 비교하면됨 temp는 j와 j+1의 같은 글자수 temp_last는 j-1과 j 의 같은 글자수  
        for (int j = 0; j < a[i].size() - 1; j++) {
            for (int k = 1; k < min(a[i][j].length(), a[i][j + 1].length()); k++) {
                if (a[i][j][k] == a[i][j + 1][k]) {
                    temp += 1;
                }
                else break;
            }
            answer += max(temp, temp_last);
            if (max(temp, temp_last) < a[i][j].length()) {                
                answer += 1;
            }
            
            

            temp_last = temp;
            temp = 1;
        } 
        if (temp_last < a[i][a[i].size() - 1].length()) {  // 마지막 단어 처리  
            answer += 1;
        }
        answer += temp_last;
    }

   /* for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            int temp = 0;
            string s1 = words[i];
            string s2 = words[j];
            for (int k = 0; k < min(s1.length(), s2.length()); k++) {
                if (s1[k] == s2[k]) {
                    temp += 1;
                }
                else {                   
                    break;
                }
            }
            if (d[i] < temp) {
                d[i] = temp;
                if (temp < words[i].length()) {
                    d[i] += 1;
                }
            }
            if (d[j] < temp) {
                d[j] = temp;
                if (temp < words[j].length()) {
                    d[j] += 1;
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (d[i] == 0) answer += 1;
        else {
            answer += d[i];
        }
    }*/

    return answer;
}

int main() {
    vector<string> s = { "go","gone","guild" };
    cout << solution(s);
}
