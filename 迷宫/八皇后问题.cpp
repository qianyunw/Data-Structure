#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include<fstream>
#include"windows.h"
/*
����С�᣺�ۺϸо����Թ�������·���ƣ���ʹ�û��ݷ���
��������Ҫ�������������ƶ���������һ����Ӧ�ü�¼һ��·��ջ�����ٿյ�Σ�գ���Ҫ�����жϡ�
PS������СС��δ��֮��δ�ҿ��������Դֲڵ��ڸǡ�
*/
/*
������ʦ�Ĵ����Բ��λ�....
�ڴ�������ʦ�ļ�龫�����롣
bool placeQueens(int* queenList, int row)  {
	bool foundLocation;
	if (row == 8)   {		// ��ֹ����
		foundLocation = true;
	}  else {
	      foundLocation = false;
	      int col = 0;	// �ӵ�0�п�ʼ
   	      while (col < 8 && !foundLocation) {
		  if (safeLocation(row, col, queenList)) {     // ����(row,col)��ȫ
		        queenList[row] = col;  // �ڷ���(row,col)���ûʺ�
		        // �ݹ鲽�裬���Խ��ʺ�ŵ���row+1��
		       foundLocation = placeQueens(queenList, row + 1);
		       if (!foundLocation)  // ��ǰ�в��ܽ�����⣬ʹ����һ��
		           col ++;
		       }
		      else { 	 // ����(row,col)����ȫ��������һ��
		           col ++;
		      }
		}
	}
	return foundLocation;  // ��true��false���ص�ǰһ��
}

*/
using namespace std;
struct Coord
{
    int x;
    int y;
    Coord(int xi = 0, int yi = 0, int stepi = 0):x(xi),y(yi){}
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
         //   cout<<"Sorry, I'm missing (i-i).\n";
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


class QiPan{
public:
    QiPan()
    {
        int i,j;
        for(i = 0; i < 8; i++)
            for(j = 0; j < 8; j++)
                {
                    Pan[i][j] = 0;
                    TruePan[i][j] = 0;
                }
        current = Coord(0,0);
        time = 0;
    };
    bool Judge(Coord current)//�ǵ�wei�������жϡ�
    {
        int i,j,hang = 0, lie = 0, zheng = 0, fu = 0;
        for(i = current.x, j = 0; j < 8; j++)
        {
            if(Pan[i][j] == 1)
                hang++;
        }
        for(j = current.y, i = 0; i < 8; i++)
        {
            if(Pan[i][j] == 1)
                lie++;
        }
        for(i = current.x, j = current.y; i < 8 && j < 8; j++, i++)
        {
            if(Pan[i][j] == 1)
                zheng++;
        }
        for(i = current.x - 1, j = current.y - 1; i >=0 && j >=0; j--, i--)
        {
            if(Pan[i][j] == 1)
                zheng++;
        }
        for(i = current.x, j = current.y; i < 8 && j >= 0; j--, i++)
        {
            if(Pan[i][j] == 1)
                fu++;
        }
        for(i = current.x - 1, j = current.y + 1; i >= 0 && j < 8; j++, i--)
        {
            if(Pan[i][j] == 1)
                fu++;
        }
        if(zheng == 0 && fu == 0 && hang == 0 &&lie == 0)
            return true;
        else
            return false;

    }
    void ZouQi()
    {
        int i,j;
        for(i = current.x; i < 8; i++)
        {
            int t;
            for(j = 0; j < 8; j++)
            {
                if(Judge(Coord(i,j)))//zhuyi
                {
                    backup.Push(Coord(i,j));
                    current = Coord(i,j);
                    //cout<<current.x<<current.y<<endl;
                }
            }
            if(current.x == i)
            {
                zuji.Push(backup.GetTop());
                Pan[backup.GetTop().x][backup.GetTop().y] = 1;
               // cout<<backup.GetTop().x<<backup.GetTop().y<<endl;
            }
            else
                return;//����ͷ��
        }
        time++;
        cout<<time<<endl;
        int k = 0;
       // while(!(backup.Get(k)==backup.GetTop()))
        //{
        //    cout<<backup.Get(k).x<<backup.Get(k).y<<endl;
        //    k++;
       // }
        ZhanShi();
    }
void BackSpace()
    {
        int i,j;
        Coord backpoint , zujipoint;
        backup.Pop(backpoint);
        zuji.Pop(zujipoint);
        Pan[zujipoint.x][zujipoint.y] = 0;
        while(zujipoint == backpoint)
        {
            Pan[zujipoint.x][zujipoint.y] = 0;

            if(zuji.IsEmpty())
            {
                backup.Pop(current);
                zuji.Push(current);
                Pan[current.x][current.y] = 1;
                current.x++;
                return;
            }
            zuji.Pop(zujipoint);
            if(backup.IsEmpty())
                    cout<<"OVER."<<endl;
            backup.Pop(backpoint);
        }
        int m,n = 0;
        //cout<<"zujipoint.x][zujipoint.y"<<zujipoint.x<<zujipoint.y<<endl;
       // cout<<"backpoint.x][backpoint.y"<<backpoint.x<<backpoint.y<<endl;
        zuji.Push(zujipoint);
        Pan[zujipoint.x][zujipoint.y] = 1;
        Pan[backpoint.x][backpoint.y] = 1;
        backup.Push(backpoint);
        current.x = backpoint.x;
        for(m = 0; m < 8; m++)
        {
            if(Pan[0][m] == 1)
                n++;
        }
        if(n == 2)
            Pan[0][6] = 0;//��Ȼ�������Ϊʲô0 6 ��1 ������ȷʵ���ˡ�
       // cout<<current.x<<current.y<<endl;
       // ZhanShi();
    }
void ZouQi2()
    {
        if(backup.IsEmpty())
            return ;
        else
        {
            BackSpace();
            ZouQi();
            ZouQi2();
        }
    }//while СС�ظĳ��˵ݹ顣

void KaiTouZhanShi()
    {
        int i, j;
        for(i = 0; i < 8; i++)
        {
            for(j = 0; j < 8; j++)
            {
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole,FOREGROUND_RED);
                cout<<"# ";
                SetConsoleTextAttribute(hConsole,FOREGROUND_RED | FOREGROUND_GREEN|FOREGROUND_BLUE);
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
        for(i = 0; i < 8; i++)
        {
            for(j = 0; j < 8; j++)
            {
                if(Pan[i][j] == 1)
                {
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole,FOREGROUND_GREEN);
                    cout<<"* ";
                    SetConsoleTextAttribute(hConsole,FOREGROUND_RED | FOREGROUND_GREEN|FOREGROUND_BLUE);
                }
                else
                {
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole,FOREGROUND_RED);
                    cout<<"# ";
                    SetConsoleTextAttribute(hConsole,FOREGROUND_RED | FOREGROUND_GREEN|FOREGROUND_BLUE);
                }
            }
            cout<<endl;
        }
        cout<<endl;
        i = zuji.top;
    }
private:
    ZuJi zuji, backup;
    int time;
    Coord current;
    int Pan[8][8];
    int TruePan[8][8];
};

int main()
{
    QiPan q;
    q.KaiTouZhanShi();
    q.ZouQi();
    q.ZouQi2();
    return 0;
}
