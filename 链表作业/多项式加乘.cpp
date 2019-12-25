#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include"windows.h"
#include"math.h"
using namespace std;

template<class T>
struct LinkNode
{
    T ci;
    T xi;
    LinkNode<T> *link;
    LinkNode(LinkNode<T> *next = NULL):link(next){}
    LinkNode(const T itemx, const T itemc, LinkNode<T> *next = NULL):ci(itemc),xi(itemx),link(next){}
};

template<class T>
class Node
{
    public:
        Node(){};
        T MaxOrder()
        {
            LinkNode<T> *head = first.link;
            while(head->link)
            {
                head = head->link;
            }
            return head->ci;
        }
    protected:
    private:
        LinkNode<T> first;
        int length;
        friend ostream& operator << (ostream& out, const Node<T>& A)
        {
            LinkNode<T> *head = A.first.link;
            while(head)
            {
                if(head != A.first.link)
                    out<<" + ";
                out<<head->xi<<"x^"<<head->ci;
                head = head->link;
            }
            out<<endl;
            return out;
        }
        friend istream& operator >> (istream& in, Node<T>& A)
        {
            T x,c;
            LinkNode<T> *head = A.first.link;
            LinkNode<T> *tail = &A.first;
            cout<<"coefficient:     exponent:   0->end (exp small->large).\n";
            in>>x;
            while(x)
            {
                cout<<"                 ";
                in>>c;
                cout<<endl;
                head = new LinkNode<T>(x, c);
                tail->link = head;
                tail = head;
                head = head->link;
                in>>x;
            }
            cout<<A;
            return in;
        }
        friend Node<T> operator + (Node<T>&A, Node<T>&B)
        {
            Node<T> C;
            LinkNode<T> *headA = A.first.link;
            LinkNode<T> *headB = B.first.link;
            LinkNode<T> *head = C.first.link;
            LinkNode<T> *tail = &C.first;
            T c;
            T x;
            while(headA && headB)
            {
                if(headA->ci == headB->ci)
                {
                    x = headA->xi + headB->xi;
                    c = headA->ci;
                    headA = headA->link;
                    headB = headB->link;
                }
                else if(headA->ci > headB->ci)
                {
                    x = headB->xi;
                    c = headB->ci;
                    headB = headB->link;

                }
                else
                {

                    x = headA->xi;
                    c = headA->ci;
                    headA = headA->link;

                }
                head = new LinkNode<T>(x,c);
                tail->link = head;
                tail = head;
                head = head->link;
            }
            if(A.MaxOrder() == B.MaxOrder())                                        //此处可化简为找到剩余的head的地址
            {
            return C;
            }
            else if(A.MaxOrder() > B.MaxOrder())
            {
                while(headA)
                {
                    head = new LinkNode<T>(headA->xi,headA->ci);
                    tail->link = head;
                    tail = head;
                    head = head->link;
                    headA = headA->link;
                }
                return C;
            }
            else
            {
                while(headB)
                {
                    head = new LinkNode<T>(headB->xi,headB->ci);
                    tail->link = head;
                    tail = head;
                    head = head->link;
                    headB = headB->link;
                }
                return C;
            }
        }
        friend Node<T> operator * (Node<T>&A, Node<T>&B)
        {
            Node<T> C;
            int MAX = 1 + A.MaxOrder() + B.MaxOrder();
            T * result = new T [MAX];                                               //借助result来实现, 缺陷在于指数必为整数 若为小数， 则复杂。
            int i;
            for(i = 0; i < MAX; i++)
                result[i] = 0;

            LinkNode<T> *headA = A.first.link;
            LinkNode<T> *headB = B.first.link;
            LinkNode<T> *head = C.first.link;
            LinkNode<T> *tail = &C.first;
            T c;
            T x;
            for(headA = A.first.link; headA != NULL; headA = headA->link)
            {
                for(headB = B.first.link; headB != NULL; headB = headB->link)
                {
                    result[int(headA->ci + headB->ci)] += headA->xi * headB->xi;
                }
            }
            for(i = 0; i < MAX; i++)
            {
                if(result[i])
                {
                    head = new LinkNode<T>(result[i],i);
                    tail->link = head;
                    tail = head;
                    head = head->link;
                }
            }
            return C;
        }
};

int main()
{
	char answer='Y';
	while(answer == 'Y'||answer == 'y')
    {
        int n,i;
        system("cls");
        cout << "int-1,double-default.\n";
        char t;
        cin>>t;
        switch(t)
        {
            case '1':
            {
                Node<int> A1,B1;
                cin>>A1>>B1;
                cout<<"We did addition:\n";
                cout<<(A1 + B1);
                cout<<"We did multiply:\n";
                cout<<(A1 * B1);
                break;
            }
            default:
            {
                Node<double> A2,B2;
                cin>>A2>>B2;
                cout<<"We did addition:\n";
                cout<<(A2 + B2);
                cout<<"We did multiply:\n";
                cout<<(A2 * B2);
            }
        }
        cout<<"Again?(Y/y)\n";
        cin>>answer;
    }
    cout<<"WELCOME NEXT TIME\n";
    return 0;
}
