#include <bits/stdc++.h>
#include <cstdlib>
#include "AVL_data_structure.h"

using namespace std;

//function used
void showMenu();
void Welcome();


void showMenu()
{
    system("CLS");
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

    switch(choice)
    {
        case 1:
        obj.Insert();
        showMenu();
        break;
        case 2:
        obj.Delete();
        showMenu();
        break;
        case 3:
        obj.searchEmployee();
        showMenu();
        break;
        case 4:
        obj.modifyEmployee();
        showMenu();
        break;
        case 5:
        cout<<"ID   |        Name        |     Phone     |  Block/sector/district |     City     |      State      |    Country   |  Designation  |   Salary   |"<<endl;
        obj.Inorder();
        showMenu();
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

 
int main() 
{
    Welcome();

    return 0;
}