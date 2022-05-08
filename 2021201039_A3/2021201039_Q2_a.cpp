#include<iostream>
#include<vector>
#include<string>
using namespace std;
int mat[10000][10000]={0};
void path_util(vector<int >&parent,int i,string &str)
{
    if(parent[i]==-1)
        return;
    str+=to_string(i)+" ";
    path_util(parent,parent[i],str);
}
string path(vector<int >&parent,int i)
{
    string temp="";
    path_util(parent,i,temp);
    return temp;
}
int shortest(vector<bool> &seen,vector<int> &src_dist)
{
    int idx;
    int small=INT_MAX;
    int k=seen.size();
    for(int i=0;i<k;i++)
    {
        if(seen[i]==false && src_dist[i]<small)
        {
            idx=i;
            small=src_dist[i];
        }
    }
    return idx;
}
void solve(int src,int n)
{
    vector<bool> seen(n,false);
    vector<int> src_dist(n,INT_MAX);
    vector<int> parent(n);
    vector<string> lex_path(n);
    parent[src]=-1;
    src_dist[src]=0;
    for(int j=0;j<n;j++)
    {
        int curr=shortest(seen,src_dist);
        seen[curr]=true;
        for(int i=0;i<n;i++)
        {
            if(mat[curr][i] && seen[i]==false && (src_dist[curr]+mat[curr][i]<=src_dist[i]))
            {
                src_dist[i]=mat[curr][i]+src_dist[curr];
                parent[i]=curr;
                if(lex_path[i]=="")
                {
                    lex_path[i]=path(parent,i);
                    lex_path[i]+=to_string(src);
                }
                else
                {
                    string strr=path(parent,i);
                    strr+=to_string(src);
                    if(strr<lex_path[i])
                        lex_path[i]=strr;
                }
            }
        }
    }
    for(int i=0;i<n;i++)
    {
        if(parent[i]==-1)
            continue;
        cout<<lex_path[i]<<endl;
    }
}
int main()
{
    int n,m;
    cin>>n>>m;
    int temp=m;
    while(temp--)
    {
        int i,j,w;
        cin>>i>>j>>w;
        mat[i][j]=w;
        mat[j][i]=w;
    }
    int src;
    cin>>src;
    solve(src,n);
    return 0;
}

 