//使用Dijkstra算法。
//问题：为什么输入7时时间最短的反而比钱最少的那条路径时间长？
//问题：为什么输入4时钱最少可以找到的路径而时间最短却找不到？
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include"windows.h"
#include <math.h>
using namespace std;

struct Clock
{
    int hour;
    int minute;
    Clock()
    {
        hour = 100;
        minute = 30;
    }
    Clock(int hour1, int minute1)
    {
        hour = hour1;
        minute = minute1;
    }
    Clock(int n)
    {
        hour = n/60;
        minute = n%60;
    }
    Clock(Clock &x)
    {
        hour = x.hour;
        minute = x.minute;
    }
    operator int()
    {
        return hour*60+minute;
    }
    bool operator > (Clock n)
    {
        if(int(*this) > int(n))
            return true;
        else
            return false;
    }
    Clock operator - (Clock n)
    {
        if(*this > n)
            return Clock(int(*this)-int(n));
        else
            return Clock(24*60+int(*this)-int(n));
    }
    Clock operator + (Clock n)
    {
        return Clock(int(*this)+int(n));
    }
    void Show()
    {
        cout<<setw(2)<<setfill('0')<<hour<<":"<<setw(2)<<minute;
    }
};

class Table
{
private:
public:
    string number;
    string strstart;
    string strending;
    int intstart;
    int intending;
    int money;
    Clock start;
    Clock ending;
    int turn;
    Table()
    {
        string s[8] = {"BJ", "SH", "WLMQ", "XA", "GZ", "LS", "KM", "WH"};
        intstart = 0;
        intending = 0;
        strstart = s[intstart];
        strending = s[intending];
        number = "0000";
        money = 9999;
        start = Clock(9999);
        ending = Clock(99999);
        turn = 9;//默认是9不是1
    }
    Table(int ints, int inte, string number1, int money1, Clock start1, Clock ending1, int turn1)
    {
        string s[8] = {"BJ", "SH", "WLMQ", "XA", "GZ", "LS", "KM", "WH"};
        intstart = ints;
        intending = inte;
        strstart = s[intstart];
        strending = s[intending];
        number = number1;
        money = money1;
        start = start1;
        ending = ending1;
        turn = turn1;
    }
    Table(Table &x)
    {
        number = x.number;
        strstart = x.strstart;
        strending = x.strending;
        intstart = x.intstart;
        intending = x.intending;
        money = x.money;
        start = x.start;
        ending = x.ending;
        turn = x.turn;
    }

    Clock During()
    {
        return (ending - start);
    }
    void Show()
    {
        cout<<setw(22)<<setfill(' ')<<number<<":"<<setw(4)<<setfill(' ')<<strstart<<" -"<<setw(4)<<setfill(' ')<<strending<<" ";
        start.Show();
        cout<<"-";
        ending.Show();
        cout<<" "<<"Duration: ";
        During().Show();
        cout<<" "<<setw(5)<<setfill(' ')<<money<<"$ "<<"Turn: "<<turn;
        cout<<endl;
    }
    Table operator + (Table n)
    {
        Table t;
        int xmoney;
        xmoney =  money + n.money;
        Clock wait = n.start -  ending;
        Clock xending =  ending + wait + n.During();
        int i;
        int mlen = number.length();
        int nlen = n.number.length();
        char xnumber[mlen + nlen + 1];
        for(i = 0; i < mlen; i++)
            xnumber[i] =  number[i];
        xnumber[i] = '-';
        for(i = i + 1; i < mlen + nlen + 1; i++)
            xnumber[i] = n.number[i - mlen - 1];
        xnumber[i] = 0;
        t = Table(intstart, n.intending, xnumber, xmoney, start, xending, turn + n.turn);
        return t;
    }

};
class PrefectPlan
{
private:
    Table data[8][8];
    int source;
    string strsource;
    Table dismon[8];
    Table distime[8];
    Table disturn[8];
    int gather[10];
public:
    PrefectPlan()
    {
        int i,j;
        for(i = 0; i < 8; i++)
        {
            for(j = 0; j < 8; j++)
            {
                data[i][j] = Table(i,j,"0000", 9999,Clock(9999),Clock(99999),9);
            }
        }
        data[0][1] = Table(0,1,"6320",680 ,Clock(16,20),Clock(17,25),1);
        data[0][2] = Table(0,2,"2104",1150,Clock(8,0)  ,Clock(9,55),1) ;
        data[0][3] = Table(0,3,"0201",930 ,Clock(15,25),Clock(17,0),1) ;
        data[1][0] = Table(1,0,"6320",680 ,Clock(18,0) ,Clock(19,5),1) ;
        data[2][0] = Table(2,0,"2104",1150,Clock(10,45),Clock(11,40),1);
        data[2][6] = Table(2,6,"0082",1480,Clock(9,30) ,Clock(12,15),1);
        data[3][0] = Table(3,0,"0201",930 ,Clock(12,35),Clock(14,15),1);
        data[3][4] = Table(3,4,"2323",1320,Clock(7,15) ,Clock(9,35),1) ;
        data[4][3] = Table(4,3,"2323",1320,Clock(10,15),Clock(11,35),1);
        data[4][7] = Table(4,7,"4723",810 ,Clock(11,25),Clock(13,5),1) ;
        data[5][6] = Table(5,6,"0173",830 ,Clock(10,20),Clock(11,45),1);
        data[5][7] = Table(5,7,"3304",890 ,Clock(14,15),Clock(15,45),1);
        data[6][2] = Table(6,2,"0082",1480,Clock(13,5) ,Clock(15,50),1);
        data[6][5] = Table(6,5,"0173",830 ,Clock(12,35),Clock(14,0),1) ;
        data[7][4] = Table(7,4,"4723",810 ,Clock(7,5)  ,Clock(8,45),1) ;
        data[7][5] = Table(7,5,"3304",890 ,Clock(16,25),Clock(17,55),1);
        cout<<"ENTER SOURCE: 0-BJ 1-SH 2-WLMQ 3-XA 4-GZ 5-LS 6-KM 7-WH\n";
        cin>>source;
        string s[8] = {"BJ", "SH", "WLMQ", "XA", "GZ", "LS", "KM", "WH"};
        strsource = s[source];
        gather[0] = source;
        for(i = 1; i < 8; i++)
        {
            gather[i] = 10;
            dismon[i] = data[source][i];
            distime[i] = data[source][i];
            disturn[i] = data[source][i];
        }
        dismon[0] = data[source][0];
        distime[0] = data[source][0];
        disturn[0] = data[source][0];
        LeastTime();

        gather[0] = source;
        for(i = 1; i < 8; i++)
        {
            gather[i] = 10;
        }
        LeastCost();
        gather[0] = source;
        for(i = 1; i < 8; i++)
        {
            gather[i] = 10;
        }
        LeastTurn();
    }
    bool IsGather(int m)
    {
        int i;
        for(i = 0; i < 8; i++)
        {
            if(m == gather[i])
                return true;
        }
        return false;
    }
    void LeastCost()
    {
        int i;
        Table minitable = dismon[0];
        int miniint = 0;
        for(i = 0; i < 8; i++)
        {
            if(!IsGather(i))
            {
                if(minitable.money > dismon[i].money)
                {
                    miniint = i;
                    minitable = dismon[i];
                }
            }
        }
        int j = 0;
        while(gather[j] != 10)//可能会错
            j++;
        gather[j] = miniint;//小心不是i哪！！！
        for(i = 0; i < 8; i++)
        {
            if(!IsGather(i))
            {
                if(dismon[i].money > (minitable + data[miniint][i]).money)
                {
                    dismon[i] = minitable + data[miniint][i];
                }
            }
        }
        j = 0;
        while(gather[j] != 10)
            j++;
        if(j >= 8)
        {
            int i;
            cout<<strsource<<"->  (Least Money)\n";
            for(i = 0; i < 8; i++)
            {
                if(dismon[i].number != "0000")
                    dismon[i].Show();
            }
        }
        else
        {
            LeastCost();
        }
    }
    void LeastTime()
    {
        int i;
        Table minitable = distime[0];
        int miniint = 0;
        for(i = 0; i < 8; i++)
        {
            if(!IsGather(i))
            {
                if(minitable.During() > distime[i].During())
                {
                    miniint = i;
                    minitable = distime[i];
                }
            }
        }
        int j = 0;
        while(gather[j] != 10)//可能会错
            j++;
        gather[j] = miniint;//小心不是i哪！！！
        for(i = 0; i < 8; i++)
        {
            if(!IsGather(i))
            {
                if(distime[i].During() > (minitable + data[miniint][i]).During())
                {
                    distime[i] = minitable + data[miniint][i];
                }
            }
        }
        j = 0;
        while(gather[j] != 10)
            j++;
        if(j >= 8)
        {
            int i;
            cout<<strsource<<"->  (Least Time)\n";
            for(i = 0; i < 8; i++)
            {
                if(distime[i].number != "0000")
                    distime[i].Show();
            }
            return;
        }
        else
        {
            LeastTime();
        }
    }

    void LeastTurn()
    {
        int i;
        Table minitable = disturn[0];
        int miniint = 0;
        for(i = 0; i < 8; i++)
        {
            if(!IsGather(i))
            {
                if(minitable.turn > disturn[i].turn)
                {
                    miniint = i;
                    minitable = disturn[i];
                }
            }
        }
        int j = 0;
        while(gather[j] != 10)
            j++;
        gather[j] = miniint;
        for(i = 0; i < 8; i++)
        {
            if(!IsGather(i))
            {
                if(disturn[i].turn > (minitable + data[miniint][i]).turn)
                {
                    disturn[i] = minitable + data[miniint][i];
                }
            }
        }
        j = 0;
        while(gather[j] != 10)
            j++;
        if(j >= 8)
        {
            int i;
            cout<<strsource<<"->  (Least Turn)\n";
            for(i = 0; i < 8; i++)
            {
                if(disturn[i].number != "0000")
                    disturn[i].Show();
            }
        }
        else
        {
            LeastTurn();
        }
    }

};

int main()
{
    PrefectPlan t;;
    return 0;
}
