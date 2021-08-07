#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <time.h>
#include <stdlib.h>
#include <sstream>
#include <windows.h>
#include <conio.h>
using namespace std;
class student
{
    string username, password;

public:
    void studentView();
    int checkStudentCredentials(string username, string password);
    int Attendance(string username);
    int sendLeaveApplication(string username);
};
enum IN
{

    // 13 is ASCII for carriage
    // return
    IN_BACK = 8,
    IN_RET = 13

};

// Function that accepts the password
std::string takePasswdFromUser(
    char sp = '*')
{
    // Stores the password
    string passwd = "";
    char ch_ipt;

    // Until condition is true
    while (true)
    {

        ch_ipt = getch();

        // if the ch_ipt
        if (ch_ipt == IN::IN_RET)
        {
            cout << endl;
            return passwd;
        }
        else if (ch_ipt == IN::IN_BACK && passwd.length() != 0)
        {
            passwd.pop_back();

            // Cout statement is very
            // important as it will erase
            // previously printed character
            cout << "\b \b";

            continue;
        }

        // Without using this, program
        // will crash as \b can't be
        // print in beginning of line
        else if (ch_ipt == IN::IN_BACK && passwd.length() == 0)
        {
            continue;
        }

        passwd.push_back(ch_ipt);
        cout << sp;
    }
}
// void studentView();
// int studentLogin();
// int checkStudentCredentials(string userName, string password);
int adminLogin();
int teacherlogin();
int Attendance(string username);
// int sendLeaveApplication(string username);
int total = 100;
int adminView();
int deleteAllStudents();
int checkListOfStudentsRegistered();
int registerStudent();
int m = 0;
int k = 0;

int adminLogin()
{
    system("clear");
    cout << "\n -------------------- Admin Login --------------------";

    string username;
    string password;

    cout << "\n Enter username : ";
    cin >> username;
    cout << "\n Enter password : ";
    password=takePasswdFromUser();

    if (username == "admin" && password == "admin")
    {
        adminView();
        getchar();
    }
    else
    {
        cout << "\n Error ! Invalid Credintials..";
        cout << "\n Press any key for main menu ";
        getchar();
        getchar();
    }

    return 0;
}

int adminView()
{
    int goBack = 0;
    while (1)
    {
        system("clear");
        cout << "\n 1 Register a Student";
        cout << "\n 2 Delete All students name registered";
        cout << "\n 3 Check List of Student registered by username";
        cout << "\n 0. Go Back <- \n";
        int choice;

        cout << "\n Enter you choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            registerStudent();
            break;
        case 2:
            deleteAllStudents();
            break;
        case 3:
            checkListOfStudentsRegistered();
            break;
        case 0:
            goBack = 1;
            break;
        default:
            cout << "\n Invalid choice. Enter again ";
            getchar();
        }

        if (goBack == 1)
        {
            break;
        }
    }

    return 0;
}

int deleteAllStudents()
{
    remove("db.dat");
    cout << "\n Please any key to continue..";

    getchar();
    getchar();
    return 0;
}

int checkListOfStudentsRegistered()
{
    cout << "\n ---------- Check List of Student Registered by Username----------- ";

    //check if record already exist..
    ifstream read;
    read.open("db.dat");

    if (read)
    {
        int recordFound = 0;
        string line;
        while (getline(read, line))
        {

            char name[100];
            strcpy(name, line.c_str());
            string filename = name;
            cout << "\n"
                 << filename;

            int total_lines = 0;
            ifstream read1;
            read1.open(filename.c_str(), ios::app);
            string line;
            while (getline(read1, line))
            {
                ++total_lines;
            }
            read1.close();
            ifstream read;
            read.open(filename.c_str(), ios::app);
            string l;
            if (read)
            {
                int line_no = 0;
                while (line_no != total_lines && getline(read, l))
                {
                    ++line_no;
                }
                if (line_no == total_lines)
                {
                    cout << "-> " << l << "\n";
                }
                read.close();
                // char name[100];
                // strcpy(name, line.c_str());
                // char onlyname[100];
                // strncpy(onlyname, name, (strlen(name) - 4));
                // cout<<" \n " << onlyname;
            }
            read.close();
        }
    }
    else
    {
        cout << "\n No Record found :(";
    }

    cout << "\n Please any key to continue..";
    getchar();
    getchar();
    return 0;
}

int registerStudent()
{
    cin.get();
    cout << "\n ----- Form to Register Student ---- \n";

    string name, username, password, confirmpassword, rollno, branch, address, father, mother;
    int total;
    cin.get();
    cout << "\n Enter Name : ";
    // cin >> name;
    getline(cin, name);

    cout << "\n Enter Username : ";
    getline(cin, username);
    // cin >> username;
    while (1)
    {
        cout << "\n Enter password : ";
        password = takePasswdFromUser();
        // cin >> password;
        cout << "\n Confirm password : ";
        confirmpassword = takePasswdFromUser();
        if (password == confirmpassword)
        {
            break;
        }
        cout<<"Password didnot match"<<endl;
    }
    cout << "\n Enter rollno : ";
    getline(cin, rollno);
    // cin >> rollno;
    getchar();

    cout << "\n Enter branch : ";
    getline(cin, branch);
    // cin >> branch;
    cout << "\n Enter Address: ";
    getline(cin, address);
    cout << "\n Enter Father's name: ";
    // cin>>father;
    getline(cin, father);
    cout << "\n Enter Mother's name: ";
    // cin>>mother;
    getline(cin, mother);
    cout << "\n Enter initial number of presents :";
    cin >> m;

    //check if record already exist..
    ifstream read;
    read.open("db.dat");

    if (read)
    {
        int recordFound = 0;
        string line;
        while (getline(read, line))
        {
            if (line == username + ".dat")
            {
                recordFound = 1;
                break;
            }
        }
        if (recordFound == 1)
        {
            cout << "\n Username already Register. Please choose another username ";
            getchar();
            getchar();
            read.close();
            return 0;
        }
    }
    read.close();

    ofstream out;
    out.open("db.dat", ios::app);
    out << username + ".dat"
        << "\n";
    out.close();

    ofstream out1;
    string temp = username + ".dat";
    out1.open(temp.c_str());
    out1 << name << "\n";
    out1 << username << "\n";
    out1 << password << "\n";
    out1 << rollno << "\n";
    out1 << branch << "\n";
    out1 << address << "\n";
    out1 << father << "\n";
    out1 << mother << "\n";
    out1 << m << "\n";

    out1.close();

    cout << "\n Student Registered Successfully !!";

    cout << "\n Please any key to continue..";
    getchar();
    getchar();
    return 0;
}

int Attendance();
int teacherView();
int teacherlogin();

int teacherlogin()
{
    system("clear");
    cout << "\n -------------------- Teacher Login ----------------------";

    string username;
    string password;

    cout << "\n Enter username : ";
    cin >> username;
    cout << "\n Enter password : ";
    password=takePasswdFromUser();

    if (username == "teacher" && password == "teacher")
    {
        teacherView();
        getchar();
    }
    else
    {
        cout << "\n Error ! Invalid Credintials..";
        cout << "\n Press any key for main menu ";
        getchar();
        getchar();
    }

    return 0;
}

int Attendance()
{
    ifstream read;
    read.open("db.dat");

    if (read)
    {
        int recordFound = 0;
        string line;
        while (getline(read, line))
        {

            char name[100];
            strcpy(name, line.c_str());
            string filename = name;

            int total_lines = 0;
            ifstream read1;
            read1.open(filename);
            string line;
            while (getline(read1, line))
            {
                ++total_lines;
            }
            read1.close();

            ifstream read;
            read.open(filename);
            // ifstream read;
            // read.open("db.dat");
            cout << "name:" << filename << endl;
            int c;
            cout << "1: present:"
                 << "\t"
                 << "O : absent:" << endl;
            cout << "enter choice:" << endl;
            cin >> c;
            switch (c)
            {
            case 1:
            {
                string line;
                if (read)
                {
                    //cout<<"inside switch"<<endl;
                    int line_no = 0;
                    while (line_no != total_lines && getline(read, line))
                    {
                        ++line_no;
                    }
                    if (line_no == total_lines)
                    {
                        int i;
                        istringstream(line) >> i;
                        i++;
                        // cout<<"i "<<i<<endl;
                        ofstream out1;
                        string temp = name;
                        out1.open(temp.c_str(), ios::app);
                        out1 << i << "\n";
                        out1.close();
                    }
                }
                break;
            }
            case 0:
                break;
            }

            read.close();
        }
    }
    read.close();

    cout << "\n Please any key to continue..";

    getchar();
    getchar();

    return 0;
}

int teacherView()
{
    int goBack = 0;
    while (1)
    {
        system("clear");
        cout << "\n 1 Mark Attendance";
        cout << "\n 0. Go Back <- \n";
        int choice;

        cout << "\n Enter you choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            Attendance();
            break;
        case 0:
            goBack = 1;
            break;
        default:
            cout << "\n Invalid choice. Enter again ";
            getchar();
        }

        if (goBack == 1)
        {
            break;
        }
    }

    return 0;
}
//student part
void student::studentView()
{
    cout << "\n Enter username : ";
    cin >> username;

    cout << "\n Enter password : ";
    cin >> password;

    int res = checkStudentCredentials(username, password);

    if (res == 0)
    {
        cout << "\n Invalid Credentials !!";
        cout << "\n Press any key for Main Menu..";
        getchar();
        getchar();
        return;
    }

    int goBack = 0;
    while (1)
    {

        system("clear");
        cout << "\n 1 Count my Attendance";
        cout << "\n 2 Send a leave application";
        cout << "\n 0. Go Back <- \n";
        int choice;

        cout << "\n Enter you choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            Attendance(username);
            break;
        case 2:
            sendLeaveApplication(username);
            break;
        case 0:
            goBack = 1;
            break;
        default:
            cout << "\n Invalid choice. Enter again ";
            getchar();
        }

        if (goBack == 1)
        {
            break;
        }
    }
}

int studentLogin()
{
    student s; // creating object of class studnet
    system("clear");
    cout << "\n -------------------- Student Login ----------------------";
    s.studentView();
    return 0;
}

int student::checkStudentCredentials(string username, string password)
{

    ifstream read;
    read.open("db.dat");
    int recordFound = 0;
    if (read)
    {
        string line;
        string temp = username + ".dat";
        while (getline(read, line))
        {
            if (line == temp)
            {
                recordFound = 1;
            }
        }
    }
    read.close();
    cout << "recordFound " << recordFound << " username " << username << " password " << password << endl;
    if (recordFound == 1)
    {
        ifstream read;
        string filename = username + ".dat";
        read.open(filename);
        int line_number = 0;
        string line;
        while (line_number != 3 && getline(read, line))
        {
            cout << "Line " << line << endl;
            ++line_number;
        }
        read.close();
        if (password == line)
            return 1;
        else
            return 0;
    }
    else
        return 0;
}

int student::Attendance(string username) // Function OVERLOADING
{
    int total_lines = 0;
    string filename = username + ".dat";
    ifstream read;
    read.open(filename);
    string line;
    while (getline(read, line))
    {
        ++total_lines;
    }

    read.close();
    ifstream read1;
    read1.open(filename);
    if (read1)
    {
        int line_no = 0;
        while (line_no != total_lines && getline(read1, line))
        {
            ++line_no;
        }
        if (line_no == total_lines)
        {
            cout << "\nTotal present: " << line;
            int i;
            istringstream(line) >> i;
            cout << "\nPercentage of attendance :\t" << (i * 100 / total) << "%";
        }
    }

    cout << "\n Please any key to continue..";

    getchar();
    getchar();

    return 0;
}

int student::sendLeaveApplication(string username)
{
    char add[100];
    cout << "\n Write your application here: ";
    getchar();
    cin.getline(add, 100);

    time_t now = time(0);
    tm *ltm = localtime(&now);

    ofstream out;
    out.open("application.dat", ios::app);
    out << add << " -> " << ltm->tm_mday << "/" << 1 + ltm->tm_mon << "/" << 1900 + ltm->tm_year << " -> " << username << "\n";
    out.close();
    cout << "\n Application successfully sent !!";
    cout << "\n Please any key to continue..";
    getchar();
    return 0;
}

int main(int argc, char **argv)
{

    while (1)
    {
        system("clear");

        cout << "\t\t\t\t\t Attendance Management System \n";
        cout << "-------------------------------------------------------------------------\n\n";

        cout << "1. Student Login\n";
        cout << "2. Admin Login\n";
        cout << "3. teacher Login\n";
        cout << "0. Exit\n";
        int choice;

        cout << "\n Enter you choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            studentLogin();
            break;
        case 2:
            adminLogin();
            break;
        case 3:
            teacherlogin();
            break;
        case 0:
            while (1)
            {
                system("clear");
                cout << "\n Are you sure, you want to exit? y | n \n";
                char ex;
                cin >> ex;
                if (ex == 'y' || ex == 'Y')
                    exit(0);
                else if (ex == 'n' || ex == 'N')
                {
                    break;
                }
                else
                {

                    cout << "\n Invalid choice !!!";
                    getchar();
                }
            }
            break;

        default:
            cout << "\n Invalid choice. Enter again ";
            getchar();
        }
    }

    return 0;
}
