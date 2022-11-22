#include <bits/stdc++.h>

using namespace std;

struct name                                             //the node that will store all data
{
    char nam[256];
    name* add[256];
    int islast;                                         //it will be 1 if node contains the last letter of the name 
};

int actual_search(string,name*,string,int*);            //function declaration
void actual_show_database(string,name*);                //function declaration

void toZero(name* d)                                    //to set all values of the node to zero
{
    for(int y=0;y<256;y++)
    {
        d->nam[y]='0';
        d->add[y]=NULL;
    }
    d->islast=0;
}
name* root1 = new name; 
                                 //root1 of the entire data structure
void insert_(string a)                                  //to insert a value using recursion 
{
    
    char v;
    name* ki=root1;
    for(int i=0;i<a.length();i++)
    {
        v=a[i];
        int k=v;
        if((ki->nam[k])=='0')
        {
        /*
        this if condition checks whether the letter is already present or not in the node if it is present
        then it sends the pointer to next if not then changes the value and create a new node 
        */
            ki->nam[k]='1';
            name* temp=new name;
            toZero(temp);
            if(i==a.length()-2)
            {
                temp->islast=1;
            }
            ki->add[k]=temp;
            ki=temp;
        }
        else
        {
            //to change pointer 
            ki=ki->add[k];
        }
    }
}

void search(string sea)
{
/*
we made search and actual_search two functions for ease of user.
User does not need to pass an empty string , root, and an int
pointer to search a name
*/
    cout<<"Employees with name "<<sea<<" are "<<endl;
    cout<<endl;
    int a=0;
    int f=actual_search("",root1,sea,&a);
    /*
    we create a int pointing pointer with
    initial value 0 ,then we pass the adress to the function actual_search
    and it returns the value of j we now use the change in j to tell how
    many people with name sea were in the data
    */
    if(f==0)
    {
        //if there are no such names in the data
        cout<<"Employees with name "<<sea<<" are -"<<" 0"<<endl;
    }
}

int actual_search(string str,name* nod,string sea,int* h)
{
/*
it is very similar to insert function , we check each letter 
of the word using recursion
*/
    for(int i=0;i<256;i++)
    {
        if(nod->nam[i]=='1')
        {
            if(nod==root1)
            {
                str="";
            }
            string s=str+(char(i));
            int check=0;
            if(str.substr(0,sea.length())==sea)
            {
               check=1;
            }
            if(nod->islast==1&&str.length()>=sea.length()&&check==1)
            {
               cout<<s<<endl;//to print names
               *h=*h+1;
               //if we found a name then we increase the adress' value by 1
            }
            actual_search(s,nod->add[i],sea,h);
        }
    }
    return *h;//we return the address of search's j variable
}

void show_database()
{
    //to show all names in the data
    cout<<endl;
    cout<<"__________________"<<endl;
    cout<<"ALL THE EMPLOYEES WHO ARE OR WAS WORKING HERE ARE "<<endl;
    cout<<endl;
    actual_show_database("",root1);
}

void actual_show_database(string str,name* nod)
{
    for(int i=0;i<256;i++)
    {
        if(nod->nam[i]=='1')
        {
            if(nod==root1)
            {
                str="";
            }
            string s=str+(char(i));
            if(nod->islast==1)
            {
                cout<<s<<endl;
            }
            actual_show_database(s,nod->add[i]);
        }
    }
}

void employee_history()
{
    choi:
    cout<<"\nPress 1 to search for an employee and 2 to see all employees:\n";
    int n;
    cin>>n;
    if(n==1)
    {
        cout<<"\nEnter the name of the employee:\n";
        string s;
        cin>>s;
        search(s);
    }
    else if(n==2)
    {
        show_database();
    }
    else
    {
        cout<<"\nEnter valid option:\n";
        goto choi;
    }
}