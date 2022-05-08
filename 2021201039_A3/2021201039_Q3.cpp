#include <iostream>
#include <string>
using namespace std;
char grid[100][100];
string words[50];
int r, c, x;
string ans[50];
struct TrieNode
{
    TrieNode *child[26];
    char c;
    bool is_end;
    string word;
};
struct TrieNode *newNode(char ch)
{
    TrieNode *temp = new TrieNode;
    temp->is_end = false;
    temp->word = "";
    for (int i = 0; i < 26; i++)
        temp->child[i] = NULL;
    temp->c = ch;
    return temp;
}
void solve_util(int i, int j, TrieNode *curr, int &count)
{
    int idx = grid[i][j] - 'a';
    if (curr->child[idx] == NULL || grid[i][j] == ';')
    {
        return;
    }
    curr = curr->child[idx];
    if (curr->word != "")
    {
        ans[count] = curr->word;
        count++;
    }
    char tc = grid[i][j];
    grid[i][j] = ';';
    if (i >= 1)
    {
        solve_util(i - 1, j, curr, count);
    }
    if (i < r - 1)
    {
        solve_util(i + 1, j, curr, count);
    }
    if (j >= 1)
    {
        solve_util(i, j - 1, curr, count);
    }
    if (j < c - 1)
    {
        solve_util(i, j + 1, curr, count);
    }
    grid[i][j] = tc;
}
TrieNode *root = newNode('/');
void insert_into_Trie(string str)
{
    TrieNode *curr = root;
    for (int i = 0; i < str.length(); i++)
    {
        int idx = str[i] - 'a';
        if (curr->child[idx] == NULL)
            curr->child[idx] = newNode(str[i]);
        curr = curr->child[idx];
    }
    curr->word = str;
    curr->is_end = true;
}

void solve(int &count)
{
    for (int i = 0; i < x; i++)
    {
        string w = words[i];
        insert_into_Trie(w);
    }
    for (int l = 0; l < r; l++)
    {
        for (int k = 0; k < c; k++)
        {
            solve_util(l, k, root, count);
        }
    }
}
int main()
{
    int count = 0;
    cin >> r >> c;
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            cin >> grid[i][j];
        }
    }
    cin >> x;
    if (x == 0)
    {
        cout << "" << endl;
        return 0;
    }
    for (int i = 0; i < x; i++)
    {
        cin >> words[i];
    }
    solve(count);
    for (int i = 0; i < count - 1; ++i)
    {
        for (int j = i + 1; j < count; ++j)
        {
            if (ans[i] > ans[j])
            {
                string t = ans[i];
                ans[i] = ans[j];
                ans[j] = t;
            }
        }
    }    
    for (int i = 0; i < count; i++)
    {
        cout << ans[i] << " ";
    }
    cout << endl;
    return 0;
}