/*
- 처음에 수가 많이 큰 줄 알고 건너 뛰어야 한다고 생각함 
- 그러나 시간 복잡도 계산해 보니 모든 수를 다 돌아도 된다고 생각할 수 있었음

알고리즘 
1. 사람 수 만큼의 string 배열을 만들어 숫자(num) 을 키워가면서, n 진수로 바꿔주고
2. 나온 n진수 수의 길이만큼 돌면서 사람들의 배열에 넣어준다. 
3. 원하는 사람의 답 길이가 t 보다 크거나 같으면 break;
*/

#include <string>
#include <vector>
#include <iostream>
using namespace std;

vector<string> ans;  //사람들의 수만큼 배열 

string trans(int n, int number) { // number를 n진수로 바꿔주는 함수 
    string temp = "";
    while (true) {
        if (number < n) {
            if (number >= 10) { // 마지막 수 처리 
                number -= 10;
                temp = char(number + 'A') + temp;
            }
            else {
                temp = to_string(number) + temp;
            }
            
            break;
        }
        int t = number % n; // 나머지 
        if (t >= 10) {  // 10 보다 크면 알파벳으로 
            t -= 10;
            temp = char(t + 'A') + temp;
        }
        else {
            temp = to_string(t) + temp;
        }
        number /= n; 
        

    }
    return temp;
}


string solution(int n, int t, int m, int p) {
    string answer = "";
    for (int i = 0; i < m; i++) { // 각 사람들의 배열에 빈 string 넣어줌
        ans.push_back("");
    }
    int num = 0; // n 진수로 변하게 될 수 
    int index = 0;  // 몇번째 사람에게 넣어줘야 하는지 나타내는 수
    while (true) {
        if (ans[p - 1].length() >= t) break;
        string temp = trans(n, num);
        for (int i = 0; i < temp.length(); i++) { // n 진수 길이만큼 돌면서 각 답변에 넣어줌
            ans[index] += temp[i];
            index += 1;
            if (index == m) index = 0;
        }
        num += 1; // number 높이고 다시 진행
    }
    answer = ans[p - 1].substr(0, t); 
    return answer;
}


int main() {
    cout << solution(16, 16, 2, 2);
}