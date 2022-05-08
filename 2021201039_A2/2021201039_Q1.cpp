#include <iostream>
#include <limits>
#include <string>

using namespace std;

class CompObj
{
public:
    pair<int, int> p1;
    CompObj()
    {
        p1.first = 0;
        p1.second = 0;
    }
    CompObj(int a, int b)
    {
        p1.first = a;
        p1.second = b;
    }
    bool operator<(CompObj temp)
    {
        if (p1.first < temp.p1.first)
            return true;
        else if (p1.first == temp.p1.first && p1.second < temp.p1.second)
            return true;
        return false;
    }
    bool operator>(CompObj temp)
    {
        if (p1.first > temp.p1.first)
            return true;
        else if (p1.first == temp.p1.first && p1.second > temp.p1.second)
            return true;
        return false;
    }
    bool operator==(CompObj temp)
    {
        return ((p1.first == temp.p1.first) && (p1.second == temp.p1.second));
    }
    bool operator<=(CompObj temp)
    {
        if (p1.first < temp.p1.first)
            return true;
        else if (p1.first == temp.p1.first && p1.second < temp.p1.second)
            return true;
        else if (p1.first == temp.p1.first && p1.second == temp.p1.second)
            return true;
        return false;
    }
    bool operator>=(CompObj temp)
    {
        if (p1.first > temp.p1.first)
            return true;
        else if (p1.first == temp.p1.first && p1.second > temp.p1.second)
            return true;
        else if (p1.first == temp.p1.first && p1.second == temp.p1.second)
            return true;
        return false;
    }
};
template <typename T>
class Node
{
public:
    T val;
    Node<T> *left, *right;
    int height, freq;
    Node(T x)
    {
        val = x;
        left = NULL;
        right = NULL;
        height = 1;
        freq = 1;
    }
};

template <typename T>
class AVL
{
public:
    Node<T> *lb, *ub;
    int max(int x, int y)
    {
        if (x > y)
            return x;
        return y;
    }
    int _height(Node<T> *tRoot)
    {
        if (tRoot == NULL)
            return 0;
        return tRoot->height;
    }
    int balanceFactor(Node<T> *tRoot)
    {
        if (tRoot == NULL)
            return 0;
        return (_height(tRoot->left) - _height(tRoot->right));
    }
    Node<T> *leftRotate(Node<T> *tRoot)
    {
        Node<T> *oRoot = tRoot->right;
        Node<T> *temp = oRoot->left;
        oRoot->left = tRoot;
        tRoot->right = temp;

        oRoot->height = 1 + max(_height(oRoot->left), _height(oRoot->right));
        tRoot->height = 1 + max(_height(tRoot->left), _height(tRoot->right));
        return oRoot;
    }
    Node<T> *rightRotate(Node<T> *tRoot)
    {
        Node<T> *oRoot = tRoot->left;
        Node<T> *temp = oRoot->right;
        oRoot->right = tRoot;
        tRoot->left = temp;
        oRoot->height = 1 + max(_height(oRoot->left), _height(oRoot->right));
        tRoot->height = 1 + max(_height(tRoot->left), _height(tRoot->right));
        return oRoot;
    }
    Node<T> *insertion(Node<T> *root, T key)
    {
        if (root == NULL)
        {
            Node<T> *newnode = new Node<T>(key);
            return newnode;
        }

        if (key == (root->val))
        {
            (root->freq)++;
            return root;
        }
        if ((root->val) > key)
        {
            root->left = insertion(root->left, key);
        }
        else
        {
            root->right = insertion(root->right, key);
        }
        root->height = 1 + max(_height(root->left), _height(root->right));
        int bf = balanceFactor(root);
        if (bf < -1 && key > (root->right->val))
            return leftRotate(root);
        if (bf < -1 && key < (root->right->val))
        {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
        if (bf > 1 && key < (root->left->val))
            return rightRotate(root);
        if (bf > 1 && key > (root->left->val))
        {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        return root;
    }
    Node<T> *ioSuccessor(Node<T> *tRoot)
    {
        Node<T> *curr = tRoot;
        while (curr->left)
            curr = curr->left;
        return curr;
    }
    Node<T> *deletion(Node<T> *root, T key)
    {
        if (root == NULL)
            return root;
        if (key < (root->val))
            root->left = deletion(root->left, key);
        else if (key > (root->val))
            root->right = deletion(root->right, key);
        else
        {
            if (((root->left) == NULL) || ((root->right) == NULL))
            {
                Node<T> *temp = root->left ? root->left : root->right;
                if (temp == NULL)
                {
                    temp = root;
                    root = NULL;
                    delete (temp);
                }
                else
                {
                    *root = *temp; //may be *root=*temp
                    delete (temp);
                }
            }
            else
            {
                Node<T> *temp = ioSuccessor(root->right);
                root->val = temp->val;
                root->freq = temp->freq;
                root->right = deletion(root->right, temp->val);
            }
        }
        if (root == NULL)
            return root;
        root->height = 1 + max(_height(root->left), _height(root->right));
        int bf = balanceFactor(root);
        if (bf > 1 && balanceFactor(root->left) < 0)
        {
            root->left = leftRotate(root);
            return rightRotate(root);
        }
        if (bf > 1 && balanceFactor(root->left) >= 0)
            return rightRotate(root);
        if (bf < -1 && balanceFactor(root->right) > 0)
        {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
        if (bf < -1 && balanceFactor(root->right) <= 0)
            return leftRotate(root);
        return root;
    }
    bool search(Node<T> *root, T key)
    {
        if (root == NULL)
            return false;
        if (root->val == key)
            return true;
        if ((root->val) > key)
            return search(root->left, key);
        if ((root->val) < key)
            return search(root->right, key);
    }
    int countOccurrences(Node<T> *root, T key)
    {
        if (root == NULL)
            return 0;
        if (root->val == key)
            return root->freq;
        if ((root->val) > key)
            return countOccurrences(root->left, key);
        if ((root->val) < key)
            return countOccurrences(root->right, key);
    }
    void help_lower_bound(Node<T> *root, T key)
    {
        if (root == NULL)
            return;
        if (root->val >= key)
        {
            lb = root;
            help_lower_bound(root->left, key);
        }
        else
            help_lower_bound(root->right, key);
    }
    T lower_bound(Node<T> *root, T key)
    {
        lb = NULL;
        help_lower_bound(root, key);
        if (lb)
            return lb->val;
    }
    void help_upper_bound(Node<T> *root, T key)
    {
        if (root == NULL)
            return;
        if (root->val > key)
        {
            ub = root;
            help_upper_bound(root->left, key);
        }
        else
            help_upper_bound(root->right, key);
    }
    T upper_bound(Node<T> *root, T key)
    {
        static T spvar;
        ub = NULL;
        help_upper_bound(root, key);
        if (ub)
            return ub->val;
        return spvar;
    }

    void help_closestElement(Node<T> *tRoot, T key, T &diff, T &elem)
    {
        if (tRoot == NULL)
            return;
        if ((tRoot->val) == key)
        {
            elem = key;
            return;
        }
        if (diff > abs((tRoot->val) - key))
        {
            diff = abs((tRoot->val) - key);
            elem = tRoot->val;
        }
        if (key < (tRoot->val))
            help_closestElement(tRoot->left, key, diff, elem);
        else
            help_closestElement(tRoot->right, key, diff, elem);
    }
    T closestElement(Node<T> *root, T key)
    {
        T diff = numeric_limits<T>::max();
        T element = 0;
        help_closestElement(root, key, diff, element);
        return element;
    }

    void help(Node<T> *root, int k, int &c, bool &flag)
    {
        if (root == NULL || c >= k)
            return;
        help(root->right, k, c, flag);
        c += root->freq;
        if (c >= k && flag)
        {
            flag = false;
            cout << root->val << endl;
            return;
        }
        help(root->left, k, c, flag);
    }
    void kLargest(Node<T> *root, int k)
    {
        static T spvar;
        int count = 0;
        bool flag = true;
        help(root, k, count, flag);
        if (flag == true)
            cout << spvar << endl;
    }
    int countInRange(Node<T> *root, T start, T end)
    {
        if (root == NULL)
            return 0;
        T x = root->val;
        if (x == start && x == end)
            return root->freq;
        if (x >= start && x <= end)
            return ((root->freq) + countInRange(root->left, start, end) + countInRange(root->right, start, end));
        else if (x < start)
            return countInRange(root->right, start, end);
        else
            return countInRange(root->left, start, end);
    }
    void printInorder(Node<T> *root)
    {
        if (root)
        {
            printInorder(root->left);
            cout << root->val << " ";
            printInorder(root->right);
        }
    }
};
int main()
{
    // AVL<int> tree;
    // Node<int> * root=NULL;
    // root=tree.insertion(root,1);
    // root=tree.insertion(root,1);
    // root=tree.insertion(root,4);
    // root=tree.insertion(root,5);
    // root=tree.insertion(root,6);
    // root=tree.deletion(root,4);
    // cout<<tree.search(root,5)<<endl;
    // cout<<tree.search(root,154)<<endl;
    // cout<<tree.countOccurrences(root,1)<<endl;
    // cout<<tree.lower_bound(root,6)<<endl;
    // cout<<tree.upper_bound(root,3)<<endl;
    // cout<<tree.closestElement(root,3)<<endl;
    // tree.kLargest(root,1);
    // cout<<tree.countInRange(root,1,5)<<endl;
    // tree.printInorder(root);
    // cout<<endl;
    int t;
    int key; //T
    AVL <int> tree;
    Node<int> * root=NULL;
	while(1){
		cin>>t;
		switch(t){
			case 1:
				cin>>key;
				root=tree.insertion(root,key);
				break;
			case 2:
				cin>>key;
				root=tree.deletion(root,key);
				break;
			case 3:
                cin>>key;
				cout<<tree.search(root,key)<<endl;
				break;
				
			case 4:
				cin>>key;
				cout<<tree.countOccurrences(root,key)<<endl;
				break;
			case 5:
				cin>>key;
				
				cout<<tree.lower_bound(root,key)<<endl;
				break;
			case 6:
				cin>>key;
				cout<<tree.upper_bound(root,key)<<endl;
				break;
			case 7:
				cin>>key;
				cout<<tree.closestElement(root,key)<<endl;
				
				break;
			case 8:
				int k;
                cin>>k;
				tree.kLargest(root,k);
				break;
			case 9:
				int low,high; //T
				cin>>low>>high;
				cout<<tree.countInRange(root,low,high)<<endl;	
				break;
		}
    }
    return 0;
}