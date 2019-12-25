#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include"windows.h"
#include <math.h>
using namespace std;

struct Cell
{
    int text;
    int step;
    Cell *left;
    Cell *right;
    Cell(int texti = 0, Cell *lefti = NULL, Cell *righti = NULL):step(0)
    {
        text = texti;
        left = lefti;
        right = righti;
    }
    Cell(Cell &x)
    {
        step = x.step;
        text = x.text;
        left = x.left;
        right = x.right;
    }
};

class Line{
public:
    Line()
    {
        tail = -1;
        head = -1;

    };
    void Push(Cell *&x)
    {
        if(head+1 == 90)
        {
            cout<<"FULL.\n";
            exit(0);
        }
        element[++head] = x;
    }
    Cell*& Pop()
    {
        if(tail > head)
        {
            cout<<"Sorry, I'm missing (i-i).\n";
            exit(0);
        }
        if(tail == -1)
            tail++;
        return *&element[tail++];
    }
    bool IsEmpty()
    {
        if(tail > head)
            return true;
        return false;
    }
private:
    Cell* element[90];
    int head;
    int tail;
};


class Stack{
public:
    Stack()
    {
        top = -1;
    };
    void Push(Cell *&x)
    {
        if(top+1 == 90)
        {
            cout<<"FULL.\n";
            exit(0);
        }
        element[++top] = x;
    }
    Cell*& Pop()
    {
        if(top == -1)
        {
            cout<<"Sorry, I'm missing (i-i).\n";
            exit(0);
        }
        return *&element[top--];
    }
    bool IsEmpty()
    {
        if(top == -1)
            return true;
        return false;
    }
    int top;
private:
    Cell* element[90];

};

class Tree
{
private:
    int depth;
    int width;
    int door0;
    int door1;
    int door2;
    int *w;
    int MAX;
    Stack DelStack;
public:
    Cell *root;
    Tree()
    {
        root = NULL;
        door0 = 0;
        door1 = 0;
        door2 = 0;
        depth = 0;
        width = 0;
        MAX = 0;
    }
    void Set(Cell *&root)
    {
        int item;
        cin>>item;
        if(item != 0)
        {
            root = new Cell(item);
            Set(root->left);
            Set(root->right);
        }
        else
            root = NULL;
    }
    void SetStep()
    {
        static Line line;
        static int j = 1;
        if(j == 1)
        {
            line.Push(root);
            root->step = 1;
        }
        j++;
        if(line.IsEmpty())
            return ;
        Cell* temp = line.Pop();
        if(temp->left)
        {
            line.Push(temp->left);
            temp->left->step = temp->step+1;
        }
        if(temp->right)
        {
            line.Push(temp->right);
            temp->right->step = temp->step+1;
        }
        SetStep();
    }
    void Show(Cell *root)
    {
        cout<<root->text<<" ";
        if(root->left != NULL)
        {
            Show(root->left);
        }
        if(root->right != NULL)
        {
            Show(root->right);
        }
    }
    void ShowStep(Cell *root,int answer)
    {
        if(root->text == answer)
        {
            cout<<root->text<<" .Address: "<<root<<"\t.Step: "<<root->step<<endl;
        }
        if(root->left != NULL)
        {
            ShowStep(root->left,answer);
        }
        if(root->right != NULL)
        {
            ShowStep(root->right,answer);
        }
    }
    void FinalShow()
    {
        Door(root);
        cout<<"DU = 0:\t"<<door0<<endl;
        cout<<"DU = 1:\t"<<door1<<endl;
        cout<<"DU = 2:\t"<<door2<<endl;
        SetStep();
        Depth(root);
        cout<<"Depth:\t"<<depth<<endl;
        w = new int [depth + 1];
        int i = 0;
        memset(w,0,depth+1);
        for(i = 0; i < depth+1 ; i++)
        {
            w[i] = 0;
        }
        Width(root);
        for(i = 0; i < depth+1 ; i++)
        {
            if(width < w[i])
                width = w[i];
        }
        cout<<"Width:\t"<<width<<endl;
        Max(root);
        cout<<"MAX:\t"<<MAX<<endl;
        Show(root);
        cout<<"\nPlease choose a text from one of them.\n";
        int answer;
        cin>>answer;
        ShowStep(root,answer);
        Delete1(root);
        Delete2();
        cout<<"\nAfter deleting:\n";
        Show(root);
    }
    void JudgeDoor(Cell *root)
    {
        if(root->left && root->right)
        {
            door2++;
            return ;
        }
        if(root->left || root->right)
        {
            door1++;
            return ;
        }
        door0++;
    }
    void Door(Cell *root)
    {
        JudgeDoor(root);
        if(root->left != NULL)
        {
            Door(root->left);
        }
        if(root->right != NULL)
        {
            Door(root->right);
        }
    }
    void Depth(Cell *root)
    {
        if(root->left == NULL && root->right == NULL)
        {
            if(depth < root->step)
                depth = root->step;
        }
        if(root->left != NULL)
        {
            Depth(root->left);
        }
        if(root->right != NULL)
        {
            Depth(root->right);
        }
    }
    void Width(Cell *root)
    {
        w[root->step] += 1;
        if(root->left != NULL)
        {
            Width(root->left);
        }
        if(root->right != NULL)
        {
            Width(root->right);
        }
    }
    void Delete1(Cell *root)
    {
        if(root->left == NULL && root->right == NULL)
        {
            DelStack.Push(root);
        }
        if(root->left != NULL)
        {
            Delete1(root->left);
        }
        if(root->right != NULL)
        {
            Delete1(root->right);
        }
    }
    void Delete(Cell *root,Cell *del)
    {
        if(root->left == del)
        {
            delete del;
            root->left = NULL;
        }
        if(root->right == del)
        {
            delete del;
            root->right = NULL;
        }
        if(root->left != NULL)
        {
            Delete(root->left,del);
        }
        if(root->right != NULL)
        {
            Delete(root->right,del);
        }
    }
    void Delete2()
    {
        if(DelStack.IsEmpty())
        {
            return ;
        }
        Cell *del = DelStack.Pop();
        Delete(root,del);
        Delete2();
    }
    void Max(Cell *root)
    {
        if(MAX < root->text)
            MAX = root->text;
        if(root->left != NULL)
        {
            Max(root->left);
        }
        if(root->right != NULL)
        {
            Max(root->right);
        }
    }
};

int main()
{
    Tree t;
    t.Set(t.root);
    t.FinalShow();
    return 0;
}
//只找到了根。
