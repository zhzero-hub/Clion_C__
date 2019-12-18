#include<iostream>
struct Node
{
    int data;
    Node *l;
    Node *r;
};
struct Tree
{
    Node *base;
};

Tree Newtree()
{
    Tree temp;
    temp.base = (Node *)malloc(sizeof(Node));
    temp.base->data = 0;
    temp.base->l = temp.base->r = NULL;
    return temp;
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

Node *Find(Node *x , int t)
{
    if(t == x->data || x == NULL)
    {
        return x;
    }
    if(t < x->data)
    {
        return Find(x->l , t);
    }
    else if(t > x->data)
    {
        return Find(x->r , t);
    }
}

void Insert(Node *x , int t)
{
    Node *temp = x;
    while(temp != NULL)
    {
        if(t <= temp->data)
        {
            temp = temp->l;
        }
        else
        {
            temp = temp->r;
        }
    }
    temp = (Node *)malloc(sizeof(Node));
    return;
}

Node *Delete(Node *x , int t)
{
    if(t < x->data)x = Delete(x->l , t);
    else if(t > x->data)x = Delete(x->r , t);
    if(x->l != NULL && x->r !=- NULL)
    {
        Node *q = Findmin(x->r);
        x->data = q->data;
        x->r = Delete(x , x->data);
    }
    else
    {
        Node *p = x;
        if(x->l != NULL)
        {
            x = x->l;
        }
        else if(x->r != NULL)
        {
            x = x->r;
        }
        free(p);
    }
    return x;
}