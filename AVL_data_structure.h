#include<bits/stdc++.h>
#include <cstdlib>
#include "record_data_structure.h"
using namespace std;

//class node for the every node in avl data structure
class Node 
{
    public:

    //Things required for AVL
    Node* lchild;     //left child
    int data;         //key for the avl which is same as the id of the employee
    Node* rchild;     //right child
    int height;       //stores height of that node

    //Pointer to the record
    record * employee_details;
};

//class avl to create required data structure
class AVL
{
    public:

    Node* root;       //stores root node of the avl tree
    
    AVL()             //constructor to initialise root as null 
    { 
        root = NULL; 
    }
 
    //***** Helper methods for inserting/deleting *****
    int NodeHeight(Node* p);   
    int BalanceFactor(Node* p);      //returns balance factor of the node
    Node* LLRotation(Node* p);       //solves LL imbalance 
    Node* RRRotation(Node* p);       //solves RR imbalance
    Node* LRRotation(Node* p);       //solves LR imbalance
    Node* RLRotation(Node* p);       //solves RL imbalance
    Node* InPre(Node* p);            //returns inorder predecessor of the node
    Node* InSucc(Node* p);           //return inorder successor of the node
 
    //***** Recursive insert function *****
    void Insert();                   //helper function to call recursive insert function
    Node* rInsert(Node* p, int key,record * details);
    
    //****** Traversal ******
    void Inorder();                  //helper function to call recursive inorder function
    void Inorder(Node* p);

    //***** Delete function *****
    void Delete();                   //helper function to call recursive delete function
    Node* Delete(Node* p, int key);

    //***** Searching for the node *****
    Node* searchNode(int key);       //function to search for a node

    //***** Searching for employee *****
    void searchEmployee();           //function to search of a specific employee

    //***** Modifying Employee details *****
    void modifyEmployee();           //function to modify details of specific employee

}obj;

int AVL::NodeHeight(Node* p)
{ 
    int hl;                                                //to store height of left subtree
    int hr;                                                //to store height of right subtree
    hl = (p && p->lchild) ? p->lchild->height : 0;         //calculate height of left subtree
    hr = (p && p->rchild) ? p->rchild->height : 0;         //calculate height of right subtree
    return hl>hr?hl+1:hr+1;                                //return height of current node
}
 
int AVL::BalanceFactor(Node *p)
{
    int hl;                                                //to store height of left subtree
    int hr;                                                //to store height of right subtree
    hl = (p && p->lchild) ? p->lchild->height : 0;         //calculate height of left subtree
    hr = (p && p->rchild) ? p->rchild->height : 0;         //return height of current node
    return hl - hr;                                        //return balance factor of current node
}
 
Node* AVL::LLRotation(Node *p) 
{
    Node* pl = p->lchild;                       //pl to store leftchild of p
    Node* plr = pl->rchild;                     //plr to store rightchild of pl

    //changing links
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
    Node* pr = p->rchild;                        //pr to store rightchild of p
    Node* prl = pr->lchild;                      //prl to store leftchild of pr

    //changing links
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
    Node* pl = p->lchild;                         //pl to store leftchild of p 
    Node* plr = pl->rchild;                       //plr to store rightchild of pl

    //changing links
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
    Node* pr = p->rchild;                           //pr to store rightchild of p
    Node* prl = pr->lchild;                         //prl to store leftchild of pr

    //changing links
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
    while (p && p->rchild != NULL){         //travels to rightmost node of the given subtree root node
        p = p->rchild;
    }
    return p;
}

Node* AVL::InSucc(Node *p) 
{
    while (p && p->lchild != NULL){         //travels to leftmost node of the given subtree root node
        p = p->lchild;
    }
    return p;
}

void AVL::Insert()
{
    record* details=new record;             //create object of record class and calls its constructor to take input for details
    cout<<"Entered record deatils are:\n\n";
    cout<<"ID   |        Name        |     Phone     |  Block/sector/district |     City     |      State      |    Country   |  Designation  |   Salary   |"<<endl;
    details->print_records();
    cout<<"\n *ARE THE DETAILS CORRECT*\n";
    cout<<"Press Y for YES and N for NO\n";
    char choice;
    choi:
    cin>>choice;
    if(choice=='Y' || choice=='y')
    {
        root=rInsert(root, details->id,details);      //calls the function to insert the node with the key
        string em_his=details->name+" "+details->phone;
        insert_(em_his);
        cout<<"\n***Insertion succesfull***\n";
    }
    else if(choice=='N' || choice=='n')
    {
        cout<<"\nEnter the details again:\n";
        delete(details);
        choic:
        cout<<"Press 1 to re-enter details press 0 to go to main menu:\n";
        int choice;
        cin>>choice;
        if(choice==1)
        {
            delete(details);
            Insert();
        }
        else
        {
            if(choice!=0)
            {
                cout<<"press valid number:";
                goto choic;
            }
        }
    }
    else
    {
        cout<<"Enter correct choice :\n";
        goto choi;
    }
}

Node* AVL::rInsert(Node* p, int key,record * details)
{
    Node* t;

    if (p == NULL)                          //if node is null means we reached the leaf node than insert the node there
    {
        t = new Node;
        t->data = key;
        t->lchild = NULL;
        t->rchild = NULL;
        t->height = 1; 
        t->employee_details=details;         // Starting height from 1 onwards instead of 0
        return t;
    }
 
    if (key < p->data)
    {
        p->lchild = rInsert(p->lchild, key,details);   //if key smaller than move to left subtree
    } 
    else if (key > p->data)
    {
        p->rchild = rInsert(p->rchild, key,details);   //if key is larger than move to right subtree
    }
 
    // Update height
    p->height = NodeHeight(p);
 
    // Balance Factor and Rotation
    if (BalanceFactor(p) == 2 && BalanceFactor(p->lchild) == 1) 
    {
        return LLRotation(p);
    } 
    else if (BalanceFactor(p) == 2 && BalanceFactor(p->lchild) == -1)
    {
        return LRRotation(p);
    } 
    else if (BalanceFactor(p) == -2 && BalanceFactor(p->rchild) == -1)
    {
        return RRRotation(p);
    } 
    else if (BalanceFactor(p) == -2 && BalanceFactor(p->rchild) == 1)
    {
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
        p->employee_details->print_records();     // prints all the details by calling print_records function
        Inorder(p->rchild);
    }
}

void AVL::Delete()
{
    choi:
    cout<<"Enter the id of the employee whose record you want to delete\n";
    int key;
    cin>>key;
    if(searchNode(key)!=NULL)
    {
        Node* temp=searchNode(key);
        cout<<"\nID   |        Name        |     Phone     |  Block/sector/district |     City     |      State      |    Country   |  Designation  |   Salary   |"<<endl;
        temp->employee_details->print_records();
        cout<<endl;
        choi1:
        cout<<"******Are you sure you want to delete this record******\n\n";
        cout<<"press y for yes and n for no\n";
        char ch;
        cin>>ch;
        if(ch=='y' || ch=='Y')
        {
            Delete(root,key);                         //calls function to delete the node with the key
            cout<<"deletion succesfull\n";
        }
        else if(ch=='n' || ch=='N')
        {}
        else
        {
            cout<<"\n****Press valid option key****\n";
            goto choi1;
        }
        
    }
    else
    {
        cout<<"***Id not present in database***\n";
        choic:
        cout<<"Press 1 to re-renter id press 0 to go to main menu:\n";
        char choice;
        cin>>choice;
        if(choice=='1')
        {
            goto choi;
        }
        else if(choice=='0')
        {}
        else
        {
            cout<<"press valid number:";
            goto choic;
        }
    }
}
Node* AVL::Delete(Node* p, int key)
{
    if (p == NULL)
    {
        return NULL;
    }
 
    if (p->lchild == NULL && p->rchild == NULL){
        if (p == root){
            root = NULL;
        }
        delete p;
        return NULL;
    }
 
    if (key < p->data)
    {
        p->lchild = Delete(p->lchild, key);
    } 
    else if (key > p->data)
    {
        p->rchild = Delete(p->rchild, key);
    } 
    else                                                            //if key matches with the key to current node key than
    {                                                               //swap the node value with inorder successor or inorder predecessor
        Node* q;                                                    //compare the height of the left and right subtree to check 
        if (NodeHeight(p->lchild) > NodeHeight(p->rchild))          //which node to put at the place of the deleted node
        {
            q = InPre(p->lchild);
            p->data = q->data;
            p->employee_details=q->employee_details;
            p->lchild = Delete(p->lchild, q->data);
        } 
        else 
        {
            q = InSucc(p->rchild);
            p->data = q->data;
            p->employee_details=q->employee_details;
            p->rchild = Delete(p->rchild, q->data);
        }
    }
 
    // Update height
    p->height = NodeHeight(p);
 
    // Balance Factor and Rotation
    if (BalanceFactor(p) == 2 && BalanceFactor(p->lchild) == 1) 
    {  
        return LLRotation(p);
    } 
    else if (BalanceFactor(p) == 2 && BalanceFactor(p->lchild) == -1)
    {  
        return LRRotation(p);
    } 
    else if (BalanceFactor(p) == -2 && BalanceFactor(p->rchild) == -1)
    { 
        return RRRotation(p);
    } 
    else if (BalanceFactor(p) == -2 && BalanceFactor(p->rchild) == 1)
    {  
        return RLRotation(p);
    } 
    else if (BalanceFactor(p) == 2 && BalanceFactor(p->lchild) == 0)
    {  
        return LLRotation(p);
    } 
    else if (BalanceFactor(p) == -2 && BalanceFactor(p->rchild) == 0)
    {  
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

void AVL::searchEmployee()
{
    choi:
    cout<<"Enter the id of the employee whose record you want to search\n";
    int key;
    cin>>key;
    Node* temp=searchNode(key);
    if(temp!=NULL)
    {
        cout<<"***** Record found *****\n\n";
        cout<<"ID   |        Name        |     Phone     |  Block/sector/district |     City     |      State      |    Country   |  Designation  |   Salary   |"<<endl;
        temp->employee_details->print_records();
    }
    else
    {
        cout<<"***Id not present in database***\n";
        choic:
        cout<<"Press 1 to re-renter id press 0 to go to main menu:\n";
        char choice;
        cin>>choice;
        if(choice=='1')
        {
            goto choi;
        }
        else if(choice=='0'){}
        else
        {
            cout<<"press valid number:";
            goto choic;
        }
    }
}

void AVL::modifyEmployee()
{
    choi:
    cout<<"Enter the id of the employee whose record you want to modify\n";
    int key;
    cin>>key;
    Node* temp=searchNode(key);
    if(temp!=NULL)
    {
        cout<<"***** Record found *****\n\n";
        cout<<"ID   |        Name        |     Phone     |  Block/sector/district |     City     |      State      |    Country   |  Designation  |   Salary   |"<<endl;
        temp->employee_details->print_records();
        cout<<"\nWhich detail you would like to change:\n";
        cout<<"**<1> NAME                    ***\n";
        cout<<"**<2> PHONE                   ***\n";
        cout<<"**<3> Block/sector/district   ***\n";
        cout<<"**<4> City                    ***\n";
        cout<<"**<5> State                   ***\n";
        cout<<"**<6> Country                 ***\n";
        cout<<"**<7> Designation             ***\n";
        cout<<"**<8> Salary                  ***\n";
        cout<<"**<0> To go to main menu      ***\n";

        char choice;
        choicee:
        cin>>choice;

        //switch case for menu based input
        switch(choice)
        {
            case '1':
            cout<<"Enter new name:\n";
            getline(cin>>ws,temp->employee_details->name);
            cout<<"\n**** Name updated ****\n";
            break;
            case '2':
            cout<<"Enter new phone number:\n";
            getline(cin>>ws,temp->employee_details->phone);
            cout<<"\n**** Phone number updated ****\n";
            break;
            case '3':
            cout<<"Enter new Block/sector/district:\n";
            getline(cin>>ws,temp->employee_details->address[0]);
            cout<<"\n**** Block/sector/district updated ****\n";
            break;
            case '4':
            cout<<"Enter new city:\n";
            getline(cin>>ws,temp->employee_details->address[1]);
            cout<<"\n**** city updated ****\n";
            break;
            case '5':
            cout<<"Enter new state:\n";
            getline(cin>>ws,temp->employee_details->address[2]);
            cout<<"\n**** state updated ****\n";
            break;
            case '6':
            cout<<"Enter new country:\n";
            getline(cin>>ws,temp->employee_details->address[3]);
            cout<<"\n**** country updated ****\n";
            break;
            case '7':
            cout<<"Enter new designation:\n";
            getline(cin>>ws,temp->employee_details->designation);
            cout<<"\n**** designation updated ****\n";
            break;
            case '8':
            cout<<"Enter new salary:\n";
            cin>>temp->employee_details->salary;
            cout<<"\n**** salary updated ****\n";
            break;
            case '0':
            return;
            break;
            default :
            cout<<"Enter correct choice: ";
            goto choicee;
        }
        cout<<"\n***New details are:***\n\n";
        cout<<"ID   |        Name        |     Phone     |  Block/sector/district |     City     |      State      |    Country   |  Designation  |   Salary   |"<<endl;
        temp->employee_details->print_records();
        zchoi:
        cout<<"Do you want to make any further changes:\n";
        cout<<"press y to for yes and n to go to main\n";
        char ch;cin>>ch;
        if(ch=='y' || ch=='Y')
        {
            goto choi;
        }
        else if(ch=='n' || ch=='N'){}
        else 
        {
            cout<<"Enter valid choice\n";
            goto zchoi;
        }
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
        else if(choice==0){}
        else
        {
            cout<<"\n****Press valid number****\n\n";
            goto choic;
        }
    }
}