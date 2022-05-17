


//guestlogin.cpp
#include "guestlogin.h"
#include "guest_console.h"


void guestlogin::guestsignup()
{
    system("CLS");

    const char* sql1;
    try
    {
        connection C("dbname = hotel_rentel_management_system user = postgres password = qwerty port = 5432");
        if (C.is_open())
        {
            double mob_num;
            string user_name, pwd;

            string first_name, last_name, mail, city;


            system("CLS");
            cout << setw(60) << "**********************************************" << endl;
            cout << setw(60) << "*             GUEST Sign-Up SCREEN           *" << endl;
            cout << setw(60) << "**********************************************" << endl;
            cout << endl;



            cout << "Enter your First Name          :"; cin >> first_name;
            cout << "Enter your Last Name           :"; cin >> last_name;
            cout << "Enter your Mobile Number       :"; cin >> mob_num;
            cout << "Enter your Email-Id            :"; cin >> mail;
            cout << "Enter your City                :"; cin >> city;

            cout << endl << endl;

            cout << setw(10) << "**********************************************" << endl;
            cout << setw(10) << "*           Guest LOGIN-IN Credentials:      *" << endl;
            cout << setw(10) << "**********************************************" << endl;
            cout << endl;

            cout << "Please Enter your User-Name    :";cin >> user_name;
            cout << "Please Enter your Password     :";cin >> pwd;




            std::string sql = "insert into guest_info  values(""'" + (first_name)+"'" + "," + "'" + (last_name)+"'" + ", \
            " + std::to_string(mob_num) + "," + "'" + (mail)+"'" + ", " + "'" + (city)+"'" + ")";


            std::string sql1 = "insert into guest_login  values(""'" + (user_name)+"'" + ", " + "'" + (pwd)+"'" + ")";

            work W(C);
            W.exec(sql);
            W.exec(sql1);
            W.commit();
            cout << endl << endl;

            cout << "Guest Sign-Up created successfully" << endl;
        }
        else
        {
            cout << "Can't open database" << endl;

        }

    }
    catch (const std::exception& e) {
        cerr << e.what() << std::endl;
    }
    system("cls");
    cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
    cout << "\t\t\t\t\t\t***********************************************" << endl;
    cout << "\t\t\t\t\t\t*                                             *" << endl;
    cout << "\t\t\t\t\t\t*        You have successfully Signed-Up      *" << endl;
    cout << "\t\t\t\t\t\t*       Thank you for Choosing our Hotel!!    *" << endl;
    cout << "\t\t\t\t\t\t*                                             *" << endl;
    cout << "\t\t\t\t\t\t***********************************************" << endl;

    _getch();
    guest_login();


}
void guestlogin::guestsignin()
{

    guest_console guest;
    string userName;
    string password, get_password;
    connection C("dbname = hotel_rentel_management_system user = postgres password = qwerty port = 5432");
    int test = 0;
    bool check = false;
    system("CLS");

    do {
        system("cls");

        cout << endl;

        cout << "\t\t\t\t\t\t   ********************************************" << endl;
        cout << "\t\t\t\t\t\t   *             GUEST SIGN-IN SCREEN         *" << endl;
        cout << "\t\t\t\t\t\t   ********************************************" << endl;

        cout << endl;
        cout << endl << endl << endl << endl;

        cout << "\t\t\t\t\t\t   Username     : ";
        cin >> userName;
        cout << "\t\t\t\t\t\t   Password     : ";
        cin >> password;
        cin.ignore();
        std::string sql = "select Password from guest_login where User_name = (""'" + (userName)+"'" + ")";
        work W(C);

        result R(W.exec(sql));
        for (result::const_iterator c = R.begin(); c != R.end(); ++c) {

            get_password = c[0].as<string>();
        }
        W.commit();
        if (get_password == password)
        {
            cout << endl << endl << endl;
            cout << "\t\t\t\t\t\t   Login successfully!" << endl;
            cout << "\t\t\t\t\t\t   Press any key to continue!";
            (void)_getch();


            guest.guest_menu();
            check = true;

        }

        else {
            system("cls");
            test++;
            cout << endl << endl << endl << endl << endl << endl;
            cout << "\t\t\t\t\t\tYou are only allowed to try 3 times. You just have " << (3 - test) << " times left!" << endl;
            cout << "\t\t\t\t\t\tPress any key to continue!" << endl;
            (void)getchar();
            if (test == 3) {
                cout << "\t\t\tYou have entered the wrong username or password 3 times and you are not allowed to login to the system!" << endl;
                (void)getchar();
                //exitSys();

            }
        }
    } while (!check);

}