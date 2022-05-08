#include<iostream>
#include<string>
#define N 90000
using namespace std;

template <typename T>
class Deque
{
    public:
    int first,cap,sz;
    T* arr=new T[N];
    Deque()
    {
        
        sz=0;
        cap=N;
        first=0;
    }
    Deque(int n, T x)
    {
        sz=0;
        cap=N;
        first=0;
        for(int i=0;i<n;i++)
            push_back(x);
    }
    void push_back(T x)
    {
        if(sz==cap)
        {
            int newCap=2*cap;
            T* temp= new T[newCap];
            int rear=(first+sz-1)%cap;
            int i=0;
            while(i<sz)
            {
                temp[i]=arr[(i+first)%cap];
                i++;
            }
            arr=temp;
            cap=newCap;
            first=0;
        }
        int rear=(first+sz)%cap;
        arr[rear]=x;
        sz++;
    }
    void pop_back()
    {
        if(empty())
            return;
        sz--;
    }
    void push_front(T x)
    {
        if(sz==cap)
        {
            int newCap=2*cap;
            T* temp= new T[newCap];
            int rear=(first+sz-1)%cap;
            int i=0;
            while(i<sz)
            {
                temp[i]=arr[(i+first)%cap];
                i++;
            }
            arr=temp;
            cap=newCap;
            first=0;
        }
        first=(first+cap-1)%cap;
        arr[first]=x;
        sz++;
    }
    void pop_front()
    {
        if(empty())
            return;
        first=(first+1)%cap;
        sz--;
    }
    T front()
    {
        static T spvar;
        if(empty())
            return spvar;
        return arr[first];
    }
    T back()
    {
        static T spvar;
        if(empty())
            return spvar;
        return arr[(first+sz-1)%cap];
    }
    bool empty()
    {
        if(sz==0)
            return true;
        return false;
    }
    int size()
    {
        return sz;
    }
    void resize(int x, T d)
    {
        if(x==sz)
            return;
        else if(x<sz)
        {
            while(sz!=x)
                pop_back();
        }
        else
        {
            while(sz!=x)
                push_back(d);
        }
    }
    void clear()
    {
        first=0;
        sz=0;
    }
    T operator[](int n)
    {
        static T spvar;
        if(n<sz)
            return arr[(first+n)%cap];
        return spvar;
    }
};
int main()
{
    // Deque<int> d2;
    // d2.push_back(3);
    // d2.push_back(3);
    // d2.push_front(2);
    // d2.push_front(2);
    // d2.pop_back();
    // d2.pop_front();
    // cout<<d2.back()<<endl;
    // cout<<d2.front()<<endl;
    // cout<<d2.size()<<endl;
    // d2.resize(6 , 5);
    // cout<<d2[1]<<endl;
    // cout<<d2.size()<<endl;
    // for(int i=0;i<d2.size();i++)
    //     cout<<d2[i]<<" ";


    // Deque<int> d1(3 ,20);
    // cout<<d1.back()<<endl;
    // cout<<d1.front()<<endl;
    // cout<<d1.front()<<endl;
    // d1.resize(3 , 5);
    // d1.resize(10 , 5);
    // for(int i=0;i<d1.size();i++)
    //     cout<<d1[i]<<" ";
    // d1.clear();
    // cout<<d1.front()<<endl;


    // cout<<endl;
    // d.push_front(20);
    // d.push_front(2);
    // d.push_front(89);
    // d.push_back(5);
    // d.push_back(7);
    // d.push_back(10);
    // d.push_back(11);
    // d.push_back(12);
    // d.push_back(13);
    
    // //cout<<d[8]<<endl;
    // cout<<d.size()<<endl;

    // for(int i=0;i<d.size();i++)
    //     cout<<d[i]<<" ";
    // // cout<<d.front()<<endl;
    // // cout<<d.empty()<<endl;
    // // cout<<d.back()<<endl;
    return 0;
}