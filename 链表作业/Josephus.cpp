#include <stdlib.h>
#include <iostream>
#include <iomanip>
using namespace std;

int const MAX=20;
class Josephus
{
    public:
        Josephus(int n1,int s1,int m1);
        void DeletePeople(int del);
        int CountPeople();
        void OutPeople();
        ~Josephus();
    protected:
    private:
        bool People[MAX];
        int m;
        int n;
        int s;

};


Josephus::Josephus(int n1=0,int s1=0,int m1=0)
{
    if(m1>0&&n1>0&&s1>0&&n1<=MAX&&m1<=MAX&&s1<=MAX)
    {
        m=m1;
        n=n1;
        s=s1;
        int i;
        for(i=0;i<n;i++)
            People[i]=true;
        for(i=n;i<MAX;i++)
            People[i]=false;
    }
    else
    {
        cout<<"Please enter a positive integer which is smaller than "<<MAX<<"."<<endl;
        exit(0);
    }
}

void Josephus::DeletePeople(int del)
{
    People[del]=false;
    int i;
    cout<<endl;
    for(i=0;i<n;i++)
    {
        cout<<setw(3)<<i+1;
    }
    cout<<endl;
    for(i=0;i<n;i++)
    {
        if(People[i]==false)
            cout<<"   ";
        else
            cout<<"  *";
    }
    cout<<endl<<"No."<<del+1<<"person is out.\n";
}

int Josephus::CountPeople()
{
    int i=0;
	int num=0;
    for(i=0;i<n;i++)
    {
        if(People[i]==true)
            num++;
    }
    return num;
}

void Josephus::OutPeople()
{
    int i=0;
	int time=1;
    for(i=s-1;CountPeople()>0;i++,time++)
    {
        if(i>=n)
            i%=n;
        while(People[i]==false)
        {
            i++;
            if(i>=n)
            i%=n;
        }

        if(time==m)
        {
            DeletePeople(i);
			time=0;
        }
    }
}

Josephus::~Josephus()
{
    //dtor
}

int main()
{
	char answer='Y';
	while(answer=='Y'||answer=='y')
    {
        system("cls");
        cout << "Please enter n,s,m.\n";
        int m,s,n;
        cin>>m>>s>>n;
        Josephus A(m,s,n);
        A.OutPeople();
        cout<<"Again?(Y/y)\n";
        cin>>answer;
    }
    return 0;
}
