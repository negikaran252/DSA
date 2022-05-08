#include <iostream>
#include<unordered_map>
using namespace std;

class LRU_Cache
{
	public:
		class node
		{
			public:
				int key;
				int value;
				node *prev;
				node *next;

				node(int k, int v)
				{
					next=NULL;
					prev=NULL;
					key=k;
					value=v;
				}			
		};
		int cap;
		unordered_map<int,node*> m;
		node* head=new node(0,0);
		node* tail=new node(0,0);
		LRU_Cache(int c)
		{
			cap=c;
			head->next=tail;
			tail->prev=head;
		}
		void add_Node(node* newnode)
		{
			node* temp = head->next;
			head->next=newnode;
			newnode->prev=head;
			newnode->next=temp;
			temp->prev=newnode;
		}
		void delete_Node(node* delnode)
		{
			node* before=delnode->prev;
			node* after=delnode->next;
			before->next=after;
			after->prev=before;
			delete(delnode);
		}
		int get(int k)
		{
			if(m.find(k)!=m.end())
			{
				node* curr=m[k];
				int res=curr->value;
				m.erase(k);
				node* temp=new node(k,res);
				delete_Node(curr);
				add_Node(temp);
				m[k]=head->next;
				return res;
			}
			return -1;
		}
		void set(int k,int v)
		{
			if(m.find(k)!=m.end())
			{
				node* curr=m[k];
				m.erase(k);
				delete_Node(curr);
			}
			if(m.size()==cap)
			{
				m.erase(tail->prev->key);
				delete_Node(tail->prev);
			}
			node* nn=new node(k,v);
			add_Node(nn);
			m[k]=head->next;
		}
};
int main()
{
	int s;
	cout<<"Enter the size of LRU Cache"<<endl;
	cin>>s;
	LRU_Cache c1(s);
	int i;
	cout<<"Type 1 to get the value"<<endl;
	cout<<"Type 2 to set the value"<<endl;
	cout<<"Type 3 to exit"<<endl;
	while(true)
	{
		cin>>i;
		if(i==1)
		{
			int k;
			cin>>k;
			cout<<c1.get(k)<<endl;
		}
		if(i==2)
		{
			int k,v;
			cin>>k>>v;
			c1.set(k,v);
		}
		if(i==3)
			break;
	}
}