#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include"windows.h"
#include <math.h>
using namespace std;

struct Tree
{
    char name;
    int text;
    Tree *left;
    Tree *right;
    Tree(char namei = 0, int texti = 0, Tree *lefti = NULL, Tree *righti = NULL)
    {
        name = namei;
        text = texti;
        left = lefti;
        right = righti;
    }
    Tree(Tree &x)
    {
        name = x.name;
        text = x.text;
        left = x.left;
        right = x.right;
    }
};

class Forest
{
private:
    Tree *f[5];
    int Code[6][5];
    Tree *root;
    Tree whatever[20];
    int codes[100];
    int CodeLen;
public:
    Forest()
    {
        int i, j;
        for(i = 0; i < 6; i++)
            for(j = 0; j < 5; j++)
                Code[i][j] = 2;
        f[0] = new Tree('a', 4);
        f[1] = new Tree('b', 7);
        f[2] = new Tree('c', 5);
        f[3] = new Tree('d', 2);
        f[4] = new Tree('e', 9);
    }
    int Min()
    {
        int i = 0;
        while(f[i] == NULL)
            i++;
        int mini = i;
        for(i; i < 5; i++)
        {
            if(f[i] != NULL && f[i]->text < f[mini]->text)
                mini = i;
        }
        return mini;
    }
    void Set()
    {
        int i = 5;
        while(i > 1)
        {
            int static j = 0;
            whatever[j] = *f[Min()];
            j++;
            f[Min()]->text = 999;
            //delete f[Min()];
            whatever[j] =*f[Min()];
            j++;
            f[Min()]->right = &whatever[j-1];//此处错误：不静态出了括号就没有了->静态无法更新->在外建大数组whatever.
            f[Min()]->left = &whatever[j-2];
            f[Min()]->text += whatever[j-2].text;
            i--;
        }
        root = f[Min()];
    }
    void SetCode(Tree *t, int addcode, int next)
    {
        if(next >= 0)
            Code[5][next] = addcode;
        if(t->left != NULL)
        {
            SetCode(t->left, 0, next+1);
        }
        if(t->right != NULL)
        {
            SetCode(t->right, 1, next+1);
        }
        if(t->right == NULL && t->left == NULL)
        {
            int i;
            for(i = 0; i <= next; i++)//Code[][] != 2->next 原因是上一级的数组值会覆盖掉2。
            {
                Code[int(t->name-'a')][i] = Code[5][i];
            }
        }
    }
    void Show()
    {
        Set();
        SetCode(root, 2, -1);
        cout<<"SetCode\n";
        int i,j;
        int a[5] = {4,7,5,2,9};
        for(i = 0; i < 5; i++)
        {
            cout<<char(i+'a')<<"-"<<a[i]<<":";
            for(j = 0; Code[i][j] != 2; j++)
                cout<<Code[i][j]<<" ";
            cout<<endl;
        }
        cout<<"ENTER CODES:(2-END)\n";
        char ch;//尝试 int 失败，录入时无法连续判断,因为一大串数字他以为是一个大数。
        i = 0;
        while((ch = getchar()) != '2' && ch != '\n')
        {
            codes[i] = int(ch - '0');
            i++;
        }
        codes[i] = 2;
        CodeLen = i;
        Translate(0);
    }
    //因为这里任意两位长度码与三位长度码前两位都不同，所以不用考虑冲突取哪个的问题，即一股脑向后翻译。
    //二次觉悟：不可能出现要考虑的问题，因为之所以称其为译码，意思就是不会有两位长度码与三位长度码前两位相同的情况。
    void Translate(int start)
    {
        int result = 0;
        if(start+1 < CodeLen)
        {
            if(codes[start] == 1)
            {
                result = 2;
                if(codes[start+1] == 1)
                    cout<<"e";
                else
                    cout<<"b";
            }
            else if(codes[start+1] == 0)
            {
                result = 2;
                cout<<"c";
            }
        }
        if(result == 0 && start+2 < CodeLen )
        {
            result = 3;
            if(codes[start+2] == 0)
                    cout<<"d";
                else
                    cout<<"a";
        }
        if(result != 0)
            Translate(start+result);
        else
        {
            cout<<"\nThat's all\n";
            exit(0);
        }


    }
};

int main()
{
    Forest t;
    t.Show();
    return 0;
}
