#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include<fstream>
#include"windows.h"
using namespace std;

//问题：什么时候退出呢？ 是尝试了所有可能的方法但还是没成功后，递归栈已空的时候吗？

int main()
{
    bool KNAP(int s,int n,int *w);
    int s;
    int n;
    char answer = 'Y';
    while(answer == 'Y' || answer == 'y')
    {
        cout<<"Enter s,n."<<endl;
        cin>>s>>n;
        int *w = new int[n];
        int i;
        for(i = 0; i < n; i++)
        {
            cout<<"NO."<<i<<":";
            cin>>w[i];
        }
        if(KNAP(s,n,w))
        {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole,FOREGROUND_GREEN);
            cout<<"YES"<<endl;
            SetConsoleTextAttribute(hConsole,FOREGROUND_RED | FOREGROUND_GREEN|FOREGROUND_BLUE);
        }
        else
            cout<<"SORRY"<<endl;
        cout<<"AGAIN ? (Y/y)"<<endl;
        cin>>answer;
    }

    return 0;
}
bool KNAP(int s,int n,int *w)
    {
        if(s == 0)
            return true;
        if(s < 0 || (s > 0 && n < 0))
            return false;
        if(s > 0 && n >= 0)
        {
            if(KNAP(s - w[n],n-1,w))
            {
                cout<<"NO."<<n;
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole,FOREGROUND_GREEN);
                cout<<"("<<w[n]<<")";
                SetConsoleTextAttribute(hConsole,FOREGROUND_RED);
                cout<<" & ";
                SetConsoleTextAttribute(hConsole,FOREGROUND_RED | FOREGROUND_GREEN|FOREGROUND_BLUE);
            }
            else
                KNAP(s,n-1,w);

        }
    }
