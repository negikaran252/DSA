#include<iostream>
#include<vector>
#include<string>
using namespace std;
vector<string> res;
struct TrieNode
{
    TrieNode* child[26];
    bool is_end;
    string word;
    TrieNode()
    {
        for(int i=0;i<26;i++)
            child[i]=NULL;
        is_end=false;
        word="";
    }
};
bool lastNode(TrieNode *temp)
{
    for(int i=0;i<26;i++)
    {
        if(temp->child[i]!=NULL)
            return false;
    }    
    return true;
}
void insert(TrieNode *root,string str)
{
    TrieNode *curr=root;
    for(int i=0;i<str.length();i++)
    {
        int idx=str[i]-'a';
        if(curr->child[idx]==NULL)
            curr->child[idx]=new TrieNode();
        curr=curr->child[idx];
    }
    curr->is_end=true;
    curr->word=str;
}
bool search(TrieNode *root,string str)
{
    TrieNode* curr=root;
    for(int i=0;i<str.size();i++)
    {
        int idx=str[i]-'a';
        if(curr->child[idx]==NULL)
            return false;
        curr=curr->child[idx];
    }
    return curr->is_end;
}
void autocompl_util(TrieNode *curr,string str)
{
    if(curr->is_end)
        res.push_back(curr->word);
    if(lastNode(curr))
        return;
    for(int i=0;i<26;i++)
    {
        if(curr->child[i]==NULL)
            continue;
        else
        {
            autocompl_util(curr->child[i],str);
        }
    }
}

void autocomplete(TrieNode *root,string str)
{   
    TrieNode* curr=root;
    for(int i=0;i<str.size();i++)
    {
        int idx=str[i]-'a';
        if(curr->child[idx]==NULL)
            return;
        curr=curr->child[idx];
    }
    if(curr->is_end && lastNode(curr))
    {
        res.push_back(str);
        return;
    }    
    if(lastNode(curr)==false)
    {
        autocompl_util(curr,str);
    }
}
int min(int a, int b, int c)
{
    int small=INT_MAX;
    if(a<small)
        small=a;
    if(b<small)
        small=b;
    if(c<small)
        small=c;
    return small;
}
int edit_distance(string s1,string s2)
{
    int mat[200][200];
    int n=s1.size();
    int m=s2.size();
    for(int i=0;i<=n;i++)
    {
        for(int j=0;j<=m;j++)
        {
            if(i==0)
            {
                mat[i][j]=j;
            }
            else if(j==0)
            {
                mat[i][j]=i;
            }
            else if(s1[i-1]==s2[j-1])
            {
                mat[i][j]=mat[i-1][j-1];
            }
            else
            {
                mat[i][j]=min(mat[i-1][j],mat[i][j-1],mat[i-1][j-1])+1;
            }
        }
    }
    return mat[n][m];
}
void autocorrect(TrieNode* curr,string str)
{
    if(str.size()>104)
        return;
    if(curr->is_end)
    {
        if(edit_distance(str,curr->word)<=3)
            res.push_back(curr->word);
    }
    if(lastNode(curr))
        return;
    for(int i=0;i<26;i++)
    {
        if(curr->child[i]==NULL)
            continue;
        else
        {
            autocorrect(curr->child[i],str);
        }
    }
}
int main()
{
    TrieNode* root=new TrieNode();
    int n;
    cin>>n;
    for(int i=0;i<n;i++)
    {
        string str;
        cin>>str;
        insert(root,str);
    }   
    int ai;
    string ti;
    cin>>ai;
    cin>>ti;
    if(ai==1)
    {
        cout<<search(root,ti)<<endl;
    }
    else if(ai==2)
    {
        res.clear();
        autocomplete(root,ti);
        cout<<res.size()<<endl;
        for(int i=0;i<res.size();i++)
        {
            cout<<res[i]<<endl;
        }
    }
    else if(ai==3)
    {
        res.clear();
        autocorrect(root,ti);
        cout<<res.size()<<endl;
        for(int i=0;i<res.size();i++)
        {
            cout<<res[i]<<endl;
        }
    }
    return  0;
}