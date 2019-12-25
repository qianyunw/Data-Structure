#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include"windows.h"
using namespace std;

template<class T>
struct LinkNode
{
    T data;
    LinkNode<T> *link;
};

template<class T>
class Node
{
    public:
        Node()
        {
            first.data = NULL;
            first.link = NULL;
        }
        void Create(T* a,int n)
        {
            int i = 0;
            first.link = new LinkNode<T>;
            LinkNode<T> *head = first.link;
            LinkNode<T> *tail = first.link;
            head->data = a[0];
            head->link = NULL;
            for(i = 1; i < n; i++)
            {
                head->link = new LinkNode<T>;
                tail = head->link;
                tail->data = a[i];
                tail->link = NULL;
                head = tail;
            }
            length=n+1;
        }
        LinkNode<T>* Locate(int i)
        {
            int j=0;
            LinkNode<T> *head = first.link;
            for(j = 1; j < i; j++)
            {
                if(head  ==  NULL)
                    return head;
                else
                    head = head->link;
            }
            return head;
        }
        LinkNode<T>* Max()
        {
            int i = 0;
            LinkNode<T> *maxi = first.link;
            for(i = 1; i < length; i++)
            {
                if(maxi->data < Locate(i)->data)
                {
                    maxi = Locate(i);
                }
            }
            return maxi;
        }
        LinkNode<T>* Number(LinkNode<T>* head)
        {
            T x = head->data;
            for(head = head->link; head != NULL; head = head->link)
            {
                if(x  ==  head->data)
                {
                    return head;
                }
            }
            if(head  ==  NULL)
                return NULL;
        }
        int Translation(LinkNode<T> *p)
        {
            LinkNode<T> *head = first.link;
            int i=1;
            for(head,i;head != NULL&&head != p;head=head->link,i++)
            {}
            return i;
        }
        void Delete(int num)
        {
            LinkNode<T> *temp = Locate(num);
            Locate(num-1)->link=Locate(num+1);
            delete temp;
        }
        void Tidyup()
        {
            LinkNode<T> *head = first.link;
            for(head;head != NULL;head=head->link)
            {
                while(Number(head) != NULL)
                {
                    Delete(Translation(Number(head)));
                    length--;
                }
            }
        }
        void ShowMax()
        {
            LinkNode<T> *head = first.link;
            int i;
            for(i=1;i<length;i++)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY);
                cout<<setw(4)<<i;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
            }
            cout<<endl;
            for(head;head != NULL;head = head->link)
            {
                if(head  ==  Max())
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED);
                    cout<<setw(4)<<head->data;
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
                }
                else
                    cout<<setw(4)<<head->data;
            }
            cout<<endl;
        }
        void ShowNumber(T x)
        {
            LinkNode<T> *head = first.link;
            int i;
            for(i=1;i<length;i++)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY);
                cout<<setw(4)<<i;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
            }
            cout<<endl;
            for(head;head != NULL;head=head->link)
            {
                if(x  ==  head->data)
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN);
                    cout<<setw(4)<<head->data;
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
                }
                else
                    cout<<setw(4)<<head->data;
            }
            cout<<endl;
        }
    protected:
    private:
        LinkNode<T> first;
        int length;

};

int const MAX=20;
int main()
{
	char answer='Y';
	while(answer == 'Y'||answer == 'y')
    {
        int n,i;
        system("cls");
        cout << "char-1,int-2,double-default.\n";
        char t;
        cin>>t;
        cout<<"How many elements would you like to add?\n";
        cin>>n;
        if(n>MAX||n<=0)
        {
            cout<<"The number is going to be smaller than "<<MAX<<", and bigger than 0.\n";
            exit(0);
        }
        switch(t)
        {
            case '1':
            {
                char a1[MAX];
                cout<<"Please enter your elements\n";
                for(i=0;i<n;i++)
                    cin>>a1[i];
                Node<char> A1;
                A1.Create(a1,n);
                char x1;
                cout<<"Here comes the max element.\n";
                A1.ShowMax();
                cout<<"What element would you like to find?\n";
                cin>>x1;
                A1.ShowNumber(x1);
                cout<<"Let's tidy them up!\n";
                A1.Tidyup();
                A1.ShowMax();
                break;
            }
            case '2':
            {
                int a2[MAX];
                cout<<"Please enter your elements\n";
                for(i=0;i<n;i++)
                    cin>>a2[i];
                Node<int> A2;
                A2.Create(a2,n);
                int x2;
                cout<<"Here comes the max element.\n";
                A2.ShowMax();
                cout<<"What element would you like to find?\n";
                cin>>x2;
                A2.ShowNumber(x2);
                cout<<"Let's tidy them up!\n";
                A2.Tidyup();
                A2.ShowMax();
                break;
            }

            default:
            {
                double a3[MAX];
                cout<<"Please enter your elements\n";
                for(i=0;i<n;i++)
                    cin>>a3[i];
                Node<double> A3;
                A3.Create(a3,n);
                double x3;
                cout<<"Here comes the max element.\n";
                A3.ShowMax();
                cout<<"What element would you like to find?\n";
                cin>>x3;
                A3.ShowNumber(x3);
                cout<<"Let's tidy them up!\n";
                A3.Tidyup();
                A3.ShowMax();
            }
        }
        cout<<"Again?(Y/y)\n";
        cin>>answer;
    }
    cout<<"WELCOME NEXT TIME\n";
    return 0;
}
