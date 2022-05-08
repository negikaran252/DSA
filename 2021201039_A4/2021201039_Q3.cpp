#include<iostream>
#include<vector>
using namespace std;
struct TrieNode
{
    TrieNode* child[2];
    bool is_end;
    TrieNode()
    {
        child[0]=NULL;
        child[1]=NULL;
        is_end=false;
    }
};
void insert(TrieNode *root,long long int x)
{
    TrieNode *curr=root;
    for(int i=63;i>=0;i--)
    {
        long long int b=(bool)(x&(1ll<<i));
        if(curr->child[b]==NULL)
            curr->child[b]=new TrieNode();
        curr=curr->child[b];
    }
    curr->is_end=true;
}
long long int findxor(TrieNode *root,long long int x)
{
    long long int res=0;
    TrieNode* curr=root;
    for(int i=63;i>=0;i--)
    {
        long long int b=(bool)(x&(1ll<<i));
        long long int temp=b^1ll;
        if(curr->child[temp]!=NULL)
        {
            res=res+(1ll<<i);
            curr=curr->child[temp];
        }
        else
        {
            curr=curr->child[b];
        }
    }
    return res;
}
int main()
{
    TrieNode* root=new TrieNode();
    long long int n,q,j;
    vector<long long int> arr;
    cin>>n>>q;
    for(j=1;j<=n;j++)
    {
        long long int num;
        cin>>num;
        arr.push_back(num);
    }
    for(j=0;j<n;j++)
    {
        insert(root,arr[j]);
    }
    for(j=1;j<=q;j++)
    {
        long long int num;
        cin>>num;
        cout<<findxor(root,num)<<endl;
    }
    return 0;
}