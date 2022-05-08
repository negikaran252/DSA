#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;
vector<pair<int,string> > pathsDist;

int mat[10][10]={0};

void all_paths(int s, int d, int n,vector<bool> seen,vector<int> path,int &path_idx)
{
    seen[s]=true;
    path[path_idx]=s;
    path_idx++;
    if(s==d)
    {
        int size=path_idx;
        string temp="";
        int dist=0;
        for(int ind=1;ind<size;ind++)
        {
            dist+=mat[path[ind-1]][path[ind]];
        }
        for(int ind=0;ind<size;ind++)
        {
            int t=path[ind];
            temp+=to_string(t)+" ";
        }
        pair<int,string> p;
        p.first=dist;
        p.second=temp;
        pathsDist.push_back(p);

    }
    else
    {
        for(int id=0;id<n;id++)
        {
            if(seen[id]==false && mat[s][id]!=0)
            {
                
                all_paths(id,d,n,seen,path,path_idx);
            }
        }
    }
    path_idx--;
    seen[s] = false;

}
void solve(int s, int d,int n)
{
    vector<bool> seen(n,false);
    vector<int> path(n);
    int path_idx=0;
    all_paths(s,d,n,seen,path,path_idx);
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
    int k;
    cin>>k;
    for(int i=0;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            solve(i,j,n);
        }
    }
    sort(pathsDist.begin(),pathsDist.end());
    int l=pathsDist.size();
    for(int i=0;i<min(k,l);i++)
    {
        cout<<pathsDist[i].second<<endl;
    }
    return 0;
}

