#include <bits/stdc++.h>
using namespace std;

//function used
void showMenu();
void Welcome();

//class that stores details of the record
class record
{
public:

    static int i; //to auto allocate the id
    
    //details of the employees
    int id;
    string name;
    string phone;
    string *address;
    string designation;
    long long salary;

    record() //constructor which takes input from user
    {
        address=new string[4];
        cout<<"Enter the details of the employee\n";
        cout<<"ID will be automatically insert.\n";
        i++;
        id=i;
        cout<<"Enter name of the employee:\n";
        getline(cin>>ws,name);
        cout<<"Enter phone number of the employee:\n";
        getline(cin>>ws,phone);
        cout<<"Enter address line 1 of the employee:\n";
        getline(cin>>ws,address[0]);
        cout<<"Enter city:\n";
        getline(cin>>ws,address[1]);
        cout<<"Enter state:\n";
        getline(cin>>ws,address[2]);
        cout<<"Enter country:\n";
        getline(cin>>ws,address[3]);
        cout<<"Enter designation:\n";
        getline(cin>>ws,designation);
        cout<<"Enter salary of the employee:\n";
        cin>>salary;
    }

    void print_records()
    {
        cout<<"Name of the emoloyee: "<<name<<endl;
        cout<<"Phone Number of the emoloyee: "<<phone<<endl;
        cout<<"Address of the emoloyee: "<<endl;
        for(int i=0;i<4;i++)
        {
            cout<<address[i]<<",";
        }
        cout<<endl;
        cout<<"Designation of the employee :"<<designation<<endl;
        cout<<"Salary of the employee :"<<salary<<endl;
    }
};
int record::i=0;

/*------------AVL and its node data structure starts from here----------------------*/

class Node 
{
    public:

    //Things required for AVL
    Node* lchild;
    int data;
    Node* rchild;
    int height;

    //Pointer to the record
    record * employee_details;
};

class AVL
{
    public:

    Node* root;
    
    AVL()
    { 
        root = NULL; 
    }
 
    //***** Helper methods for inserting/deleting *****
    int NodeHeight(Node* p); 
    int BalanceFactor(Node* p); //returns balance factor of the node
    Node* LLRotation(Node* p); //solves LL imbalance 
    Node* RRRotation(Node* p); //solves RR imbalance
    Node* LRRotation(Node* p); //solves LR imbalance
    Node* RLRotation(Node* p); //solves RL imbalance
    Node* InPre(Node* p); //returns inorder predecessor of the node
    Node* InSucc(Node* p); //return inorder successor of the node
 
    //***** Recursive insert function *****
    void Insert();
    Node* rInsert(Node* p, int key,record * details);
    
    //****** Traversal ******
    void Inorder(); //helper function to call recursive inorder function
    void Inorder(Node* p);

    //***** Delete function *****
    void Delete();
    Node* Delete(Node* p, int key);

    //***** Searching for the node *****
    Node* searchNode(int key); //function to search for a node
    
};

int AVL::NodeHeight(Node* p)
{ 
    int hl;
    int hr;
    hl = (p && p->lchild) ? p->lchild->height : 0;
    hr = (p && p->rchild) ? p->rchild->height : 0;
    return hl>hr?hl+1:hr+1;
}
 
int AVL::BalanceFactor(Node *p)
{
    int hl;
    int hr;
    hl = (p && p->lchild) ? p->lchild->height : 0;
    hr = (p && p->rchild) ? p->rchild->height : 0;
    return hl - hr;
}
 
Node* AVL::LLRotation(Node *p) 
{
    Node* pl = p->lchild;
    Node* plr = pl->rchild;
    pl->rchild = p;
    p->lchild = plr;
 
    // Update height
    p->height = NodeHeight(p);
    pl->height = NodeHeight(pl);
 
    // Update root
    if (root == p)
    {
        root = pl;
    }
    return pl;
}
 
Node* AVL::RRRotation(Node *p) 
{
    Node* pr = p->rchild;
    Node* prl = pr->lchild;
    pr->lchild = p;
    p->rchild = prl;
 
    // Update height
    p->height = NodeHeight(p);
    pr->height = NodeHeight(pr);
 
    // Update root
    if (root == p)
    {
        root = pr;
    }
    return pr;
}
 
Node* AVL::LRRotation(Node *p) 
{
    Node* pl = p->lchild;
    Node* plr = pl->rchild;
    pl->rchild = plr->lchild;
    p->lchild = plr->rchild;
 
    plr->lchild = pl;
    plr->rchild = p;
 
    // Update height
    pl->height = NodeHeight(pl);
    p->height = NodeHeight(p);
    plr->height = NodeHeight(plr);
 
    // Update root
    if (p == root)
    {
        root = plr;
    }
    return plr;
}
 
Node* AVL::RLRotation(Node *p) 
{
    Node* pr = p->rchild;
    Node* prl = pr->lchild;
    pr->lchild = prl->rchild;
    p->rchild = prl->lchild;
    prl->rchild = pr;
    prl->lchild = p;
 
    // Update height
    pr->height = NodeHeight(pr);
    p->height = NodeHeight(p);
    prl->height = NodeHeight(prl);
 
    // Update root
    if (root == p)
    {
        root = prl;
    }
    return prl;
}
  
Node* AVL::InPre(Node* p)
{
    while (p && p->rchild != NULL){
        p = p->rchild;
    }
    return p;
}

Node* AVL::InSucc(Node *p) 
{
    while (p && p->lchild != NULL){
        p = p->lchild;
    }
    return p;
}

void AVL::Insert()
{
    record* details=new record;
    cout<<"Entered record deatils are:\n\n";
    details->print_records();
    cout<<"\n *ARE THE DETAILS CORRECT*\n";
    cout<<"Press Y for YES and N for NO\n";
    char choice;
    choi:
    cin>>choice;
    if(choice=='Y' || choice=='y')
    {
        root=rInsert(root, details->id,details);
        cout<<"\n***Insertion succesfull***\n";
    }
    else if(choice=='N' || choice=='n')
    {
        cout<<"\nEnter the details again:\n";
        delete(details);
        Insert(); 
    }
    else
    {
        cout<<"Enter correct choice :\n";
        goto choi;
    }
    showMenu();
}
Node* AVL::rInsert(Node* p, int key,record * details)
{
    Node* t;

    if (p == NULL)
    {
        t = new Node;
        t->data = key;
        t->lchild = NULL;
        t->rchild = NULL;
        t->height = 1; 
        t->employee_details=details;// Starting height from 1 onwards instead of 0
        return t;
    }
 
    if (key < p->data){
        p->lchild = rInsert(p->lchild, key,details);
    } else if (key > p->data){
        p->rchild = rInsert(p->rchild, key,details);
    }
 
    // Update height
    p->height = NodeHeight(p);
 
    // Balance Factor and Rotation
    if (BalanceFactor(p) == 2 && BalanceFactor(p->lchild) == 1) {
        return LLRotation(p);
    } else if (BalanceFactor(p) == 2 && BalanceFactor(p->lchild) == -1){
        return LRRotation(p);
    } else if (BalanceFactor(p) == -2 && BalanceFactor(p->rchild) == -1){
        return RRRotation(p);
    } else if (BalanceFactor(p) == -2 && BalanceFactor(p->rchild) == 1){
        return RLRotation(p);
    }
 
    return p;
}

void AVL::Inorder()
{
     Inorder(root); 
}
void AVL::Inorder(Node* p)
{
    if (p)
    {
        Inorder(p->lchild);
        cout << p->data << ", " << flush;
        Inorder(p->rchild);
    }
}

void AVL::Delete()
{
    choi:
    cout<<"Enter the id of the employee whose record you want to delete\n";
    int key;
    cin>>key;
    if(searchNode(key))
    {
        Delete(root,key);
        cout<<"deletion succesfull\n";
        showMenu();
    }
    else
    {
        cout<<"***Id not present in database***\n";
        choic:
        cout<<"Press 1 to re-renter id press 0 to go to main menu:\n";
        int choice;
        cin>>choice;
        if(choice==1)
        {
            goto choi;
        }
        else if(choice==0)
        {
            showMenu();
        }
        else
        {
            cout<<"press valid number:";
            goto choic;
        }
    }
}
Node* AVL::Delete(Node* p, int key)
{
    if (p == NULL){
        return NULL;
    }
 
    if (p->lchild == NULL && p->rchild == NULL){
        if (p == root){
            root = NULL;
        }
        delete p;
        return NULL;
    }
 
    if (key < p->data){
        p->lchild = Delete(p->lchild, key);
    } else if (key > p->data){
        p->rchild = Delete(p->rchild, key);
    } else {
        Node* q;
        if (NodeHeight(p->lchild) > NodeHeight(p->rchild)){
            q = InPre(p->lchild);
            p->data = q->data;
            p->lchild = Delete(p->lchild, q->data);
        } else {
            q = InSucc(p->rchild);
            p->data = q->data;
            p->rchild = Delete(p->rchild, q->data);
        }
    }
 
    // Update height
    p->height = NodeHeight(p);
 
    // Balance Factor and Rotation
    if (BalanceFactor(p) == 2 && BalanceFactor(p->lchild) == 1) {  // L1 Rotation
        return LLRotation(p);
    } else if (BalanceFactor(p) == 2 && BalanceFactor(p->lchild) == -1){  // L-1 Rotation
        return LRRotation(p);
    } else if (BalanceFactor(p) == -2 && BalanceFactor(p->rchild) == -1){  // R-1 Rotation
        return RRRotation(p);
    } else if (BalanceFactor(p) == -2 && BalanceFactor(p->rchild) == 1){  // R1 Rotation
        return RLRotation(p);
    } else if (BalanceFactor(p) == 2 && BalanceFactor(p->lchild) == 0){  // L0 Rotation
        return LLRotation(p);
    } else if (BalanceFactor(p) == -2 && BalanceFactor(p->rchild) == 0){  // R0 Rotation
        return RRRotation(p);
    }
 
    return p;
}

Node* AVL::searchNode(int key) 
{
    Node* p=root;
    while(p)
    {
        if(key==p->data)return p;
        else if(key<p->data)p=p->lchild;
        else p=p->rchild;
    }
    return NULL;
}


/*-------------------------finish of avl data structure----------------------------------------------*/










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
    AVL obj;
    switch(choice)
    {
        case 1:
        obj.Insert();
        break;
        case 2:
        obj.Delete();
        break;
        // case 3:
        // obj.searchEmployee();
        // break;
        // case 4:
        // obj.modifyEmployee();
        // break;
        // case 5:
        // cout<<"ID   |        Name        |     Phone     |  Block/sector/district |     City     |      State      |    Country   |  Designation  |   Salary   |"<<endl;
        // obj.displayRecords(obj.root);
        // break;
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

 
int main() 
{
    Welcome();

    return 0;
}
