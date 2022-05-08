#include<iostream>
#include<string>
#define N 99991
using namespace std;

template <typename T1, typename T2>
struct node
{
    T1 _key;
    T2 _value;
    node<T1,T2>* next;
    node(T1 k,T2 v)
    {
        _key=k;
        _value=v;
        next=NULL;
    }
};

template <typename T1, typename T2>
class Map
{
    public:
    node<T1,T2>* arr[N];
    Map()
    {
        for(int i=0;i<N;i++)
            arr[i]=NULL;
    }
    long long hashFunc(string str)
    {
        int p=59;
        int m=1e9+9;
        long long h_value=0;
        long long power=1;
        for(int i=0;i<str.size();i++)
        {
            h_value+=((str[i]-40)*power)%m;
            power=(power*p)%m;
        }
        return h_value;
    }
    long long final_hashFunc(int k)
    {
        string str=to_string(k);
        return hashFunc(str);
    }
    long long final_hashFunc(float k)
    {
        string str=to_string(k);
        return hashFunc(str);
    }
    long long final_hashFunc(double k)
    {
        string str=to_string(k);
        return hashFunc(str);
    }
    long long final_hashFunc(string k)
    {
        return hashFunc(k);
    }
    void insert(T1 key,T2 value)
    {
        int index=(final_hashFunc(key))%N;
        node<T1,T2>* temp=new node<T1,T2>(key,value);
        if(arr[index]==NULL) 
            arr[index]=temp;
        else
        {
            node<T1,T2>* curr=arr[index];
            while(curr->next!=NULL && curr->_key!=key)
            {
                curr=curr->next;
            }
            if(curr->_key==key)
                curr->_value=value;
            else
                curr->next=temp;
        }
    }
    void erase(T1 key)
    {
        int index=(final_hashFunc(key))%N;
        node<T1,T2>* curr=arr[index];
        node<T1,T2>* prev=NULL;
        if(curr==NULL)
            return;
        while(curr!=NULL && curr->_key!=key)
        {
            prev=curr;
            curr=curr->next;
        }
        if(prev==NULL)
            arr[index]=curr->next;
        else
        {
            prev->next=curr->next;
            delete(curr);
        }

    }
    bool find(T1 key)
    {
        int index=(final_hashFunc(key))%N;
        node<T1,T2>* curr=arr[index];
        if(curr==NULL)
            return false;
        while(curr)
        {
            if(curr->_key==key)
                return true;
            curr=curr->next;
        }
        return false;
    }
    T2 operator[](T1 key)
    {
        static T2 spvar;
        int index=(final_hashFunc(key))%N;
        node<T1,T2>* curr=arr[index];
        if(curr==NULL)
        {
            //cout<<"Key doesnot exist"<<endl;
            return spvar;
        }
        while(curr)
        {
            if(curr->_key==key)
                return curr->_value;
            curr=curr->next;
        }
        //cout<<"Key doesnot exist"<<endl;
        return spvar;
    }
};
int main()
{
    Map<string,int> m1;
    m1.insert("Karan",10);
    m1.insert("Apurv",2);
    m1.insert("Adarsh",234);
    m1.erase("Adarsh");
    cout<<m1["Karan"]<<endl;
    cout<<m1["Adarsh"]<<endl;
    cout<<m1.find("Apurv");
    return 0;
}