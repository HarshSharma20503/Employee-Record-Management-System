#include <bits/stdc++.h>

using namespace std;

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

    record()
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
    }
};
int record::i=0;



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
 
    // Helper methods for inserting/deleting
    int NodeHeight(Node* p); 
    int BalanceFactor(Node* p); //returns balance factor of the node
    Node* LLRotation(Node* p); //solves LL imbalance 
    Node* RRRotation(Node* p); //solves RR imbalance
    Node* LRRotation(Node* p); //solves LR imbalance
    Node* RLRotation(Node* p); //solves RL imbalance
    Node* InPre(Node* p); //returns inorder predecessor of the node
    Node* InSucc(Node* p); //return inorder successor of the node
 
    // Recursive insert function
    void Insert();
    Node* rInsert(Node* p, int key,record * details);
    
    // Traversal
    void Inorder(); //helper function to call recursive inorder function
    void Inorder(Node* p);

    // Delete function
    void Delete(int key);
    Node* Delete(Node* p, int key);

    //Searching for the node
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
    root=rInsert(root, details->id,details); 
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

void AVL::Delete(int key)
{
    Delete(root,key);
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


 
int main() {
 
    // AVL tree;
    // int A[] = {10, 20, 30, 25, 28, 27, 5};
    // for (int i=0; i<sizeof(A)/sizeof(A[0]); i++){
    //     tree.root = tree.rInsert(tree.root, A[i]);
    // }
    // tree.Inorder();
    // cout << endl;
    // tree.Delete(tree.root, 28);
    // tree.Inorder();
    // cout << endl;
    // record obj;
    // obj.print_records();


    AVL tree;

    tree.Insert();
    tree.Insert();
    //tree.Delete(1);
    // Node *t=tree.searchNode(1);
    // if(t->data==1)cout<<"Hipyee";
    tree.Inorder();



    return 0;
}