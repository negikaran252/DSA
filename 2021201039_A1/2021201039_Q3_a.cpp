#include<iostream>
using namespace std;

template <typename T>
struct Node
{
    int row,column;
    T value;
    Node<T> *next;
    Node(int r,int c, T v)
    {
        row=r;
        column=c;
        value=v;
        next=NULL;
    }
};

template <typename T>
Node<T>* insert(Node<T> *head,int x,int y, T z)
{
    Node<T>* curr=head;
    Node<T>* temp=new Node<T>(x,y,z);
    if(curr==NULL)
    {
        return temp;
    }
    while(curr && curr->next) 
        curr=curr->next;
    curr->next=temp;
    return head;
}

template <typename T>
void display(Node<T> *head)
{
    Node<T>* curr=head;
    while(curr)
    {
        cout<<curr->row<<" ";
        cout<<curr->column<<" ";
        cout<<curr->value<<endl;
        curr=curr->next;
    }
}
template <typename T>
void FindMiddle(Node<T> *curr,Node<T> **first,Node<T> **second)
{
    Node<T>* fast;
    Node<T>* slow;
    slow=curr;
    fast=curr->next;
    while(fast!=NULL)
    {
        fast=fast->next;
        if(fast!=NULL)
        {
            fast=fast->next;
            slow=slow->next;
        }
        
    }
    *first=curr;
    *second=slow->next;
    slow->next=NULL;
}

template <typename T>
Node<T>* mergeBoth(Node<T> *first,Node<T> *second)
{
    Node<T>* ans=NULL;
    if(first==NULL)
        return second;
    else if(second==NULL)
        return first;
    if((first->row<second->row) || ((first->row==second->row) && (first->column<second->column)))
    {
        ans=first;
        ans->next=mergeBoth(first->next,second);
    }
    else if((first->row>second->row) || (first->row==second->row && first->column>second->column))
    {
        ans=second;
        ans->next=mergeBoth(first,second->next);
    }
    return ans;
}

template <typename T>
void mergeSort(Node<T>** head)
{
    Node<T>* curr=*head;
    Node<T>* first;
    Node<T>* sec;
    if(curr==NULL || curr->next==NULL)
        return;
    FindMiddle(curr,&first,&sec);
    mergeSort(&first);
    mergeSort(&sec);
    *head=mergeBoth(first,sec);
}

template <typename T>
Node<T>* MergeSorting(Node<T>* temp)
{
    mergeSort(&temp);
    return temp;
}

template <typename T>
Node<T>* transpose(Node<T>* a)
{
    Node<T>* curr=a;
    while(curr)
    {
        int temp=curr->row;
        curr->row=curr->column;
        curr->column=temp;
        curr=curr->next;
    }
    a=MergeSorting(a);
    return a;
}

template <typename T>
void multiply(Node<T>* a,Node<T>* b)
{
    Node<T>* res=NULL;
    b=transpose(b);
    Node<T>* curra=a;
    Node<T>* currb=b;
    while(curra)
    {
        int rr=curra->row;
        currb=b;
        while(currb)
        {
            T val=0;
            int rc=currb->row;
            Node<T>* tempa=curra;
            Node<T>* tempb=currb;
            while(tempa && (tempa->row==rr) && tempb && (tempb->row==rc))
            {
                if(tempa->column<tempb->column)
                    tempa=tempa->next;
                else if((tempa->column)>(tempb->column))
                    tempb=tempb->next;
                else
                {
                    val+=(tempa->value)*(tempb->value);
                    tempa=tempa->next;
                    tempb=tempb->next;
                }
            }
            if(val!=0)
                res=insert(res,curra->row,currb->row,val);
            while(currb && (currb->row==rc))
                currb=currb->next;
        }
        while(curra && (curra->row==rr))
            curra=curra->next;
    }
    display(res);
}
template <typename T>
void add(Node<T> *a,Node<T> *b)
{
    Node<T>* res=NULL;
    Node<T>* curra=a;
    Node<T>* currb=b;
    while(curra && currb)
    {
        if((curra->row)<(currb->row) || ((curra->row)==(currb->row) && (curra->column)<(currb->column)))
        {
            res=insert(res,curra->row,curra->column,curra->value);
            curra=curra->next;
        }  
        else if((curra->row)>(currb->row) || ((curra->row)==(currb->row) && (curra->column)>(currb->column)))
        {
            res=insert(res,currb->row,currb->column,currb->value);
            currb=currb->next;
        }
        else
        {
            T fval=curra->value+currb->value;
            if(fval!=0)
                res=insert(res,curra->row,curra->column,fval);
            curra=curra->next;
            currb=currb->next;
        }
    }
    while(curra)
    {
        res=insert(res,curra->row,curra->column,curra->value);
        curra=curra->next;
    }
    while(currb)
    {
        res=insert(res,currb->row,currb->column,currb->value);
        currb=currb->next;
    }
    display(res);
}

int main()
{
    int r,c;
    cin>>r>>c;
    float m[500][500];
    float n[500][500];
    for(int i=0;i<r;i++)
    {
        for(int j=0;j<c;j++)
            cin>>m[i][j];
    }
    for(int i=0;i<r;i++)
    {
        for(int j=0;j<c;j++)
            cin>>n[i][j];
    }
    Node<float> *a=NULL;
    Node<float> *b=NULL;
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(m[i][j])
                a=insert(a,i,j,m[i][j]);
            if(n[i][j])
                b=insert(b,i,j,n[i][j]);
        }
    }
    add(a,b);
    return 0;
}