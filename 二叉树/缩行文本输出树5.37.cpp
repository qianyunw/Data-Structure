#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include"windows.h"
#include <math.h>
using namespace std;

//空格计数的方法是利用本想用队列记录层数，还好想了一个更简单的递归方法，相当于为每个点都记录了步数，爱上递归不解释...

struct Cell
{
    int text;
    Cell *child;
    Cell *sister;
    Cell(int texti = 0, Cell *childi = NULL, Cell *sisteri = NULL)
    {
        text = texti;
        child = childi;
        sister = sisteri;
    }
    Cell(Cell &x)
    {
        text = x.text;
        child = x.child;
        sister = x.sister;
    }
};

class Tree
{
private:
    int *w;
public:
    Cell *root;
    Tree()
    {
        root = NULL;
    }
    void Set(Cell *&root)
    {
        int item;
        cin>>item;
        if(item != 0)
        {
            root = new Cell(item);
            Set(root->child);
            Set(root->sister);
        }
        else
            root = NULL;
    }
    void Show(Cell *root,int step)
    {
        int j = step;
        while(j--)
            cout<<"\t";
        cout<<root->text<<endl;
        if(root->child != NULL)
        {
            Show(root->child,step+1);
        }
        if(root->sister != NULL)
        {
            Show(root->sister,step);
        }
    }

};

int main()
{
    Tree t;
    cout<<"Please enter your tree in first_child, text, next_sister order.\n";
    t.Set(t.root);
    t.Show(t.root,0);
    return 0;
}
