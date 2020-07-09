#include <string>
#include <vector>
#include <iostream>

using namespace std;

struct TRIE
{
  bool finish;
  TRIE *Node[26];
  TRIE()
  {
    finish = false;
    for (int i = 0; i < 26; i++)
      Node[i] = NULL;
  }

  void insert(char *str)
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
    Node[cur]->insert(str + 1);
  }

  bool find(char *str)
  {
    if (*str == NULL)
    {
      if (finish == true)
        return true;
      return false;
    }
    int cur = *str - 'a';
    if (Node[cur] == NULL)
    {
      return false;
    }
    return Node[cur]->find(str + 1);
  }
};
