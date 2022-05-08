#include<iostream>
#include<queue>
#include<string>
using namespace std;
char grid[1001][1001];
struct ObjType 
{
    int row,col,dist;
    ObjType(int x, int y, int z)
    {
        row=x;
        col=y;
        dist=z;
    }
};
int solve(int x,int y, int d,int n, int m)
{
    bool seen[1001][1001];
    ObjType rider_me(x,y,d);
    for(int i1=0;i1<n;i1++)
    {
        for(int j1=0;j1<m;j1++)
        {
            if(grid[i1][j1]=='#')
                seen[i1][j1]=true;
            else
                seen[i1][j1]=false;
        }
    }
    queue<ObjType> q;
    seen[rider_me.row][rider_me.col]=true;
    q.push(rider_me);
    while(q.empty()==false)
    {
        ObjType curr=q.front();
        q.pop();
        int r=curr.row;
        int c=curr.col;
        int d=curr.dist;
        if(grid[r][c]=='D')
            return curr.dist;
        if(r<n-1 && seen[r+1][c]!=true )
        {
           ObjType temp(r+1,c,d+1);
           q.push(temp);
            seen[r+1][c]=true;
        }
        if(r>0 && seen[r-1][c]!=true )
        {
           ObjType temp(r-1,c,d+1);
           q.push(temp);
            seen[r-1][c]=true;
        }
        if(c<m-1 && seen[r][c+1]!=true )
        {
           ObjType temp(r,c+1,d+1);
           q.push(temp);
            seen[r][c+1]=true;
        }
        if(c>0 && seen[r][c-1]!=true )
        {
           ObjType temp(r,c-1,d+1);
           q.push(temp);
            seen[r][c-1]=true;
        }
    }
    return INT_MAX;
}
int main()
{
    int n,m;
    cin>>n>>m;
    for(int i=0;i<n;i++)
    {
        string strr;
        cin>>strr;
        for(int j=0;j<m;j++)
        {
            grid[i][j]=strr[j];
        }
    }
    bool flag=false;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(grid[i][j]=='.')
            {
                grid[i][j]='D';
                flag=true;
                break;
            }
        }
        if(flag)
            break;
    }
    int Rdistance=INT_MAX;
    int me_dist=INT_MAX;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            if(grid[i][j]=='R')
            {
                Rdistance=min(Rdistance,solve(i,j,0,n,m));
            }
            if(grid[i][j]=='A')
            {
                me_dist=solve(i,j,0,n,m);
            }
        }
    }
    if(me_dist>Rdistance || me_dist==INT_MAX)
    {
        cout<<"NO"<<endl;
    }
    else
    {
        cout<<"YES"<<endl;
        cout<<me_dist<<endl;
    }
    return 0;
}


