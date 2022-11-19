#include <bits/stdc++.h>

using namespace std;

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