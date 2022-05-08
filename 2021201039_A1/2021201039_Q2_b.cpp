#include<iostream>
#include<unordered_map>
using namespace std;
struct Node
{
	int key,value,cnt;
	Node* next;
	Node* prev;
	Node(int k,int v)
	{
		key=k;
		value=v;
		cnt=1;
		next=NULL;
		prev=NULL;
	}
};
struct List
{
	int size;
	Node* head;
	Node* tail;
	List()
	{
		head=new Node(0,0);
		tail=new Node(0,0);
		head->next=tail;
		tail->prev=head;
		size=0;
	}
	void addNode(Node* curr)
	{
		Node* temp=head->next;
		head->next=curr;
		curr->next=temp;
		temp->prev=curr;
		curr->prev=head;
		size++;
	}
	void deleteNode(Node* delNode)
	{
		Node* before=delNode->prev;
		Node* after=delNode->next;
		before->next=after;
		after->prev=before;
		size--;  
	}
};
class LFU_Cache
{
	unordered_map<int,Node*> m;
	unordered_map<int,List*> fl;
	int capacity;
	int minFreq;
	int cursize;
	public:
	LFU_Cache(int c)
	{
		capacity=c;
		minFreq=0;
		cursize=0;
	}
	void updateFrequencyMap(Node* temp)
	{
		m.erase(temp->key);
		fl[temp->cnt]->deleteNode(temp);
		if(temp->cnt==minFreq && fl[temp->cnt]->size==0)
			minFreq++;
		List* nextFreqList=new List();
		if(fl.find(temp->cnt+1)!=fl.end())
			nextFreqList=fl[temp->cnt+1];
		temp->cnt+=1;
		nextFreqList->addNode(temp);
		fl[temp->cnt]=nextFreqList;
		m[temp->key]=temp;
	}
	int get(int k)
	{
		if(m.find(k)!=m.end())
		{
			Node* curr=m[k];
			int ans=curr->value;
			updateFrequencyMap(curr);
			return ans;
		}
		return -1;
	}
	void set(int k,int v)
	{
        if(capacity==0)
            return;
		if(m.find(k)!=m.end())
		{
			Node* curr=m[k];
			curr->value=v;
			updateFrequencyMap(curr);
		}
		else
		{
			if(cursize==capacity)
			{
				List* l1=fl[minFreq];
				m.erase(l1->tail->prev->key);
				fl[minFreq]->deleteNode(l1->tail->prev);
				cursize--;
			}
			cursize++;
			minFreq=1;
			List* l2=new List();
			Node* newnode=new Node(k,v);
			if(fl.find(minFreq)!=fl.end())
				l2=fl[minFreq];
			
			l2->addNode(newnode);
			m[k]=newnode;
			fl[minFreq]=l2;
		}
	}
};
int main()
{
	int s;
	cout<<"Enter the size of LFU Cache"<<endl;
	cin>>s;
	LFU_Cache c1(s);
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
