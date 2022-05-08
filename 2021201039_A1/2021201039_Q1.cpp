#include<iostream>
#include<string>
using namespace std;
void _swap(string &str1,string &str2)
{
    string temp=str1;
    str1=str2;
    str2=temp;
}
void _rev(string &str)
{
    int n=str.size();
    int i=0;
    int j=n-1;
    while(i<j)
    {
        char temp=str[i];
        str[i]=str[j];
        str[j]=temp;
        i++;
        j--;
    }
}
string add(string &s1,string &s2)
{
    if(s2.size()>s1.size())
        _swap(s1,s2);
    string ans="";
    int n1=s1.size();
    int n2=s2.size();
    int diff=n1-n2;
    int carry=0;
    for(int i=n2-1;i>=0;i--)
    {
        int sum=(s1[i+diff]-'0')+(s2[i]-'0')+carry;
        ans.push_back(sum%10+'0');
        carry=sum/10;
    }
    for(int i=diff-1;i>=0;i--)
    {
        int sum=(s1[i]-'0')+carry;
        ans.push_back(sum%10+'0');
        carry=sum/10;
    }
    if(carry)
        ans.push_back(carry+'0');
    _rev(ans);
    return ans;
}
string sub(string &s1,string &s2)
{
    string ans="";
    int n1=s1.size();
    int n2=s2.size();
    int diff=n1-n2;
    int carry=0;
    for(int i=n2-1;i>=0;i--)
    {
        int res=(s1[i+diff]-'0')-(s2[i]-'0')-carry;
        if(res<0)
        {
            res+=10;
            carry=1;
        }
        else    
            carry=0;
        ans.push_back(res+'0');
    }
    for(int i=diff-1;i>=0;i--)
    {
        if(s1[i]=='0' && carry==1)
        {
            ans.push_back('9');
            continue;
        }
        int res=(s1[i]-'0')-carry;
        ans.push_back(res+'0');
        carry=0;
    }
    int k=ans.size();
    int i,c=0;
    for(i=k-1;i>=0;i--)
    {
        if(ans[i]=='0')
            c++;
        else
            break;
    }
    if(c==k)
        return "0";
    ans=ans.substr(0,k-c);
    _rev(ans);
    return ans;
}
string mul(string &s1,string &s2)
{
    if(s1=="0" || s2=="0")
        return "0"; 
    int l1=s1.size();
    int l2=s2.size();
    int *arr;
    int l=l1+l2;
    arr=new int[l];
    for(int i=0;i<l;i++)
        arr[i]=0;
    int i=l2-1;
    int pf=0;
    while(i>=0)
    {
        int ival=s2[i]-'0';
        i--;
        int j=l1-1;
        int k=l-1-pf;
        int carry=0;
        while(j>=0 || carry!=0)
        {
            int jval=j>=0?s1[j]-'0': 0;
            j--;
            int prod=ival*jval+carry+arr[k];
            arr[k]=prod%10;
            carry=prod/10;
            k--;
        }
        pf++;
    }
    string res="";
    bool flag=false;
    for(int n=0;n<l;n++)
    {
        if(arr[n]==0 && flag==false)
            continue;
        else
        {
            flag=true;
            res+=to_string(arr[n]);
        }
    }
    return res;
}
bool compare(string &s1,string &s2)
{
    int n1=s1.size();
    int n2=s2.size();
    if(n1>n2)
        return true;
    if(n2>n1)
        return false;
    if(n1==n2)
    {
        for(int i=0;i<n1;i++)
        {
            if(s1[i]>s2[i])
                return true;
            if(s1[i]<s2[i])
                return false;
        }
    }
    return true;
}
string mod(string &a, string &b)
{
    while(compare(a,b))
    {
        int k=b.size();
        string temp=a.substr(0,k);
        if(!compare(temp,b))
        {
            k=k+1;
            temp=a.substr(0,k);
        }    
        bool flag=true;
        for(int i=0;i<temp.size();i++)
        {
            if(temp[i]!='0')
            {
                flag=false;
                break;
            }
                
        }
        if(flag==true)
            temp="";
        while(compare(temp,b))
            temp=sub(temp,b);
        if(temp!="0")   
            a=temp+a.substr(k);
        else
            a=a.substr(k);
    }
    if(a=="")
        return "0";
    return a;
}
string fact(string &str)
{
    string s="1";
    string one="1";
    string res="1";
    while(str!=s)
    {
        res=mul(res,s);
        s=add(s,one);
    }
    res=mul(res,str);
    return res;
}
string gcd(string a,string b)
{
    if(b=="0")
        return a;
    return gcd(b,mod(a,b));
}
string fgcd(string &a,string &b)
{
    string ans="";
    if(compare(a,b))
        ans=gcd(a,b);
    else
        ans=gcd(b,a);
    return ans;
}
string exp(string &a,string &b)
{
    long long int n=0;
    for(int i=0;i<b.size();i++)
        n=n*10+(b[i]-'0');
    string res="1";
    while(n>0)
    {
        if(n&1)
            res=mul(res,a);
        a=mul(a,a);
        n=n>>1;
    }
    return res;
}
bool isoperator(char c)
{
    if(c=='+' || c=='-' || c=='x')
        return true;
    return false;  
}
string calc(string &str)
{
    string pop="";
    string nop="";
    for(int i=0;i<str.size();i++)
    {
        if(str[i]=='x')
        {
            int p=i-1;
            while(p>=0 && (!isoperator(str[p])))
            {
                pop+=str[p];
                p--;
            }
            _rev(pop);
            int n=i+1;
            while(n<str.size() && (!isoperator(str[n])))
            {
                nop+=str[n];
                n++;
            }
            str=str.substr(0,p+1)+mul(pop,nop)+str.substr(n);
            i=0;
            pop="";
            nop="";
        }
    }
    pop="";
    nop="";
    int i;
    for(i=0;i<str.size();i++)
    {
        if(isoperator(str[i]))
            break;
        pop+=str[i];
    }
    int j=i;
    i++;
    for(;i<str.size();i++)
    {
        if(isoperator(str[i]))
        {
            if(str[j]=='+')
            {
                pop=add(pop,nop);
                nop="";
                j=i;
                continue;
            }
            else if(str[j]=='-')
            {
                pop=sub(pop,nop);
                nop="";
                j=i;
                continue;
            }
        }
        else
            nop+=str[i];        
    }
    if(str[j]=='+')
        pop=add(pop,nop);
    else if(str[j]=='-')
        pop=sub(pop,nop);
    return pop;
}
int main()
{
    cout<<"Enter the type of operation"<<endl;
    cout<<"1.Exponentiation"<<endl;
    cout<<"2.GCD"<<endl;
    cout<<"3.Factorial"<<endl;
    cout<<"4.Calculator"<<endl;
    int i=0;
    cin>>i;
    if(i==1)
    {
        string s1,s2;
        cin>>s1>>s2;
        cout<<exp(s1,s2);
    }
    if(i==2)
    {
        string s1,s2;
        cin>>s1>>s2;
        cout<<fgcd(s1,s2);
    }
    if(i==3)
    {
        string s1;
        cin>>s1;
        cout<<fact(s1);
    }
    if(i==4)
    {
        string s1;
        cin>>s1;
        cout<<calc(s1);
    }
}