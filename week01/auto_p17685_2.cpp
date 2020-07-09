#include <string>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

struct TRIE
{
  bool finish;
  int child;
  TRIE *Node[26];
  TRIE() : finish(false), child(0)
  {
    memset(Node, 0, sizeof(Node));
  }

  void insert(const char *str)
  {
    if (*str == NULL)
    {
      finish = true;
      return;
    }
    int cur = *str - 'a';
    if (Node[cur] == NULL)
    {
      Node[cur] = new TRIE();
    }
    else
    {
      Node[cur]->child++;
    }

    return Node[cur]->insert(str + 1);
  }

  //2번이상 참조되는 문자열을 검색
  int find(const char *str)
  {
    if (*str == NULL)
    {
      return -1;
    }
    int cur = *str - 'a';
    if (Node[cur]->child > 0)
    {
      return 1;
    }

    return Node[cur]->find(str + 1);
  }
};

TRIE *root = new TRIE();
int solution(vector<string> words);

int main(void)
{
  vector<string> words;
  string tmp;
  int num;
  cin >> num;

  for (int i = 0; i < num; i++)
  {
    cin >> tmp;
    words.push_back(tmp);
  }
  cout << solution(words) << "\n";
  return 0;
}

int solution(vector<string> words)
{
  int answer = 0;
  bool flag;

  sort(words.begin(), words.end());
  for (int i = 0; i < words.size(); i++)
  {
    const char *tmp = words[i].c_str();
    root->insert(tmp);
  }
  //make trie

  //search words
  for (int i = 0; i < words.size(); i++)
  {
    int max_len = 0;
    int tmp_len = 0;
    const char *c = words[i].c_str();

    if (root->find(c) == 0)
    {
      tmp_len++;
    }
    else
    {
      if (tmp_len > max_len)
      {
        max_len = tmp_len;
      }

      if (root->find(c) == -1)
      {
        answer += max_len;
      }
    }
  }
  return answer;
}