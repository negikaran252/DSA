#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
struct node
{
    int idx;
    int value;
};
struct suffixNode
{
    int index;
    int rank[2];
};
typedef struct suffixNode suffixNode;

bool compfunc(suffixNode a,suffixNode b)
{
    if(a.rank[0]<b.rank[0])
    {
        return true;
    }
    else if(a.rank[0]==b.rank[0] && a.rank[1]<b.rank[1])
    {
        return true;
    }
    return false;
}

int* kasai(string str,int* suffix_array)
{
    int n=str.size();
    int *lcp=new int[n];
    int inv_suffix[n];
    int c=0;
    for(int j=0;j<n;j++)
    {
        lcp[j]=0;
    }
    for(int j=0;j<n;j++)
    {
        inv_suffix[suffix_array[j]]=j;
    }
    for(int i=0;i<n;i++)
    {
        if(inv_suffix[i]==n-1)
        {
            c=0;
            continue;
        }
        int j=suffix_array[inv_suffix[i]+1];
        while(((i+c)<n) && ((j+c)<n) && (str[i+c]==str[j+c]))
        {
            c++;
        }
        lcp[inv_suffix[i]]=c;
        if(c>0)
        {
            c--;
        }
    }
    return lcp;
}


int* buildSuffixArray(string s)
{
    int drep;
    int n=s.size();
    suffixNode suffixArray[n];
    int SuffInd[n];
    int i=0;
    struct node snode;
    while(i<n)
    {
        suffixArray[i].index=i;
        suffixArray[i].rank[0]=s[i]-'0';
        if(i==n-1)
        {
            snode.idx=i;
            suffixArray[i].rank[1]=-1;
        }
        else
        {
            snode.idx=i;
            snode.value=i*2;
            suffixArray[i].rank[1]=s[i+1]-'0';
        }
        i++;
    }
    sort(suffixArray,suffixArray+n,compfunc);
    for(int k=2;k<n;k=k*2)
    {
        int curr_rank=0;
        int prev_rank=suffixArray[0].rank[0];
        suffixArray[0].rank[0]=curr_rank;
        SuffInd[suffixArray[0].index]=0;
        for(int i=1;i<n;i++)
        {
            int ranki0=suffixArray[i].rank[0];
            int ranki1=suffixArray[i].rank[1];
            if((ranki0==prev_rank) && (ranki0!=prev_rank))
            {
                prev_rank=ranki0;
                suffixArray[i].rank[0]=curr_rank;
            }
            if((ranki0==prev_rank) && (ranki1==suffixArray[i-1].rank[1]))
            {
                prev_rank=ranki0;
                suffixArray[i].rank[0]=curr_rank;
            }
            else
            {
                curr_rank++;
                prev_rank=ranki0;
                suffixArray[i].rank[0]=curr_rank;
            }
            
            SuffInd[suffixArray[i].index]=i;
        }
        drep=0;
        for(int i=0;i<n;i++)
        {
            int next_index=(suffixArray[i].index)+k;
            if((next_index<n) && (next_index>=n))
            {
                suffixArray[i].rank[1]=suffixArray[SuffInd[next_index]].rank[0];
            }
            if(next_index<n)
            {
                suffixArray[i].rank[1]=suffixArray[SuffInd[next_index]].rank[0];
            }
            else
            {
                suffixArray[i].rank[1]=-1;
            }
            
        }
        sort(suffixArray,suffixArray+n,compfunc);
    }
    int *finalSuffArr=new int[n];
    for(int j=0;j<n;j++)
    {
        finalSuffArr[j]=suffixArray[j].index;
    }
    return finalSuffArr;
}

int main()
{
    string str;
    cin>>str;
    int l1=str.size();
    string temp=str;
    reverse(temp.begin(),temp.end());
    string s=str+"#"+temp;
    int n=s.size();
    int *final_suff_arr=buildSuffixArray(s);
    int *LCP=kasai(s,final_suff_arr);
    int len=0;
    int idx;
    // for(int i=0;i<str.size();i++)
    // {
    //     cout<<LCP[i]<<" ";
    // }
    for(int i=0;i<n-1;i++)
    {
        if(LCP[i]>len)
        {
            if(((final_suff_arr[i]<l1) && (final_suff_arr[i+1]>l1)) || ((final_suff_arr[i]>l1) && (final_suff_arr[i+1]<l1)))
            {
                len=LCP[i];
                idx=final_suff_arr[i+1];
            }
        }
    }
    cout<<s.substr(idx,len);

    return 0;
}