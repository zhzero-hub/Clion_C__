//
// Created by Z_HAO on 2019/11/27.
//

#include <iostream>

struct Node
{
    int data = 0;
    Node *l = nullptr;
    Node *r = nullptr;
    int h = 0;
};

struct Tree
{
    Node *base = nullptr;
};

int max(int a , int b)
{
    if(a > b)return a;
    else return b;
}

int Gethight(Node *x)
{
    if(x == nullptr || (x->l == nullptr && x->r == nullptr))return 0;
    else
    {
        return max(Gethight(x->l) , Gethight(x->r)) + 1;
    }
}

Node *RR_rotation(Node *x)
{
    Node *p = x->r;
    x->r = p->l;
    p->l = x;
    x->h = max(Gethight(x->l) , Gethight(x->r)) + 1;
    p->h = max(Gethight(p->l) , x->h) + 1;
    return p;
}

Node *LL_rotation(Node *x)
{
    Node *p = x->l;
    x->l = p->r;
    p->r = x;
    x->h = max(Gethight(x->l) , Gethight(x->r)) + 1;
    p->h = max(Gethight(p->l) , x->h) + 1;
    return p;
}

Node *LR_rotation(Node *x)
{
    x->l = RR_rotation(x->l);
    return LL_rotation(x);
}

Node *RL_rotation(Node *x)
{
    x->r = LL_rotation(x->r);
    return RR_rotation(x);
}

Node *Ballance_insert(Node *x , int t)
{
    if(x == nullptr)
    {
        x = (Node *)malloc(sizeof(Node));
        x->data = t;
        x->l = x->r = nullptr;
        x->h = 0;
        return x;
    }
    else
    {
        if(t < x->data)
        {
            x->l = Ballance_insert(x->l , t);
            if(Gethight(x->l) - Gethight(x->r) == 2)
            {
                if(t < x->l->data)//LL
                {
                    x = LL_rotation(x);
                }
                else
                {
                    x = LR_rotation(x);
                }
            }
        }
        else
        {
            x->r = Ballance_insert(x->r , t);
            if(Gethight(x->l) - Gethight(x->r) == -2)
            {
                if(t > x->r->data)//RR
                {
                    x = RR_rotation(x);
                }
                else
                {
                    x = RL_rotation(x);
                }
            }
        }

    }
    x->h = max(Gethight(x->l) , Gethight(x->r)) + 1;
    return x;
}

void newnode(Tree &x , int t)
{
    x.base = (Node *)malloc(sizeof(Node));
    x.base->data = t;
    x.base->l = nullptr;
    x.base->r = nullptr;
}

Node *Findmin(Node *x)
{
    Node *p = x;
    while(p->l != nullptr)p = p->l;
    return p;
}

Node *Findmax(Node *x)
{
    Node *p = x;
    while(p->r != nullptr)p = p->r;
    return p;
}

Node *Delete(Node *x , int t)
{
    if(x == nullptr)return x;
    if(t < x->data)
    {
        x->l = Delete(x->l , t);
        if(Gethight(x->r) - Gethight(x->l) >= 2)
        {
            if(Gethight(x->r->r) - Gethight(x->r->l) >= 2)
            {
                x = RR_rotation(x);
            }
            else
            {
                x = RL_rotation(x);
            }
        }
        x->h = max(Gethight(x->l) , Gethight(x->r)) + 1;
    }
    else if(t > x->data)
    {
        x->r = Delete(x->r , t);
        if(Gethight(x->l) - Gethight(x->r) >= 2)
        {
            if(Gethight(x->l->l) - Gethight(x->l->r) >= 2)
            {
                x = LL_rotation(x);
            }
            else
            {
                x = LR_rotation(x);
            }
        }
        x->h = max(Gethight(x->l) , Gethight(x->r)) + 1;
    }
    else
    {
        if(x->l != nullptr && x->r != nullptr)
        {
            if(Gethight(x->l) < Gethight(x->r))
            {
                Node *temp = Findmin(x->r);
                x->data = temp->data;
                x->r = Delete(x->r , x->data);
            }//右子树更高，从右子树删除
            else
            {
                Node *temp = Findmax(x->l);
                x->data = temp->data;
                x->r = Delete(x->l , x->data);
            }
        }
        else if (x->l == nullptr)
        {
            Node *temp = x;
            x = x->r;
            free(temp);
        }
        else if(x->r == nullptr)
        {
            Node *temp = x;
            x = x->l;
            free(temp);
        }
        return x;
    }
}

void in_order(Node *node)
{
    if(node != nullptr)
    {
        in_order(node->l);
        printf("%d " , node->data);
        in_order(node->r);
    }
}



int main()
{
    Tree tree;
    int a[] = {324,432,3,24,235,32,3242};
    int size = sizeof(a) / sizeof(a[0]);
    for(int i = 0;i < size;i ++)
    {
        tree.base = Ballance_insert(tree.base , a[i]);
    }
    Delete(tree.base , 3);
    in_order(tree.base);
}