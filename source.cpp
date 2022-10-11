#include <bits/stdc++.h>
using namespace std;

class node
{
    public:
    
    int id;
    string firstname;
    string lastname;
    int phone;
    string *address;
    string designation;
    string department;
    int salary;
    
    static int i;
    node* lchild;
    node* rchild;
    int height;

    node(){}
    node(string f,string l,int p,string a[],string de,string d,int s)
    {
        id=i++;
        firstname=f;
        lastname=l;
        phone=p;
        address=new string[4];
        address=a;
        designation=de;
        salary=s;
    }
};
int node::i=1;

class Employee_record
{
    public:
    node* root;
    
    Employee_record()
    {
        root=NULL;
    }
    
    int NodeHeight(node *p) // return height of the tree
    {
        int hl,hr;
        hl=(p && p->lchild)?p->lchild->height:0;
        hr=(p && p->rchild)?p->rchild->height:0;
        return hl>hr?hl+1:hr+1;
    }
    
    int BalanceFactor(node *p)
    {
        int hl,hr;
        hl=(p && p->lchild)?p->lchild->height:0;
        hr=(p && p->rchild)?p->rchild->height:0;
        return hl-hr;
    }
    
    node* LLRotation(node* p)
    {
        node* pl=p->lchild;
        node* plr=pl->rchild;
        
        //changing links
        pl->rchild=p;
        p->lchild=plr;
        
        //updating height
        p->height=NodeHeight(p);
        pl->height=NodeHeight(pl);
        
        //updating root
        if(root==p)
        root=pl;
        return pl;
    }
    
    node* RRRotation(node* p)
    {
        node* pr=p->rchild;
        node* prl=p->lchild;
        
        //changing links
        pr->lchild=p;
        p->rchild=prl;
        
        //updating heights;
        p->height=NodeHeight(p);
        pr->height=NodeHeight(pr);
        
        //updating root
        if(root==p)
        root=pr;
        return pr;
    }
    
    node*LRRotation(node *p)
    {
        node* pl=p->lchild;
        node* plr=pl->rchild;
        
        //changing links
        pl->rchild=plr->lchild;
        p->lchild=plr->lchild;
        plr->lchild=pl;
        plr->rchild=p;
        
        //updating heights
        pl->height=NodeHeight(pl);
        p->height=NodeHeight(p);
        plr->height=NodeHeight(plr);
        
        //updating root
        if(p==root)
        root=plr;
        return plr;
    }
    
    node* RLRotation(node *p)
    {
        node* pr=p->rchild;
        node* prl=pr->lchild;
        
        //changing links
        pr->lchild=prl->rchild;
        p->rchild=prl->lchild;
        prl->rchild=pr;
        prl->lchild=p;
        
        //updating height
        pr->height=NodeHeight(pr);
        p->height=NodeHeight(p);
        prl->height=NodeHeight(prl);
        
        //updating root
        if(root==p)
        root=prl;
        return prl;
    }
};






int main()
{
    cout<<"Hello World";

    return 0;
}
