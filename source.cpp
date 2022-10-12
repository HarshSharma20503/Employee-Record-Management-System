#include <iostream>
#include <stdlib.h> //to use system("CLS")
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
    
    node* rinsert(node* p,node *q)
    {
           
    }
    node* deletion(node* p,int key)
    {
        
    }
    node* search(node* p)
    {
        
    }
    
    void insertEmployee()
    {
        
    }
    
    void deleteEmployee()
    {
        
    }
    void searchEmployee()
    {
        
    }
    void modifyEmployee()
    {
        
    }
    void display()
    {
        
    }
    void displayRecord(node* p)
    {
        
    }
};

void showMenu()
{
    system ("cls");
    cout<<"+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
    cout<<"+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
    cout<<"\n********Enter your choice for what you want to do :********\n"<<endl;
    cout<<"**<1> for inserting a new employee record ***\n";
    cout<<"**<2> for deleting an employee record     ***\n";
    cout<<"**<3> for searching an employee record    ***\n";
    cout<<"**<4> for modifying an employee record    ***\n";
    cout<<"**<5> for viewing all employees record    ***\n";
    cout<<"**<0> for exiting the program             ***\n";
    cout<<"\n\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
    cout<<"+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
    cout<<"\nChoice: ";
    int choice;
    choi:
    cin>>choice;
    Employee_record obj;
    switch(choice)
    {
        case 1:
        obj.insertEmployee();
        break;
        case 2:
        obj.deleteEmployee();
        break;
        case 3:
        obj.searchEmployee();
        break;
        case 4:
        obj.modifyEmployee();
        break;
        case 5:
        obj.display();
        break;
        case 0:
        exit(0);
        break;
        default :
        cout<<"Enter correct choice: ";
        goto choi;
    }
}

void Welcome()
{
    cout<<"+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
    cout<<"+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
    cout<<"**** Welcome to Employement Record Management System ****\n\n";
    cout<<"*** How this system works ***"<<endl;
    cout<<"*You will be given number for a particular task. which ever task you want to perform you can "<<endl;
    cout<<" enter that number and system which guide you to perform that task."<<endl;
    cout<<"*** Lets begin ***\n";
    cout<<"**<1> for Entering the System             ***\n";
    cout<<"**<0> for exiting the program             ***\n";
    cout<<"\nChoice: ";
    int choice;
    choi:
    cin>>choice;
    if(choice==1)
    showMenu();
    else if(choice==0)
    return ;
    else
    {
        cout<<"Enter correct choice: ";
        goto choi;
    }
}

//program starts from here (MAIN FUNCTION)
int main()
{
    Welcome();
    return 0;
}
