//
//  main.cpp
//  EmployeeApp
//
//  Created by Zhiyi Xu on 4/13/17.
//  Copyright © 2017 Zhiyi Xu. All rights reserved.
//

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
#include <cctype>
#include <iomanip>
using namespace std;

class employee
{
public:
    int type;           //1:developer; 2:project manager; 3:sales person
    string firstname;
    string lastname;
    string birthday;
    string numofemp;    //can be added by 2 and 3
    string salary;
    string building;    //for 1 only
    string floor;       //for 1 only
    string office;      //for 1 only
    string client;      //for 3 only
    
    employee()
    {
        type = 0;
        firstname = "";
        lastname = "";
        birthday = "";
        numofemp = "";
        salary = "";
        building = "";
        floor = "";
        office = "";
        client = "";
    }
};


vector<employee> libra;
int FNmax;
int LNmax;
int Salarymax;
int Buildmax;
int Officemax;
///////////////////
void setup();
void menu();

void remove();
void edit();
void editone(int index);
void update(int index, int attribute);
void add();
////////
bool testDigit(string list);
bool test(int attribute, int type, string statement);
int testinput(string list, int limit);
bool testDate(int year, int month, int date);
///////
void printsetup();
void printtable();
void printmenu();
void printemployee(int i);
///////
void readin();
void writeout();
void exportdata();

int main(int argc, const char * argv[]) {
 
    readin();
    setup();
    menu();
}

void menu()
{
    printtable();
    int choice = 1;
    while(choice != 0)
    {
        printmenu();
        cout << "=>";
        cin >> choice;
        while(choice < 0 || choice > 7)
        {
            cout << "Please enter in range 0~7:";
            cin >> choice;
        }
        if(choice == 0)
            break;
        
        switch (choice) {
            case 1:
                add();
                printtable();
                writeout();
                break;
            
            case 2:
                printtable();
                if(libra.size() == 0)
                {
                    cout << "There's no employee to be removed" << endl;
                }
                else
                {
                    edit();
                    writeout();
                    printtable();
                }
                break;
                
            case 3:
                printtable();
                if(libra.size() == 0)
                {
                    cout << "There's no employee to be removed" << endl;
                }
                else
                {
                    remove();
                    writeout();
                    printtable();
                }
                break;
                
            case 4:
                printtable();
                break;
                
            case 5:
                printsetup();
                setup();
                break;
                
            case 6:
                exportdata();
                break;
            
            case 7:
            {
                printsetup();
                cout << "Do you want to save the setting? (yes/no) =>";
                string tmp;
                cin >> tmp;
                while(tmp != "yes" && tmp != "no")
                {
                    cout << "Please enter \"yes\" or \"no\":";
                    cin >> tmp;
                }
                if(tmp == "no")
                {
                    FNmax = 15;
                    LNmax = 15;
                    Salarymax = 6;
                    Buildmax = 4;
                    Officemax = 4;
                    libra.clear();
                    writeout();
                }
                else
                {
                    libra.clear();
                    writeout();
                }
                break;
            }
            
            default:
                cout << "not possible" << endl;
                break;
        }
    }
}

void add()
{
    employee newemp;
    
    cout << "Please choose the type of employee that you are adding." << endl;
    cout << "1. Developer." << endl;
    cout << "2. Project Manager." << endl;
    cout << "3. Sales person" << endl;
    cout << "(Enter \"no\" to end adding.)" << endl;
    cout << "=>";
    string list;
    cin >> list;
    
    if(list == "no")
        return;
    while(list != "no")
    {
        newemp.type = testinput(list, 3);
        libra.push_back(newemp);
        int index = (int)libra.size() - 1;
        
        for(int i = 1; i <= 9; i++)
        {
            if(newemp.type == 1 && (i == 4 || i == 9))
            {
                continue;
            }
            else if(newemp.type == 2 && i == 9)
            {
                continue;
            }
            else if (newemp.type == 3 && (i == 6 || i == 7 || i == 8))
            {
                continue;
            }
            else
                update(index, i);
        }
        printtable();
        writeout();
        cout << "Add another employee?" << endl;
        cout << "1. Developer." << endl;
        cout << "2. Project Manager." << endl;
        cout << "3. Sales person" << endl;
        cout << "(Enter \"no\" to end adding.)" << endl;
        cout << "=>";
        cout << "(Enter \"no\" to stop)";
        cin >> list;
    }

}

void remove()
{
    cout << "Please enter the ID of the employee that you want to remove" << endl;
    cout << "(\"the number\" or \"no\" to stop)";
    string list;
    cin >> list;
    if(list == "no")
        return;
    while(list != "no")
    {
        int index = testinput(list, (int)libra.size());
        libra.erase(libra.begin() + index - 1);
        printtable();
        if(libra.size() == 0)
            return;
        printtable();
        writeout();
        cout << "Remove another employee?" << endl;
        cout << "(\"the number\" or \"no\" to stop)" << endl;
        cout << "The ID of the employee=>";
        cin >> list;
    }
}

void edit()
{
    cout << "Please enter the ID of the employee that you want to edit" << endl;
    cout << "(\"the number\" or \"no\" to stop)";
    string list;
    cin >> list;
    if(list == "no")
        return;
    while(list != "no")
    {
        int index = testinput(list, (int)libra.size());
        index--;
        editone(index);
        printtable();
        writeout();
        cout << "Edit another employee?" << endl;
        cout << "(\"the number\" or \"no\" to stop)";
        cin >> list;
    }

}

void editone(int index)
{
    printemployee(index);
    cout << "Please attribute that you want to edit" << endl;
    cout << "(\"the number\" or \"no\" to stop)";
    string list;
    cin >> list;
    if(list == "no")
        return;
    while(list != "no")
    {
        int attribute = testinput(list, 9);
        if(libra[index].type == 1 && attribute == 4)
            cout << endl << "=====Error=====" << endl << "Developers do not have number of employees" << endl;
        else if(libra[index].type == 1 && attribute == 9)
            cout << endl << "=====Error=====" << endl << "Developers do not have client" << endl;
        else if(libra[index].type == 2 && attribute == 9)
            cout << endl << "=====Error=====" << endl << "Project Managers do not have client" << endl;
        else if(libra[index].type == 3 && attribute == 6)
            cout << endl << "=====Error=====" << endl << "Sales Persons do not have Building number" << endl;
        else if(libra[index].type == 3 && attribute == 7)
            cout << endl << "=====Error=====" << endl << "Sales Persons do not have Floor number" << endl;
        else if(libra[index].type == 3 && attribute == 8)
            cout << endl << "=====Error=====" << endl << "Sales Persons do not have Office number" << endl;
        else
        {
            update(index, attribute);
        }
        printemployee(index);
        cout << "Edit another attribute?" << endl;
        cout << "(\"the number\" or \"no\" to stop)";
        cin >> list;
    }
}

void update(int index, int attribute)
{
    bool result;
    string statement;
    switch (attribute) {
        case 1:
            cout << "Please enter the new First Name:";
            cin >> statement;
            result = test(1, libra[index].type, statement);
            while(result == false)
            {
                cout << "The new statement is invalid." << endl;
                cout << "Re-enter:";
                cin >> statement;
                result = test(1, libra[index].type, statement);
            }
            libra[index].firstname = statement;
            break;
        
        case 2:
            cout << "Please enter the new Last Name:";
            cin >> statement;
            result = test(2, libra[index].type, statement);
            while(result == false)
            {
                cout << "The new statement is invalid." << endl;
                cout << "Re-enter:";
                cin >> statement;
                result = test(2, libra[index].type, statement);
            }
            libra[index].lastname = statement;
            break;
            
        case 3:
            cout << "Please enter the new Birth Date(95/06/26):";
            cin >> statement;
            result = test(3, libra[index].type, statement);
            while(result == false)
            {
                cout << "The new statement is invalid." << endl;
                cout << "Re-enter:";
                cin >> statement;
                result = test(3, libra[index].type, statement);
            }
            libra[index].birthday = statement;
            break;
            
        case 4:
            cout << "Please enter the new Number of Employee(0 for none):";
            cin >> statement;
            result = test(4, libra[index].type, statement);
            while(result == false)
            {
                cout << "The new statement is invalid." << endl;
                cout << "Re-enter:";
                cin >> statement;
                result = test(4, libra[index].type, statement);
            }
            libra[index].numofemp = statement;
            break;
            
        case 5:
            cout << "Please enter the new Salary:";
            cin >> statement;
            result = test(5, libra[index].type, statement);
            while(result == false)
            {
                cout << "The new statement is invalid." << endl;
                cout << "Re-enter:";
                cin >> statement;
                result = test(5, libra[index].type, statement);
            }
            libra[index].salary = statement;
            break;
            
        case 6:
            cout << "Please enter the new Building Number:";
            cin >> statement;
            result = test(6, libra[index].type, statement);
            while(result == false)
            {
                cout << "The new statement is invalid." << endl;
                cout << "Re-enter:";
                cin >> statement;
                result = test(6, libra[index].type, statement);
            }
            libra[index].building = statement;
            break;
            
        case 7:
            cout << "Please enter the new Floor Number:";
            cin >> statement;
            result = test(7, libra[index].type, statement);
            while(result == false)
            {
                cout << "The new statement is invalid." << endl;
                cout << "Re-enter:";
                cin >> statement;
                result = test(7, libra[index].type, statement);
            }
            libra[index].floor = statement;
            break;
            
        case 8:
            cout << "Please enter the new Office Number:";
            cin >> statement;
            result = test(8, libra[index].type, statement);
            while(result == false)
            {
                cout << "The new statement is invalid." << endl;
                cout << "Re-enter:";
                cin >> statement;
                result = test(8, libra[index].type, statement);
            }
            libra[index].office = statement;
            break;
            
        case 9:
            cout << "Please enter the new Client Name:";
            cin >> statement;
            result = test(9, libra[index].type, statement);
            while(result == false)
            {
                cout << "The new statement is invalid." << endl;
                cout << "Re-enter:";
                cin >> statement;
                result = test(9, libra[index].type, statement);
            }
            libra[index].client = statement;
            break;
            
        default:
            break;
    }
}

void setup()
{
    cout << "Do you want to change the setup? (yes/no):";
    string tmp;
    cin >> tmp;
    while(tmp != "yes" && tmp != "no")
    {
        cout << "Please enter \"yes\" or \"no\":";
        cin >> tmp;
    }
    if(tmp == "no")
        return;
    else
    {
        printsetup();
        int choice = 1;
        string list;
        int length = 0;
        while(choice != 0)
        {
            cout << endl << endl;
            cout << "Which of the max length do you want to change?" << endl;
            cout << "1. Done" << endl;
            cout << "2. First Name" << endl;
            cout << "3. Last Name" << endl;
            cout << "4. Salary" << endl;
            cout << "5. Building Number" << endl;
            cout << "6. Office Number" << endl;
            cout << "=>";
            cin >> list;
            choice = testinput(list, 6);
            if(choice == 1)
                break;
            cout << "Please enter the new max length:";
            cin >> list;
            length = testinput(list,30);
            switch (choice) {
                case 2:
                    FNmax = length;
                    break;
                case 3:
                    LNmax = length;
                    break;
                case 4:
                    Salarymax = length;
                    break;
                case 5:
                    Buildmax = length;
                    break;
                case 6:
                    Officemax = length;
                    break;
                default:
                    cout << "not possible" << endl;
                    break;
            }
            printsetup();
        }
        writeout();
    }
}

//====================test======================
bool testDigit(string list)
{
    bool digit = true;
    for(int i = 0; i < list.length(); i++)
    {
        if(!isdigit(list[i]))
        {
            digit = false;
            break;
        }
    }
    return digit;
}

int testinput(string list, int limit)
{
    int index;
    bool digit = false;
    while(digit == false)
    {
        digit = testDigit(list);
        if(digit == false)
        {
            cout << "Please enter an integer:";
            cin >> list;
        }
        else
            break;
    }
    index = stoi(list);
    while(index < 1 || index > limit)
    {
        cout << "Please enter in range 1~" << limit << ":";
        cin >> list;
        digit = false;
        while(digit == false)
        {
            digit = testDigit(list);
            if(digit == false)
            {
                cout << "Please enter an integer:";
                cin >> list;
            }
            else
                break;
        }
        index = stoi(list);
    }
    return index;
}

bool testDate(int year, int month, int date)
{
    bool result = true;
    
    if(year < 52)
    {
        result = false;
        cout << endl << "=====Error=====" << endl << "The employee's age must be in range 18~65." << endl;
    }
    if(month > 12 || month < 1)
    {
        result = false;
        cout << endl << "=====Error=====" << endl << "The month must be in range 1~12." << endl;
    }
    if(date < 0)
    {
        result = false;
        cout << endl << "=====Error=====" << endl << "The date is wrong." << endl;
    }
    else
    {
        if(month == 2 && date > 29)
        {
            result = false;
            cout << endl << "=====Error=====" << endl << "The date is wrong." << endl;
        }
        if((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && date > 31)
        {
            result = false;
            cout << endl << "=====Error=====" << endl << "The date is wrong." << endl;
        }
        if((month == 2 || month == 4 || month == 6 || month == 9 || month == 11) && date > 31)
        {
            result = false;
            cout << endl << "=====Error=====" << endl << "The date is wrong." << endl;
        }
    }
    return result;
}

bool test(int attribute, int type, string statement)
{
    bool result = true;
    switch (attribute) {
        case 1:
            if(statement.length() == 0)
            {
                result = false;
                cout << endl << "=====Error=====" << endl << "The First Name is required." << endl;
            }
            if(statement.length() > FNmax)
            {
                result = false;
                cout << endl << "=====Error=====" << endl << "The First Name should be least than " << FNmax << "characters." << endl;
            }
            break;
            
        case 2:
            if(statement.length() == 0)
            {
                result = false;
                cout << endl << "=====Error=====" << endl << "The Last Name is required." << endl;
            }
            if(statement.length() > LNmax)
            {
                result = false;
                cout << endl << "=====Error=====" << endl << "The Last Name should be least than " << LNmax << "characters." << endl;
            }
            break;
            
        case 3:
            if(statement.length() != 8)
            {
                result = false;
                cout << endl << "=====Error=====" << endl << "Please enter in form \"95/06/26\"." << endl;
                break;
            }
            else
            {
                if(statement[2] != '/' || statement[5] != '/')
                {
                    result = false;
                    cout << endl << "=====Error=====" << endl << "Please enter in form \"95/06/27\"." << endl;
                }
                else
                {
                    string year, month, date;
                    istringstream iss(statement);
                    getline(iss, year, '/');
                    getline(iss, month, '/');
                    getline(iss, date);
                    if((!testDigit(year))||(!testDigit(month))||(!testDigit(date)))
                    {
                        result = false;
                        cout << endl << "=====Error=====" << endl << "Please enter numbers for year, month and date" << endl;
                        break;
                    }
                    int y,m,d;
                    y = stoi(year);
                    m = stoi(month);
                    d = stoi(date);
                    if(!testDate(y,m,d))
                        result = false;
                }
            }
            break;
            
        case 4:
            if(!testDigit(statement))
            {
                result = false;
                cout << endl << "=====Error=====" << endl << "Please enter a number." << endl;
            }
            break;
            
        case 5:
            if(!testDigit(statement))
            {
                result = false;
                cout << endl << "=====Error=====" << endl << "Please enter a number." << endl;
                break;
            }
            if(statement.length() > Salarymax)
            {
                result = false;
                cout << endl << "=====Error=====" << endl << "The Salary should be least than " << Salarymax << "characters." << endl;
            }
            if(statement.length() == 0)
            {
                result = false;
                cout << endl << "=====Error=====" << endl << "The Salary is required." << endl;
            }
            break;
            
        case 6:
            if(!testDigit(statement))
            {
                result = false;
                cout << endl << "=====Error=====" << endl << "Please enter a number." << endl;
                break;
            }
            if(statement.length() > Buildmax)
            {
                result = false;
                cout << endl << "=====Error=====" << endl << "The Building Number should be least than " << Buildmax << "characters." << endl;
            }
            if(statement.length() == 0)
            {
                result = false;
                cout << endl << "=====Error=====" << endl << "The Building Number is required." << endl;
            }
            break;
            
        case 7:
            if(!testDigit(statement))
            {
                result = false;
                cout << endl << "=====Error=====" << endl << "Please enter a number." << endl;
                break;
            }
            if(statement.length() > 2)
            {
                result = false;
                cout << endl << "=====Error=====" << endl << "The Floor Number should be least than 2 characters." << endl;
            }
            if(statement.length() == 0)
            {
                result = false;
                cout << endl << "=====Error=====" << endl << "The Floor Number is required." << endl;
            }
            break;
            
        case 8:
            if(!testDigit(statement))
            {
                result = false;
                cout << endl << "=====Error=====" << endl << "Please enter a number." << endl;
                break;
            }
            if(statement.length() > Officemax)
            {
                result = false;
                cout << endl << "=====Error=====" << endl << "The Office Number should be least than " << Officemax << "characters." << endl;
            }
            if(statement.length() == 0)
            {
                result = false;
                cout << endl << "=====Error=====" << endl << "The Office Number is required." << endl;
            }
            break;
            
        case 9:
            if(statement.length() == 0)
            {
                result = false;
                cout << endl << "=====Error=====" << endl << "The Client Name is required." << endl;
            }
            break;
            
        default:
            cout << "not possible" << endl;
            break;
    }
    return result;
}


//==================Print=======================
void printmenu()
{
    cout << endl << endl << endl;
    cout << "Menu:" << endl;
    cout << "0. Exit the App." << endl;
    cout << "======================================" << endl;
    cout << "1. Add a new employee" << endl;
    cout << "2. Edit the information of an employee" << endl;
    cout << "3. Remove an employee" << endl;
    cout << "======================================" << endl;
    cout << "4. Print the table" << endl;
    cout << "5. Print and Edit the setting" << endl;
    cout << "6. Export to a TXT file" << endl;
    cout << "7. Delete and Create a new table" << endl;
    cout << endl;
}

void printsetup()
{
    cout << endl << endl;
    cout << "Setting of Table" << endl;
    cout << "======================================" << endl;
    cout << "1. Max length of First Name:" << FNmax << endl;
    cout << "2. Max length of Last Name:" << LNmax << endl;
    cout << "3. Max length of Salary:" << Salarymax << endl;
    cout << "4. Max length of Building Number:" << Buildmax << endl;
    cout << "5. Max length of Office Number:" << Officemax << endl;
    cout << "======================================" << endl;
    cout << endl;
}



void printtable()
{
    if(libra.size() == 0)
        cout << endl << endl << "The employee table is empty." << endl;
    else
    {
        //get the longest name;
        int FNlen = 10;
        int LNlen = 9;
        int CLlen = 11;
        int Sallen = 6; //len of "Salary"
        int Bullen = 8; //len of "Building"
        int Offlen = 13; //len of "Office Number"
        for(int i = 0; i < libra.size(); i++)
        {
            if(libra[i].firstname.length() > FNlen)
                FNlen = (int)libra[i].firstname.length();
            if(libra[i].lastname.length() > LNlen)
                LNlen = (int)libra[i].lastname.length();
            if(libra[i].client.length() > CLlen)
                CLlen = (int)libra[i].client.length();
        }
        if(Salarymax > Sallen)
            Sallen = Salarymax;
        if(Buildmax > Bullen)
            Bullen = Buildmax;
        if(Officemax > Offlen)
            Offlen = Officemax;
        
        //set up
        int total = 44 + FNlen + LNlen + Sallen + Bullen + Offlen + CLlen + 4;
        cout << endl << endl << endl;
        for(int i = 0; i < total; i++)
            cout << "-";
        cout << endl;
        cout << "|" << left << setw(3) << "ID";
        cout << "|" << left << setw(FNlen) << "First Name";
        cout << "|" << left << setw(LNlen) << "Last Name";
        cout << "|" << left << setw(10) << "Birth date";
        cout << "|" << left << setw(19) << "Number of Employees";
        cout << "|" << left << setw(Sallen) << "Salary";
        cout << "|" << left << setw(Bullen) << "Building";
        cout << "|" << left << setw(5) << "Floor";
        cout << "|" << left << setw(Offlen) << "Office Number";
        cout << "|" << left << setw(CLlen) << "Client Name";
        cout << "|" << endl;
        for(int i = 0; i < total; i++)
            cout << "-";
        cout << endl;
        
        //print data
        for(int i = 0; i < libra.size(); i++)
        {
            cout << "|" << left << setw(3) << i+1;
            cout << "|" << left << setw(FNlen) << libra[i].firstname;
            cout << "|" << left << setw(LNlen) << libra[i].lastname;
            cout << "|" << left << setw(10) << libra[i].birthday;
            cout << "|" << left << setw(19) << libra[i].numofemp;
            cout << "|" << left << setw(Sallen) << libra[i].salary;
            cout << "|" << left << setw(Bullen) << libra[i].building;
            cout << "|" << left << setw(5) << libra[i].floor;
            cout << "|" << left << setw(Offlen) << libra[i].office;
            cout << "|" << left << setw(CLlen) << libra[i].client;
            cout << "|" << endl;
        }
        for(int i = 0; i < total; i++)
            cout << "-";
        cout << endl;
    }
}

void printemployee(int i)
{
    int FNlen = 10;
    int LNlen = 9;
    int CLlen = 11;
    int Sallen = 6; //len of "Salary"
    int Bullen = 8; //len of "Building"
    int Offlen = 13; //len of "Office Number"
    if(libra[i].firstname.length() > FNlen)
        FNlen = (int)libra[i].firstname.length();
    if(libra[i].lastname.length() > LNlen)
        LNlen = (int)libra[i].lastname.length();
    if(libra[i].client.length() > CLlen)
        CLlen = (int)libra[i].client.length();
    
    if(Salarymax > Sallen)
        Sallen = Salarymax;
    if(Buildmax > Bullen)
        Bullen = Buildmax;
    if(Officemax > Offlen)
        Offlen = Officemax;
    //set up
    int total = 44 + FNlen + LNlen + Sallen + Bullen + Offlen + CLlen + 4;
    cout << endl << endl;
    for(int i = 0; i < total; i++)
        cout << "-";
    cout << endl;
    cout << "|" << left << setw(3) << "";
    cout << "|" << left << setw(FNlen) << 1;
    cout << "|" << left << setw(LNlen) << 2;
    cout << "|" << left << setw(10) << 3;
    cout << "|" << left << setw(19) << 4;
    cout << "|" << left << setw(Sallen) << 5;
    cout << "|" << left << setw(Bullen) << 6;
    cout << "|" << left << setw(5) << 7;
    cout << "|" << left << setw(Offlen) << 8;
    cout << "|" << left << setw(CLlen) << 9;
    cout << "|" << endl;
    for(int j = 0; j < total; j++)
        cout << "-";
    cout << endl;
    cout << "|" << left << setw(3) << "ID";
    cout << "|" << left << setw(FNlen) << "First Name";
    cout << "|" << left << setw(LNlen) << "Last Name";
    cout << "|" << left << setw(10) << "Birth date";
    cout << "|" << left << setw(19) << "Number of Employees";
    cout << "|" << left << setw(Sallen) << "Salary";
    cout << "|" << left << setw(Bullen) << "Building";
    cout << "|" << left << setw(5) << "Floor";
    cout << "|" << left << setw(Offlen) << "Office Number";
    cout << "|" << left << setw(CLlen) << "Client Name";
    cout << "|" << endl;
    for(int j = 0; j < total; j++)
        cout << "-";
    cout << endl;
    //print data
    cout << "|" << left << setw(3) << i+1;
    cout << "|" << left << setw(FNlen) << libra[i].firstname;
    cout << "|" << left << setw(LNlen) << libra[i].lastname;
    cout << "|" << left << setw(10) << libra[i].birthday;
    cout << "|" << left << setw(19) << libra[i].numofemp;
    cout << "|" << left << setw(Sallen) << libra[i].salary;
    cout << "|" << left << setw(Bullen) << libra[i].building;
    cout << "|" << left << setw(5) << libra[i].floor;
    cout << "|" << left << setw(Offlen) << libra[i].office;
    cout << "|" << left << setw(CLlen) << libra[i].client;
    cout << "|" << endl;
    for(int j = 0; j < total; j++)
        cout << "-";
    cout << endl;
}

//file reading and writing
void readin()
{
    //ifstream inputFile("/Users/zhiyixu/Desktop/Libra/EmployeeApp/EmployeeApp/data.txt");
    ifstream inputFile("backdata.txt");
    string line;
    //ifstream inputFile("data.txt");
    if (inputFile.is_open())
    {
        //inputFile.is_open();
        //readin info for talbe
        getline(inputFile, line);
        FNmax = stoi(line);
        getline(inputFile, line);
        LNmax = stoi(line);
        getline(inputFile, line);
        Salarymax = stoi(line);
        getline(inputFile, line);
        Buildmax = stoi(line);
        getline(inputFile, line);
        Officemax = stoi(line);
        
        //readin employees' data
        getline(inputFile, line);
        getline(inputFile, line);
        int count = stoi(line);
        getline(inputFile, line);
        for(int i = 0; i < count; i++)
        {
            employee tmp;
            getline(inputFile, line);
            tmp.type = stoi(line);
            getline(inputFile, line);
            istringstream iss(line);
            getline(iss, tmp.firstname, ' ');
            getline(iss, tmp.lastname, ' ');
            getline(iss, tmp.birthday, ' ');
            if(tmp.type == 2 || tmp.type == 3)
            {
                getline(iss, tmp.numofemp, ' ');
                if(tmp.numofemp == "none")
                    tmp.numofemp = "";
            }
            getline(iss, tmp.salary, ' ');
            if(tmp.type == 1 || tmp.type == 2)
            {
                getline(iss, tmp.building, ' ');
                getline(iss, tmp.floor, ' ');
                getline(iss, tmp.office, ' ');
            }
            if(tmp.type == 3)
            {
                getline(iss, tmp.client);
            }
            libra.push_back(tmp);
        }
    }
    else
    {
        FNmax = 15;
        LNmax = 15;
        Salarymax = 6;
        Buildmax = 4;
        Officemax = 4;
        printsetup();
    }
    inputFile.close();
}

void writeout()
{
    //ofstream outputFile("/Users/zhiyixu/Desktop/Libra/EmployeeApp/EmployeeApp/data.txt");
    ofstream outputFile("backdata.txt");
    outputFile << FNmax << "\n";
    outputFile << LNmax << "\n";
    outputFile << Salarymax << "\n";
    outputFile << Buildmax << "\n";
    outputFile << Officemax << "\n";
    outputFile << "\n";
    outputFile << libra.size() << "\n";
    outputFile << "\n";
    for(int i = 0; i < libra.size(); i++)
    {
        outputFile << libra[i].type << "\n";
        outputFile << libra[i].firstname << " ";
        outputFile << libra[i].lastname << " ";
        outputFile << libra[i].birthday << " ";
        if(libra[i].type == 2 || libra[i].type == 3)
        {
            if(libra[i].numofemp.length() == 0)
                outputFile << "none" << " ";
            else
                outputFile << libra[i].numofemp << " ";
        }
        outputFile << libra[i].salary << " ";
        if(libra[i].type == 1 || libra[i].type == 2)
        {
            outputFile << libra[i].building << " ";
            outputFile << libra[i].floor << " ";
            outputFile << libra[i].office << " ";
        }
        if(libra[i].type == 3)
        {
            outputFile << libra[i].client;
        }
        outputFile << "\n";
    }
    outputFile.close();
}

void exportdata()
{
    string name;
    cout << "Please enter the name of the exported file (without extension):";
    cin >> name;
    //name = "/Users/zhiyixu/Desktop/" + name + ".txt";
    name = name + ".txt";
    
    ofstream outputFile(name);
    
    if(libra.size() == 0)
        outputFile << "The employee table is empty." << endl;
    else
    {
        //get the longest name;
        int FNlen = 10;
        int LNlen = 9;
        int CLlen = 11;
        int Sallen = 6; //len of "Salary"
        int Bullen = 8; //len of "Building"
        int Offlen = 13; //len of "Office Number"
        for(int i = 0; i < libra.size(); i++)
        {
            if(libra[i].firstname.length() > FNlen)
                FNlen = (int)libra[i].firstname.length();
            if(libra[i].lastname.length() > LNlen)
                LNlen = (int)libra[i].lastname.length();
            if(libra[i].client.length() > CLlen)
                CLlen = (int)libra[i].client.length();
        }
        if(Salarymax > Sallen)
            Sallen = Salarymax;
        if(Buildmax > Bullen)
            Bullen = Buildmax;
        if(Officemax > Offlen)
            Offlen = Officemax;
        //set up
        int total = 44 + FNlen + LNlen + Sallen + Bullen + Offlen + CLlen + 4;
        outputFile << endl;
        for(int i = 0; i < (total-22)/2; i++)
            outputFile << " ";
        outputFile << "The Employees of Libra" << endl;
        outputFile << endl;
        for(int i = 0; i < total; i++)
            outputFile << "-";
        outputFile << endl;
        outputFile << "|" << left << setw(3) << "ID";
        outputFile << "|" << left << setw(FNlen) << "First Name";
        outputFile << "|" << left << setw(LNlen) << "Last Name";
        outputFile << "|" << left << setw(10) << "Birth date";
        outputFile << "|" << left << setw(19) << "Number of Employees";
        outputFile << "|" << left << setw(Sallen) << "Salary";
        outputFile << "|" << left << setw(Bullen) << "Building";
        outputFile << "|" << left << setw(5) << "Floor";
        outputFile << "|" << left << setw(Offlen) << "Office Number";
        outputFile << "|" << left << setw(CLlen) << "Client Name";
        outputFile << "|" << endl;
        for(int i = 0; i < total; i++)
            outputFile << "-";
        outputFile << endl;
        
        //print data
        for(int i = 0; i < libra.size(); i++)
        {
            outputFile << "|" << left << setw(3) << i+1;
            outputFile << "|" << left << setw(FNlen) << libra[i].firstname;
            outputFile << "|" << left << setw(LNlen) << libra[i].lastname;
            outputFile << "|" << left << setw(10) << libra[i].birthday;
            outputFile << "|" << left << setw(19) << libra[i].numofemp;
            outputFile << "|" << left << setw(Sallen) << libra[i].salary;
            outputFile << "|" << left << setw(Bullen) << libra[i].building;
            outputFile << "|" << left << setw(5) << libra[i].floor;
            outputFile << "|" << left << setw(Offlen) << libra[i].office;
            outputFile << "|" << left << setw(CLlen) << libra[i].client;
            outputFile << "|" << endl;
        }
        for(int i = 0; i < total; i++)
            outputFile << "-";
        outputFile << endl;
    }
}
