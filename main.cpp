#include <iostream>
#include<fstream>
#include <conio.h>
using namespace std;

class lecture
{
protected:
    string password;
    int found = 0;
public:
    void verifypassword()
    {
        int i=2;
        int k=0;
        string pword;
        system("cls");
        cout<<"Welcome"<<endl;
        Again:
        cout<<"enter password: "<<endl;
        cin>>pword;
        ifstream lecdata;
        lecdata.open("lecture.txt");
        if(!lecdata.is_open())
        {
            cout<<"Unable to open file"<<endl;
        }
        else
        {
        lecdata>>password;
        while(lecdata.good())
        {
           if(password == pword)
           {
               found = 1;
               goto here;
           }
           lecdata>>password;
        }
        here:
        if(found)
        {
            cout<<"Valid password"<<endl;
        }
        else
        {
            while(i>0)
            {
                i--;
                cout<<"Invalid password"<<endl;
                goto Again;
            }
        }

        if(i==0 & found ==0)
        {
          cout<<"Invalid password"<<endl<<"Maximum attempts reached"<<endl;
          exit(1);
        }
        }
        lecdata.close();
    }

};

class SEM : public lecture
{
private:
    string name;
    string usn;
    string elective;
    string date;
    string present;
public:
    SEM()
    {
        usn = " ";
    }
    int adminview()
    {
        int option;
        cout<<" 1. Register a student"<<endl<<" 2. Display student list"<<endl<<" 3. Edit student info"<<endl<<" 4.Delete a student"<<endl<<" 5. Take attendance"<<endl<<" 6. Display attendance by date"<<endl<<" 7. Exit"<<endl;
        cin>>option;
        return option;
    }

    void reg_student(string &param)
    {
        cout<<"Enter student name :\n ";
        cin>>name;

        cout<<"Enter student USN : \n";
        cin>>usn;

        ofstream stu;
        stu.open("student.txt", ios::app );
        if(!stu.is_open())
        {
            cout<<"Error while opening file"<<endl;
        }
        else
        {
            stu << param;
            stu << endl;
            stu << name;
            stu << endl;
            stu << usn;
            stu << endl;
            stu << endl;
        }
        stu.close();
    }
    void displaystulist(string &param)
    {
        ifstream stu;
        stu.open("student.txt");
        if(!stu.is_open())
        {
            cout<<"Error while opening file"<<endl;
        }
        else
        {
            stu >> elective;
            stu >> name;
            stu >> usn;
            while(!stu.eof())
            {
                if(elective == param )
                {
                    //cout<<" elective :"<<elective<<endl;
                    cout<<" Student name : "<<name<<endl;
                    cout<<" Student USN  : "<<usn<<endl<<endl;
                }
                    stu >> elective;
                    stu >> name;
                    stu >> usn;
            }
        }
        stu.close();
    }

    void deletestudent()
    {
        string tempusn;
        cout<<"Enter a USN of student to delete"<<endl;
        cin>>tempusn;

        ifstream stu;
        stu.open("student.txt", ios:: in);

        ofstream newstu;
        newstu.open("newstudent.txt");

            stu >> elective;
            stu >> name;
            stu >> usn;

            while(!stu.eof())
            {
                if(tempusn != usn )
                {
                    newstu << endl;
                    newstu << elective;
                    newstu << endl;
                    newstu << name;
                    newstu << endl;
                    newstu << usn;
                    newstu << endl;

                }
                else
                {
                   cout<<"student removed successfully"<<endl;
                }

                    stu >> elective;
                    stu >> name;
                    stu >> usn;
            }
        stu.close();
        newstu.close();
        remove("student.txt");
        rename("newstudent.txt", "student.txt");
    }

    void editstudentusn(string &param)
    {
        string tempusn;
        cout<<"Enter a USN of student to edit"<<endl;
        cin>>tempusn;

        ifstream stu;
        stu.open("student.txt", ios:: in);

        ofstream newstu;
        newstu.open("newstudent.txt");

            stu >> elective;
            stu >> name;
            stu >> usn;
            while(!stu.eof())
            {
                 if(tempusn != usn )
                {
                    newstu << endl;
                    newstu << elective;
                    newstu << endl;
                    newstu << name;
                    newstu << endl;
                    newstu << usn;
                    newstu << endl;

                }
                else
                {
                    string usn1;
                    //char name1[20];
                    cout<<"Please enter new student name :";
                    cin>>name;
                    cout<<"Please enter new USN :";
                    cin>>usn1;
                    newstu << endl;
                    newstu << param;
                    newstu << endl;
                    newstu << name;
                    newstu << endl;
                    newstu << usn1;
                    newstu << endl;
                }
            stu >> elective;
            stu >> name;
            stu >> usn;
            }
            stu.close();
            newstu.close();
            remove("student.txt");
            rename("newstudent.txt", "student.txt");
    }

    void attendance(string &param)
    {
        cout<<"Enter P for present and N for absent"<<endl<<endl;
        cout<<"Please enter the date(dd/mm/yyyy) :";
        cin>>date;

        ofstream att;
        att.open("attendance.txt", ios::app);

        ifstream stu;
        stu.open("student.txt", ios::in);

        stu >> elective;
        stu >> name;
        stu >> usn;
        while(!stu.eof())
        {
            if(param == elective)
            {
            cout<<endl;
            cout<<"  "<<name<<" : ";
            cin>>present;
            att << endl;
            att << date;
            att << endl;
            att << elective;
            att << endl;
            att << name;
            att << endl;
            att << usn;
            att << endl;
            att << present;
            att << endl;
            }
            stu >> elective;
            stu >> name;
            stu >> usn;
       }
       stu.close();
       att.close();
    }
    void display_attendance_bydate(string &param)
    {
        string tempdate;
        cout<<"Please enter required date attendace(dd/mm/yyyy) :";
        cin>>tempdate;

        ifstream att;
        att.open("attendance.txt", ios::in);

        att >> date;
        att >> elective;
        att >> name;
        att >> usn;
        att >> present;
    while(!att.eof())
    {
        if(date==tempdate & param == elective)
        {
            cout<<" "<<name<<" : "<<present;
            cout<<endl;
            cout<<endl;
        }
        att >> date;
        att >> elective;
        att >> name;
        att >> usn;
        att >> present;
    }
    }

};

class electiveCpp : public SEM
{
public:
    void welcome()
    {
        system("cls");
        cout<<"Welcome to C++"<<endl;
    }
};

class electiverilog : public SEM
{
public:
    void welcome()
    {
        system("cls");
        cout<<"Welcome to Verilog"<<endl;
    }
};

class electiveLpp : public SEM
{
public:
    void welcome()
    {
        system("cls");
        cout<<"Welcome to Linear Programming"<<endl;
    }
};

class electiveSS : public SEM
{
public:
    void welcome()
    {
        system("cls");
        cout<<"Welcome to Sensor and actuator"<<endl;
    }
};

int main()
{
    string cplus="cpp";
    string Lp="Lpp";
    string ss="ss";
    string verilg="verilog";
   cout<<"Welcome to Elective Attendance System"<<endl;
   loop:
   cout<<" 1. C++"<<endl<<" 2. Verilog HDL"<<endl<<" 3. Sensor and actuator"<<endl<<" 4. Linear programming"<<endl<<" 5. EXIT "<<endl;
    int choice;
    cin>>choice;
    switch(choice)
    {
    case 1:
        {
            electiveCpp cpp;
            cpp.verifypassword();
            cpp.welcome();
            jump1:
            int choose = cpp.adminview();
            switch(choose)
            {
            case 1:
                {
                     cpp.reg_student(cplus);
                     break;
                }
            case 2:
                {
                     cpp.displaystulist(cplus);
                     break;
                }
            case 3:
                {
                     cpp.editstudentusn(cplus);
                     break;
                }
            case 4:
                {
                     cpp.deletestudent();
                     break;
                }
            case 5:
                {
                     cpp.attendance(cplus);
                     break;
                }
            case 6:
                {
                     cpp.display_attendance_bydate(cplus);
                     break;
                }
            case 7:
                {
                     cpp.reg_student(cplus);
                     break;
                }
            default:
                {
                     cpp.reg_student(cplus);
                     break;
                }
            }
            goto jump1;

            break;
        }
    case 2:
        {
            electiverilog verilog;
            verilog.verifypassword();
            verilog.welcome();
            jump2:
            int choose = verilog.adminview();
            switch(choose)
            {
            case 1:
                {
                     verilog.reg_student(verilg);
                     break;
                }
            case 2:
                {
                     verilog.displaystulist(verilg);
                     break;
                }
            case 3:
                {
                     verilog.editstudentusn(verilg);
                     break;
                }
            case 4:
                {
                     verilog.deletestudent();
                     break;
                }
            case 5:
                {
                     verilog.attendance(verilg);
                     break;
                }
            case 6:
                {
                     verilog.display_attendance_bydate(verilg);
                     break;
                }
            case 7:
                {
                     verilog.reg_student(verilg);
                     break;
                }
            default:
                {

                     break;
                }
            }
            goto jump2;
            break;
        }
    case 3:
        {
            electiveSS s;
            s.verifypassword();
            s.welcome();
            jump3:
            int choose = s.adminview();
            switch(choose)
            {
            case 1:
                {
                     s.reg_student(ss);
                     break;
                }
            case 2:
                {
                     s.displaystulist(ss);
                     break;
                }
            case 3:
                {
                     s.editstudentusn(ss);
                     break;
                }
            case 4:
                {
                     s.deletestudent();
                     break;
                }
            case 5:
                {
                     s.attendance(ss);
                     break;
                }
            case 6:
                {
                     s.display_attendance_bydate(ss);
                     break;
                }
            case 7:
                {
                     s.reg_student(ss);
                     break;
                }
            default:
                {

                     break;
                }
            }
            goto jump3;
            break;
        }
    case 4:
        {
            electiveLpp Lpp;
            Lpp.verifypassword();
            Lpp.welcome();
            jump4:
            int choose = Lpp.adminview();
            switch(choose)
            {
            case 1:
                {
                     Lpp.reg_student(Lp);
                     break;
                }
            case 2:
                {
                     Lpp.displaystulist(Lp);
                     break;
                }
            case 3:
                {
                     Lpp.editstudentusn(Lp);
                     break;
                }
            case 4:
                {
                     Lpp.deletestudent();
                     break;
                }
            case 5:
                {
                     Lpp.attendance(Lp);
                     break;
                }
            case 6:
                {
                     Lpp.display_attendance_bydate(Lp);
                     break;
                }
            case 7:
                {
                     Lpp.reg_student(Lp);
                     break;
                }
            default:
                {
                     break;
                }
            }
            goto jump4;
            break;
        }
    case 5:
        {
            exit(0);
            break;
        }
    default:
        {
            cout<<"Please enter valid input"<<endl;
            goto loop;
        }
    }
}

