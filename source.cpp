#include <iostream>
#include <stdlib.h> //to use system("CLS")
#include <bits/stdc++.h>
using namespace std;

void showMenu();
class node
{
    public:

    int id;
    string name;
    long long phone;
    string *address;
    string designation;
    long long salary;

    static int i;
    node* lchild;
    node* rchild;
    int height;

    node()
    {
        id=i++;
        address=new string[4];
        lchild=NULL;
        rchild=NULL;
    }
    node(string n,long p,string a[],string de,string d,int s)
    {
        id=i++;
        name=n;
        phone=p;
        address=new string[4];
        address=a;
        designation=de;
        salary=s;
        lchild=NULL;
        rchild=NULL;
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

    int NodeHeight(node *p) // returns height of the node
    {
        int hl,hr;
        hl=(p && p->lchild)?p->lchild->height:0;
        hr=(p && p->rchild)?p->rchild->height:0;
        return hl>hr?hl+1:hr+1;
    }

    int BalanceFactor(node *p) //returns balance factor of the node
    {
        int hl,hr;
        hl=(p && p->lchild)?p->lchild->height:0;
        hr=(p && p->rchild)?p->rchild->height:0;
        return hl-hr;
    }

    node* LLRotation(node* p) //solves LL imbalance
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

    node* RRRotation(node* p) //solves RR imbalance
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

    node*LRRotation(node *p) //solves LR imbalance
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

    node* RLRotation(node *p) //solves RL imbalance
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

    node* rinsert(node* p,node *q) //recursive function to insert a node in tree
    {
        int key=q->id;
        node *t;
        if(root=NULL)
        {
            root=q;
        }
        if(key<p->id)
        {
            p->lchild=rinsert(p->lchild,q);
        }
        else if(key>p->id)
        {
            p->rchild=rinsert(p->rchild,q);
        }
        p->height=NodeHeight(p);
        if(BalanceFactor(p)==2 && BalanceFactor(p->lchild)==1)
            return LLRotation(p);
        else if(BalanceFactor(p)==2 && BalanceFactor(p->lchild)==-1)
            return LRRotation(p);
        else if(BalanceFactor(p)==2 && BalanceFactor(p->rchild)==1)
            return RRRotation(p);
        else if(BalanceFactor(p)==2 && BalanceFactor(p->rchild)==-1)
            return RLRotation(p);
        return p;
    }

    node* inPre(node* p) //returns inorder predecessor
    {
        while (p && p->rchild!=NULL)
        {
            p = p->rchild;
        }
        return p;
    }

    node* inSucc(node* p) //returns inorder successor
    {
        while (p && p->lchild!=NULL)
        {
            p = p->lchild;
        }
        return p;
    }

    node* deletion(node* p,int key) //recursive function to delete node
    {
        if(p==NULL)return NULL;
        if(p->lchild==NULL && p->rchild==NULL)
        {
            if(p==root)root=NULL;
            delete p;
        }
        if(key<p->id)p->lchild=deletion(p->lchild,key);
        else if(key>p->id)p->rchild=deletion(p->rchild,key);
        else
        {
            node* q;
            if(NodeHeight(p->lchild)>NodeHeight(p->rchild))
            {
                q=inPre(p->lchild);
                q->id=p->id;
                p->lchild=deletion(p->lchild,q->id);
            }
            else
            {
                q=inSucc(p->rchild);
                p->id=q->id;
                p->rchild=deletion(p->rchild,q->id);
            }
        }
        p->height=(NodeHeight(p));
        if(BalanceFactor(p)==2 && BalanceFactor(p->lchild)==1)
            return LLRotation(p);
        else if(BalanceFactor(p)==2 && BalanceFactor(p->lchild)==-1)
            return LRRotation(p);
        else if(BalanceFactor(p)==2 && BalanceFactor(p->rchild)==1)
            return RRRotation(p);
        else if(BalanceFactor(p)==2 && BalanceFactor(p->rchild)==-1)
            return RLRotation(p);
        return p;
    }

    node* searchnode(int key) //function to search for a node
    {
        node* p=root;
        while(p)
        {
            if(key==p->id)return p;
            else if(key<p->id)p=p->lchild;
            else p=p->rchild;
        }
        return NULL;
    }

    void insertEmployee()//function to insert employee record
    {
        node* p=new node;
        cout<<"Enter the details of the employee\n";
        cout<<"ID will be automatically insert.\n";
        cout<<"Enter name of the employee:\n";
        getline(cin>>ws,p->name);
        cout<<"Enter phone name of the employee:\n";
        cin>>p->phone;
        cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
        cout<<"Enter address line 1 of the employee:\n";
        string s;
        getline(cin,s);
        p->address[0]=s;
        cout<<"Enter city:\n";
        getline(cin>>ws,s);
        p->address[1]=s;
        cout<<"Enter state:\n";
        getline(cin>>ws,s);
        p->address[2]=s;
        cout<<"Enter country:\n";
        getline(cin>>ws,s);
        p->address[3]=s;
        cout<<"Enter designation:\n";
        getline(cin>>ws,p->designation);
        cout<<"Enter salary of the employee:\n";
        cin>>p->salary;
        rinsert(root,p);
        cout<<"Record Inserted***\n";
        showMenu();
    }

    void deleteEmployee()
    {
        cout<<"Enter the id of the employee you want to delete: ";
        int id;
        cin>>id;
        deletion(root,id);
    }
    void searchEmployee()
    {
        cout<<"Enter the id of the employee you want to search: ";
        int id;
        cin>>id;
        node *p=searchnode(id);
        display(p);
    }
    void modifyEmployee()
    {
        cout<<"Enter the id of the employee you want to modify:";
        int key;
        cin>>key;
        node* p=searchnode(key);
        cout<<"**<1> for changing name\n";
        cout<<"**<2> for changing phone number\n";
        cout<<"**<3> for changing address\n";
        cout<<"**<4> for changing designation\n";
        cout<<"**<5> for changing salary\n";
        int choice;
        cin>>choice;
        switch(choice)
        {
        case 1:
            {
                cout<<"Enter the new name\n";
                string name;
                getline(cin,name);
                p->name=name;
                break;
            }
        case 2:
            {
                cout<<"Enter new phone number\n";
                long n;
                cin>>n;
                p->phone=n;
                break;
            }
        case 3:
        {
            cout<<"Enter which thing in address you want change:\n";
            cout<<"<1> for block/street\n";
            cout<<"<2> for city\n";
            cout<<"<3> for state\n";
            cout<<"<4> for country\n";
            int c;
            cin>>c;
            switch(c)
            {
            case 1:
                {
                    cout<<"Enter new block/street\n";
                    string s;
                    getline(cin,s);
                    p->address[0]=s;
                    break;
                }
            case 2:
                {
                    cout<<"Enter new city\n";
                    string s;
                    getline(cin,s);
                    p->address[1]=s;
                    break;
                }
            case 3:
                {
                    cout<<"Enter new state\n";
                    string s;
                    getline(cin,s);
                    p->address[2]=s;
                    break;
                }
            case 4:
                {
                    cout<<"Enter new country\n";
                    string s;
                    getline(cin,s);
                    p->address[3]=s;
                    break;
                }
            }
            break;
        }
        case 4:
            {
                cout<<"Enter new designation\n";
                string s;
                getline(cin,s);
                p->designation=s;
                break;
            }
        case 5:
            {
                cout<<"Enter new salary\n";
                long n;
                cin>>n;
                p->salary=n;
                break;
            }
        }
    }
    void display(node* p)
    {
        cout<<p->name<<" "<<p->phone<<" "<<p->address[0]<<" ";
    }
    void displayRecords(node* p)//display all record using inorder traversal
    {

        if(p)
        {
            displayRecords(p->lchild);
            display(p);
            displayRecords(p->rchild);
        }
    }
};

void showMenu()
{
    cout<<"\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
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
        cout<<"ID   |        Name        |     Phone     |  Block/sector/district |     City     |      State      |    Country   |  Designation  |   Salary   |"<<endl;
        obj.displayRecords(obj.root);
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
