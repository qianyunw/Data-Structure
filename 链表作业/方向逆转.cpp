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
            h = new LinkNode<T>;
            h->data = NULL;
            h->link = NULL;
        }
        void Create(T* a,int n)
        {
            int i = 0;
            h->data = a[0];
            LinkNode<T> *head = h;
            LinkNode<T> *tail = h;
            for(i = 1; i < n; i++)
            {
                head->link = new LinkNode<T>;
                tail = head->link;
                tail->data = a[i];
                tail->link = NULL;
                head = tail;
            }
            length=n;
        }
        void RollBack()
        {
            int i = 0;
            LinkNode<T> *head = h;
            LinkNode<T> *tail = h->link;
            LinkNode<T> *temp = h->link;
            for(head; temp->link != NULL;)
            {
                tail = temp;
                temp = temp->link;
                tail->link = head;
                head = tail;
            }
            h->link = NULL;
            h = temp;
            temp->link = head;
        }
        void Show(int q)
        {
            LinkNode<T> *head = h;
            int i;
            for(i=1;i<=length;i++)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY);
                cout<<setw(4)<<i;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
            }
            cout<<endl;
            for(head;head != NULL;head = head->link)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN);
                if(q)
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED);
                cout<<setw(4)<<head->data;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
            }
            cout<<endl;
        }
    protected:
    private:
        LinkNode<T>* h;
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
                cout<<"Before.\n";
                A1.Show(0);
                cout<<"After.\n";
                if(n == 1)
                {
                    A1.Show(1);
                    break;
                }
                A1.RollBack();
                A1.Show(1);
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
                cout<<"Before.\n";
                A2.Show(0);
                cout<<"After.\n";
                if(n == 1)
                {
                    A2.Show(1);
                    break;
                }
                A2.RollBack();
                A2.Show(1);
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
                cout<<"Before.\n";
                A3.Show(0);
                cout<<"After.\n";
                if(n == 1)
                {
                    A3.Show(1);
                    break;
                }
                A3.RollBack();
                A3.Show(1);
                break;
            }
        }
        cout<<"Again?(Y/y)\n";
        cin>>answer;
    }
    cout<<"WELCOME NEXT TIME\n";
    return 0;
}
