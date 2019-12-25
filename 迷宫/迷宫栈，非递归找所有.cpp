#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include<fstream>
#include"windows.h"

using namespace std;
/*
������ϸ�µ��ܽ��������е�·�ĳ����㷨��
1.��������ջ��һ��1ջ�����洢�ɹ���һ��·�ϵĵ㣻��һ��2ջ����������ԭ���ֲ�ĵ�(������һ��ջ�ϵĵ�)�Ӷ�Ѱ����һ�����ܵ�·�ߡ�
2.�ж����еķ����п���ͨ�Ķ�ѹ��2ջ�Ȼ��ѡ��2ջ���ĵ����1ջ������Ǵ˵�Ϊ3����û�п��ܵĵ㣬���Ǵ˵�Ϊ2������һ��Ϊ2ջ�Ķ��㣻ֱ����ڡ�
3.���ˣ�������1ջ��2ջ��ͬ�ĵ㣬�������Ϊ2ջ�ĵ㣬��������е�2����1ջ��ͬʱ��ն�Ӧ��3����Ϊ�ϰ�صĵ㲻��������ʵ������������ν���·�����ͣ�
4.����·���ظ� ����+��2����ֱ��2ջ��/���Ϊ��ڡ�
PS����η�ֹ����·ʱ���ص����֮ǰ������ʱ�����������Ϊ��㲽�����ߵڶ���ʱ��һ���жϣ�С�ڽ���������˵��ʧ�ܡ�
PS�����ֺ����ظ���·����Ϊ2ջ������������һ���ĳ��ڣ���ô�죿����ʱ��һ���жϣ����Ϊ���&&������ͬ ʱ��2ջ�ٴλ��ˡ�
PS�����·̫�࣬���Ի������������Աע�ⲻҪ����Ӻܶ�·��~~
�˿���Ҫ������������pia~pia~pia~лл�ƹ⣬лл������лл���ڣ�
*/
/*
������ʦ�İ˻ʺ���ݹ���룬��ʱ�����ҵ�����㷨����װ��˷��˵ݹ��㷨�����������ڲ��������ԣ������ڴ�����򵥵�˼·��
bool placeQueens(int* queenList, int row)  {
	bool foundLocation;
	if(�����յ�)
    {
        չʾСջ������е���һ��·��
        ���ݵ���Сջ����ͬ�ĵط���
        ��·����ǹ��ĵ���ա�
        if(��ջ����)
            return false;
        else
            �����Լ���
    }
	else
    {
	      �����е���һ�����ܵ��ĵ㶼�����ջ��
	      ����е㣬��������㣬Сջ����
	      ���û�У��˻��ϸ��㡣Сջ������
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
