#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include<fstream>
#include"windows.h"

using namespace std;
/*
让我来细致地总结下算所有道路的超累算法：
1.建造两个栈，一个1栈用来存储成功的一条路上的点；另一个2栈用来回溯至原来分叉的点(包括另一个栈上的点)从而寻找下一条可能的路线。
2.判断所有的方向，有可能通的都压到2栈里，然后选择2栈顶的点存入1栈，并标记此点为3，若没有可能的点，则标记此点为2，且下一点为2栈的顶点；直到入口。
3.回退：回退至1栈和2栈不同的点，将起点设为2栈的点，且清空所有的2，退1栈的同时清空对应的3（因为上半截的点不能碰，其实后来发现无所谓，下方会解释）
4.找新路：重复 回退+第2步，直到2栈空/起点为入口。
PS：如何防止找新路时返回到起点之前？回退时定义截至步数为起点步数，走第二步时加一个判断，小于截至步数则说明失败。
PS：发现后面重复找路，因为2栈存了两个步数一样的出口，怎么办？回退时加一个判断，起点为入口&&步数相同 时，2栈再次回退。
PS：如果路太多，电脑会满，请调试人员注意不要故意加很多路呦~~
此刻需要掌声！！！！pia~pia~pia~谢谢灯光，谢谢舞美，谢谢观众！
*/
/*
看完老师的八皇后简介递归代码，顿时觉得我的这个算法好像白白浪费了递归算法，但由于是在不想在烧脑，所以在此想想简单的思路。
bool placeQueens(int* queenList, int row)  {
	bool foundLocation;
	if(到达终点)
    {
        展示小栈里的所有导出一条路。
        回溯到大小栈不相同的地方；
        沿路将标记过的点清空。
        if(大栈空了)
            return false;
        else
            调用自己。
    }
	else
    {
	      把所有的走一步可能到的点都存入大栈。
	      如果有点，调用这个点，小栈存起。
	      如果没有，退回上个点。小栈弹出。
    }
}
*/



struct Coord
{
    int x;
    int y;
    int step;
    Coord(int xi = 0, int yi = 0, int stepi = 0):x(xi),y(yi),step(stepi){}
    Coord(const Coord &c)
    {
        x = c.x;
        y = c.y;
        step = c.step;
    }
    bool operator==(const Coord& other)
    {
        if(other.x == x&&other.y == y&&other.step == step)
            return true;
        else
            return false;
    }
};
class ZuJi{
public:
    ZuJi()
    {
        top = -1;
    };
    ZuJi(ZuJi &z)
    {
        Coord way;
        ZuJi temp;
        while(!z.IsEmpty())
        {
            z.Pop(way);
            temp.Push(way);
            Push(way);
        }
        while(!z.IsEmpty())
        {
            temp.Pop(way);
            z.Push(way);
        }
    };
    void Push(Coord const x)
    {
        if(top+1 == 90)
        {
            cout<<"FULL.\n";
            exit(0);
        }
        element[++top] = Coord(x);
    }
    void Pop(Coord &x)
    {
        if(top == -1)
        {
            cout<<"Sorry, I'm missing (i-i).\n";
            exit(0);
        }
        x = Coord(element[top]);
        top--;
    }
    bool IsEmpty()
    {
        if(top == -1)
            return true;
        return false;
    }
    Coord GetTop()
    {
        return element[top];
    }
    Coord Get(int num)
    {
        return element[num];
    }
    int top;
private:
    Coord element[200];

};


class ZouMiGong{
public:
    ZouMiGong()
    {
        ifstream fin("input.txt",ios::in);
        fin>>maxx>>maxy;
        int i,j;
        for(i = 0; i < maxx; i++)
            for(j = 0; j < maxy; j++)
                fin>>MiGong[i][j];
        for(i = 0; i < maxx; i++)
            for(j = 0; j < maxy; j++)
                TrueMiGong[i][j] = MiGong[i][j];
        int x,y;
        fin>>x>>y;
        current = Coord(x,y,0);
        start = Coord(x,y,0);
        fin>>x>>y;
        ending = Coord(x,y);
        zuji.Push(current);
        fin.close();
        StaticStep = 100;
        Fall = false;
    };
    bool S(Coord &current)
    {
        if(current.x >= 1 && MiGong[current.x-1][current.y] == 0)
        {
            current.x--;
            current.step++;
            return true;
        }
        else
        {
            return false;
        }

    }
    bool X(Coord &current)
    {
        if(current.x <= maxx - 2 && MiGong[current.x+1][current.y] == 0)
        {
            current.x++;
            current.step++;
            return true;
        }
        else
        {
            return false;
        }
    }
    bool Z(Coord &current)
    {
        if(current.y >= 1 && MiGong[current.x][current.y-1] == 0)
        {
            current.y--;
            current.step++;
            return true;
        }
        else
        {
            return false;
        }
    }
    bool Y(Coord &current)
    {
        if(current.y <= maxy - 2 && MiGong[current.x][current.y+1] == 0)
        {
            current.y++;
            current.step++;
            return true;
        }
        else
        {
            return false;
        }
    }
    bool ZS(Coord &current)
    {
        if(current.y >= 1 && current.x >= 1 && MiGong[current.x-1][current.y-1] == 0)
        {
            current.x--;
            current.y--;
            current.step++;
            return true;
        }
        else
        {
            return false;
        }
    }
    bool ZX(Coord &current)
    {

        if(current.y <= maxy - 2 && current.x >= 1 && MiGong[current.x-1][current.y+1] == 0)
        {
            current.x--;
            current.y++;
            current.step++;
            return true;
        }
        else
        {
            return false;
        }
    }
    bool YS(Coord &current)
    {

        if(current.x <= maxx - 2 && current.y >= 1 && MiGong[current.x+1][current.y-1] == 0)
        {
            current.x++;
            current.y--;
            current.step++;
            return true;
        }
        else
        {
            return false;
        }
    }
    bool YX(Coord &current)
    {
        if(current.x <= maxx - 2 && current.y <= maxx - 2 && MiGong[current.x+1][current.y+1] == 0)
        {
            current.x++;
            current.y++;
            current.step++;
            return true;
        }
        else
        {
            return false;
        }
    }
    void ZouQi()
    {
        while(!(current.x == ending.x && current.y == ending.y))
        {
            bool success = false;
            Coord remain = current;
            if (ZS(current)){ backup.Push(current);current = remain; success = true;}
            if (Z(current)){ backup.Push(current);current = remain;success = true;}
            if (ZX(current)){ backup.Push(current);current = remain;success = true;}
            if (YS(current)){ backup.Push(current);current = remain; success = true;}
            if (S(current)){ backup.Push(current);current = remain;success = true;}
            if (X(current)){ backup.Push(current);current = remain;success = true;}
            if (Y(current)){ backup.Push(current);current = remain;success = true;}
            if(YX(current)){ backup.Push(current);current = remain;success = true;}
            if(success)
            {
                zuji.Push(backup.GetTop());
                current = backup.GetTop();
                MiGong[current.x][current.y] = 3;
            }
            else if(current.step <= StaticStep)
            {
                Fall = true;
                break;
            }

            else
            {
                zuji.Pop(current);
                backup.Pop(current);
                current = zuji.GetTop();
                MiGong[current.x][current.y] = 2;
            }
        }
        ending.step = current.step;
        if(!Fall)
            ZhanShi();
    }
void BackSpace()
    {
        int i,j;
        for(i = 0; i < maxx; i++)
            for(j = 0; j < maxy; j++)
                if(MiGong[i][j] == 2)
                {
                    MiGong[i][j] = 0;
                }
        Coord backpoint , zujipoint;
        zuji.Pop(zujipoint);
        MiGong[zujipoint.x][zujipoint.y] = 0;
        backup.Pop(backpoint);
        MiGong[backpoint.x][backpoint.y] = 0;
        zuji.Pop(zujipoint);
        MiGong[zujipoint.x][zujipoint.y] = 0;
        backup.Pop(backpoint);
        MiGong[backpoint.x][backpoint.y] = 0;
        if(backpoint == ending)
            backup.Pop(backpoint);
        while(zujipoint == backpoint)
        {
           // if(zuji.Get(zuji.top-1) == backup.Get(backup.top-1))
                MiGong[zujipoint.x][zujipoint.y] = 0;
           // else
              //  MiGong[zujipoint.x][zujipoint.y] = 2;
            zuji.Pop(zujipoint);
            backup.Pop(backpoint);
        }
        current = backpoint;
        if(current.x == start.x && current.y == start.y)
        {
            cout<<"Here are all ways!\n";
            exit(0);
        }
        zuji.Push(zujipoint);
        MiGong[zujipoint.x][zujipoint.y] = 3;
        MiGong[backpoint.x][backpoint.y] = 3;
        zuji.Push(backpoint);
        backup.Push(backpoint);
        StaticStep = current.step;
        Fall = false;
    }
void ZouQi2()
    {
        while(!backup.IsEmpty())
        {
           BackSpace();
           ZouQi();
        }
    }

void KaiTouZhanShi()
    {
        Coord way;
        ZuJi zuji1;
        int i, j;
        for(i = 0; i < maxx; i++)
        {
            for(j = 0; j < maxy; j++)
            {
                if(TrueMiGong[i][j] == 1)
                {
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole,FOREGROUND_RED);
                    cout<<"# ";
                    SetConsoleTextAttribute(hConsole,FOREGROUND_RED | FOREGROUND_GREEN|FOREGROUND_BLUE);
                }
                else
                    cout<<TrueMiGong[i][j]<<" ";
            }
            cout<<endl;
        }
        cout<<"I'm ready...\n";
        cout<<"'#'-No,'0'-Yes,'*'-way\n";
    }
    void ZhanShi()
    {
        Coord way;
        int i, j;
        i = zuji.top;
        while(i >= 0)
        {
            way = zuji.Get(i);
            TrueMiGong[way.x][way.y] = 2;
            i--;
        }
        i = 0;
        while(i <= zuji.top)
        {
            way = zuji.Get(i);
            cout<<way.x<<","<<way.y<<" -> ";
            i++;
        }
        cout<<"^.^";
        cout<<"Altogether"<<ending.step<<" steps\n";
        for(i = 0; i < maxx; i++)
        {
            for(j = 0; j < maxy; j++)
            {
                if(TrueMiGong[i][j] == 2)
                {
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole,FOREGROUND_GREEN);
                    cout<<"* ";
                    SetConsoleTextAttribute(hConsole,FOREGROUND_RED | FOREGROUND_GREEN|FOREGROUND_BLUE);
                }
                else if(TrueMiGong[i][j] == 1)
                {
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole,FOREGROUND_RED);
                    cout<<"# ";
                    SetConsoleTextAttribute(hConsole,FOREGROUND_RED | FOREGROUND_GREEN|FOREGROUND_BLUE);
                }
                else
                    cout<<TrueMiGong[i][j]<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
        i = zuji.top;
        while(i >= 0)
        {
            way = zuji.Get(i);
            TrueMiGong[way.x][way.y] = 0;
            i--;
        }
    }
private:
    ZuJi zuji, backup;
    Coord current, start, ending;
    int StaticStep;
    int MiGong[9][9];
    int TrueMiGong[9][9];
    int maxx,maxy;
    bool Fall;
};

int main()
{
    ZouMiGong x;
    x.KaiTouZhanShi();
    x.ZouQi();
    x.ZouQi2();
    return 0;
}
