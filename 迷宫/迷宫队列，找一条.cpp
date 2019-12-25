#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include<fstream>
#include"windows.h"

using namespace std;

struct Coord
{
    int x;
    int y;
    Coord(int xi = 0, int yi = 0):x(xi),y(yi){}
    Coord(const Coord &c)
    {
        x = c.x;
        y = c.y;
    }
    bool operator==(const Coord& other)
    {
        if(other.x == x&&other.y == y)
            return true;
        else
            return false;
    }
};
class ZuJi{
public:
    ZuJi()
    {
        tail = -1;
        head = -1;

    };
    void Push(Coord const x)
    {
        if(head+1 == 90)
        {
            cout<<"FULL.\n";
            exit(0);
        }
        element[++head] = Coord(x);
    }
    void Pop(Coord &x)
    {
        if(tail > head)
        {
            cout<<"Sorry, I'm missing (i-i).\n";
            exit(0);
        }
        if(tail == -1)
            tail++;
        x = Coord(element[tail++]);

    }
    bool IsEmpty()
    {
        if(tail > head)
            return true;
        return false;
    }
    Coord GetTail()
    {
        return element[tail];
    }
    Coord& GetHead()
    {
        return element[head];
    }
    Coord Get(int num)
    {
        return element[num];
    }
private:
    Coord element[90];
    int head;
    int tail;
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
        current = Coord(x,y);
        start = Coord(x,y);
        fin>>x>>y;
        ending = Coord(x,y);
        zuji.Push(current);
        for(i = 0; i < maxx; i++)
            for(j = 0; j < maxy; j++)
                PMiGong[i][j] = Coord(0,0);
        fin.close();
    };
    bool S(Coord current)
    {
        if(current.x >= 1 && MiGong[current.x-1][current.y] == 0)
        {
            MiGong[current.x-1][current.y] = 1;
            current.x--;
            zuji.Push(current);
            PMiGong[current.x][current.y] = this->current;
            return true;
        }
        else
        {
            return false;
        }

    }
    bool X(Coord current)
    {
        if(current.x <= maxx - 2 && MiGong[current.x+1][current.y] == 0)
        {
            MiGong[current.x+1][current.y] = 1;
            current.x++;
            zuji.Push(current);
            PMiGong[current.x][current.y] = this->current;
            return true;
        }
        else
        {
            return false;
        }
    }
    bool Z(Coord current)
    {
        if(current.y >= 1 && MiGong[current.x][current.y-1] == 0)
        {
            MiGong[current.x][current.y-1] = 1;
            current.y--;
            zuji.Push(current);
            PMiGong[current.x][current.y] = this->current;
            return true;
        }
        else
        {
            return false;
        }
    }
    bool Y(Coord current)
    {
        if(current.y <= maxy - 2 && MiGong[current.x][current.y+1] == 0)
        {
            MiGong[current.x][current.y+1] = 1;
            current.y++;
            zuji.Push(current);
            PMiGong[current.x][current.y] = this->current;
            return true;
        }
        else
        {
            return false;
        }
    }
    bool ZS(Coord current)
    {
        if(current.y >= 1 && current.x >= 1 && MiGong[current.x-1][current.y-1] == 0)
        {
            MiGong[current.x-1][current.y-1] = 1;
            current.x--;
            current.y--;
            zuji.Push(current);
            PMiGong[current.x][current.y] = this->current;
            return true;
        }
        else
        {
            return false;
        }
    }
    bool ZX(Coord current)
    {

        if(current.y <= maxy - 2 && current.x >= 1 && MiGong[current.x-1][current.y+1] == 0)
        {
            MiGong[current.x-1][current.y+1] = 1;
            current.x--;
            current.y++;
            zuji.Push(current);
            PMiGong[current.x][current.y] = this->current;
            return true;
        }
        else
        {
            return false;
        }
    }
    bool YS(Coord current)
    {

        if(current.x <= maxx - 2 && current.y >= 1 && MiGong[current.x+1][current.y-1] == 0)
        {
            MiGong[current.x+1][current.y-1] = 1;
            current.x++;
            current.y--;
            zuji.Push(current);
            PMiGong[current.x][current.y] = this->current;
            return true;
        }
        else
        {
            return false;
        }
    }
    bool YX(Coord current)
    {
        if(current.x <= maxx - 2 && current.y <= maxx - 2 && MiGong[current.x+1][current.y+1] == 0)
        {
            MiGong[current.x+1][current.y+1] = 1;
            current.x++;
            current.y++;
            zuji.Push(current);
            PMiGong[current.x][current.y] = this->current;
            return true;
        }
        else
        {
            return false;
        }
    }
    void ZouQi()
    {
        while((!(current == ending)||zuji.IsEmpty()))
        {
            YX(current);
            Y(current);
            X(current);
            S(current);
            YS(current);
            Z(current);
            ZX(current);
            ZS(current);
            zuji.Pop(current);
            MiGong[current.x][current.y] = 1;
            current = zuji.GetTail();
            MiGong[current.x][current.y] = 1;
        }
    }
    void KaiTouZhanShi()
    {
        Coord way;
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
    }
    void ZhanShi()
    {
        Coord way;
        int i, j;
        TrueMiGong[current.x][current.y] = 2;
        cout<<"^.^";
        while(!(current == start))
        {

            current = PMiGong[current.x][current.y];
            cout<<" <-"<<current.x<<","<<current.y;
            TrueMiGong[current.x][current.y] = 2;
        }
        cout<<endl;
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
    }
private:
    ZuJi zuji;
    Coord current, start, ending;
    int MiGong[9][9];
    int TrueMiGong[9][9];
    Coord PMiGong[9][9];
    int maxx,maxy;
};

int main()
{
    ZouMiGong x;
    x.KaiTouZhanShi();
    x.ZouQi();
    x.ZhanShi();
    return 0;
}
