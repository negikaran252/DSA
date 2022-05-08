#include<iostream>
using namespace std;
#define MAX 250000

template <typename T>
class SpMatrix
{
    T** arr;
    int row,column,len;
    public:
    SpMatrix(int r,int c)
    {
        row=r;
        column=c;
        int n = r*c;
        len=0;
        arr=new T* [n];
        for(int i=0;i<n;i++)
        {
            arr[i]=new T[3];
        }
    }
    void insert(int r, int c, T val)
    {
        arr[len][0]=r;
        arr[len][1]=c;
        arr[len][2]=val;
        len++;
    }
    void add(SpMatrix b)
    {
        int ar=0;
        int br=0;
        SpMatrix<T> res(row,column);
        while(ar<len && br<len)
        {
            if(arr[ar][0]<b.arr[br][0] || (arr[ar][0]==b.arr[br][0] && arr[ar][1]<b.arr[br][1]))
            {
                res.insert(arr[ar][0],arr[ar][1],arr[ar][2]);
                ar++;
            }   
            else if(arr[ar][0]>b.arr[br][0] || (arr[ar][0]==b.arr[br][0] && arr[ar][1]>b.arr[br][1]))
            {
                res.insert(b.arr[br][0],b.arr[br][1],b.arr[br][2]);
                br++;
            }
            else
            {
                T fval=arr[ar][2]+b.arr[br][2];
                if(fval!=0)
                    res.insert(arr[ar][0],arr[ar][1],fval);
                ar++;
                br++;
            }
        }
        while(ar<len)
        {
            res.insert(arr[ar][0],arr[ar][1],arr[ar][2]);
            ar++;
        }
        while(br<b.len)
        {
            res.insert(b.arr[br][0],b.arr[br][1],b.arr[br][2]);
            br++;
        }
        res.display();
    }
    SpMatrix transpose()
    {
        SpMatrix<T> res(column,row);
        res.len=len;
        int* total=new int[column];
        for(int i=0;i<column;i++)
            total[i]=0;
        for(int i=0;i<len;i++)
            total[(int)(arr[i][1])]++;
        int k=column+1;
        int* index= new int[k];
        index[0]=0;
        for(int i=1;i<=column;i++)
            index[i]=index[i-1]+total[i-1];
        for(int i=0;i<len;i++)
        {
            int pos=index[(int)arr[i][1]];
            index[(int)arr[i][1]]++;
            res.arr[pos][0]=arr[i][1];
            res.arr[pos][1]=arr[i][0];
            res.arr[pos][2]=arr[i][2];
        }
        return res;
    }
    void multiply(SpMatrix b)
    {
        SpMatrix<T> res(row,b.column);
        b=b.transpose();
        int ai=0;
        int bi=0;
        while(ai<len)
        {
            int rr=arr[ai][0];
            bi=0;
            while(bi<b.len)
            {
                T val=0;
                int rc= b.arr[bi][0];
                int atemp=ai;
                int btemp=bi;
                while(atemp<len && arr[atemp][0]==rr && btemp<b.len && b.arr[btemp][0]==rc)
                {
                    if(arr[atemp][1]<b.arr[btemp][1])
                        atemp++;
                    else if(arr[atemp][1]>b.arr[btemp][1])
                        btemp++;
                    
                    else
                    {
                        val+=((arr[atemp][2])*(b.arr[btemp][2]));
                        atemp++;
                        btemp++;
                    }
                }
                if(val!=0)
                    res.insert(rr,rc,val);
                while(bi<b.len && b.arr[bi][0]==rc)
                    bi++;
            }
            while(ai<len && arr[ai][0]==rr)
                ai++;
        }
        res.display();
    }
    void display()
    {
        for(int i=0;i<len;i++)
        {
            cout<<arr[i][0]<<" ";
            cout<<arr[i][1]<<" ";
            cout<<arr[i][2]<<" ";
            cout<<endl;
        }
    }
};
int main()
{
    int r,c;
    cin>>r>>c;
    SpMatrix<double> a(r, c);
    SpMatrix<double> b(r, c);
    float m[500][500];
    float n[500][500];
    for(int i=0;i<r;i++)
    {
        for(int j=0;j<c;j++)
        {
            cin>>m[i][j];
        }
    }
    for(int i=0;i<r;i++)
    {
        for(int j=0;j<c;j++)
        {
            cin>>n[i][j];
        }
    }
    for(int i=0;i<r;i++)
    {
        for(int j=0;j<c;j++)
        {
            if(m[i][j]!=0)
                a.insert(i,j,m[i][j]);
            if(n[i][j]!=0)
                b.insert(i,j,n[i][j]);
        }
    }
    a.multiply(b);

    return 0;
}