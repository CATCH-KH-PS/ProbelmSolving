# [3차] n진수 게임



```c++
#include <string>
#include <vector>
#include <iostream>

using namespace std;



string intconvertn(int n, int base)
{
    string answer = "";
    if (n == 0)
        return ("0");
    while (n != 0)
    {   
        string temp = "";
        if (n % base  > 9)
            temp += (n % base + '0' + 7);
        else
            temp += (n % base + '0');
        answer = temp  + answer;
        n /= base;
    }
    return (answer);
}

string solution(int n, int t, int m, int p) {
    string answer = "";
    string total = "";
    
    int max_size = t * m;
    for (int i = 0; total.size() < max_size; i++)
        total += intconvertn(i, n);
    for (int i = 0; i < max_size; i++)
        if (i % m == p - 1) 
            answer += total[i];
    return answer;
}
```



## 고찰

아스키코드를 조금 신경쓰면 풀 수 있는 문제였다.