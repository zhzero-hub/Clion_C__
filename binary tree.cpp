#include<stdio.h>
#include<stdlib.h>

struct Node
{
    int data;
    Node *l;
    Node *r;
    int h;
};

struct Tree
{
    Node *base = NULL;
};

int max(int a , int b)
{
    if(a > b)return a;
    else return b;
}

int Gethight(Node *x)
{
    if(x == NULL || (x->l == NULL && x->r == NULL))return 0;
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
    if(x == NULL)
    {
        x = (Node *)malloc(sizeof(Node));
        x->data = t;
        x->l = x->r = NULL;
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
    x.base->l = NULL;
    x.base->r = NULL;
}

void Insert(Node *x , int t)//小于在左，大于在右
{
    Node *p = x;
    if(t <= p->data)
    {
        if(p->l == NULL)
        {
            Node *q = (Node *)malloc(sizeof(Node));
            q->data = t;
            q->l = q->r = NULL;
            p->l = q;
            return;
        }
        else
        {
            Insert(p->l , t);
            return;
        }
    }
    else
    {
        if(p->r == NULL)
        {
            Node *q = (Node *)malloc(sizeof(Node));
            q->data = t;
            q->l = q->r = NULL;
            p->r = q;
            return;
        }
        else
        {
            Insert(p->r , t);
            return;
        }
    }
}

Node *Findmin(Node *x)
{
    Node *p = x;
    while(p->l != NULL)p = p->l;
    return p;
}

Node *Findmax(Node *x)
{
    Node *p = x;
    while(p->r != NULL)p = p->r;
    return p;
}

Node *Delete(Node *x , int t)
{
    if(x == NULL)
    {
        return x;
    }
    if(t < x->data)x->l = Delete(x->l , t);
    else if(t > x->data)x->r = Delete(x->r , t);
    else
    {
        if(x->l != NULL && x->r != NULL)
        {
            Node *temp = Findmin(x->r);
            x->data = temp->data;
            x->r = Delete(x->r , x->data);
        }
        else if (x->l == NULL)
        {
            Node *temp = x;
            x = x->r;
            free(temp);
        }
        else if(x->r == NULL)
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
    if(node != NULL)
    {
        in_order(node->l);
        printf("%d " , node->data);
        in_order(node->r);
    }
    return;
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
    system("pause");
}