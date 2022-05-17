
#include "guest_console.h"

//guest_console.cpp

void guest_console::updateguestinfo()
{

    system("CLS");

    try
    {
        connection C("dbname = hotel_rentel_management_system user = postgres password = qwerty port = 5432");
        if (C.is_open())
        {
            do
            {
                system("CLS");
                cout << setw(60) << "**********************************************" << endl;
                cout << setw(60) << "*      UPDATION OF GUEST INFORMATION SCREEN  *" << endl;
                cout << setw(60) << "**********************************************" << endl;
                cout << endl;

                string u_choice, u_col;
                double mob_num;
                cout << "Enter the Mobile number:"; cin >> mob_num;
                cout << endl;

                cout << "Enter the Field that need to be updated" << endl;;

                cout << "\t=> First_name   " << endl;
                cout << "\t=> Last_name " << endl;
                cout << "\t=> Email_id " << endl;
                cout << "\t=> City " << endl;



                cout << "Enter your choice of field : ";cin >> u_col;

                if (u_col == "First_name" || u_col == "Last_name" || u_col == "Email_id" || u_col == "City")
                {


                    cout << "Enter the updatation: ";cin >> u_choice;

                    std::string sql = "update guest_info set " + (u_col)+" = " + "'" + (u_choice)+"'" + "  where mobile_number = (" + std::to_string(mob_num) + ")";

                    work W(C);

                    W.exec(sql);
                    W.commit();
                    cout << "Do you want to you continue to update ?... press [y/n]";
                    cin >> c1;
                }
                else
                {
                    cout << endl;
                    cout << "Entered Field is incorrect\n";
                    cout << "Please re-Enter your choice correctly:";
                    (void)_getch();
                    guest_menu();

                }
            } while (c1 == 'y');

            cout << "Room's Records Updated successfully" << endl;
        }
        else
        {
            cout << "Can't open database" << endl;

        }

    }
    catch (const std::exception& e) {
        cerr << e.what() << std::endl;

    }
    guest_menu();
}

void guest_console::bookroom()
{
    char c1;
    int t = 1, b = 1;
    const char* sql1;
    const char* sql2;
    system("CLS");
    try
    {
        connection C("dbname = hotel_rentel_management_system user = postgres password = qwerty port = 5432");
        if (C.is_open())
        {
            do
            {
                if (t < 3)
                {
                    system("CLS");
                    cout << setw(60) << "**********************************************" << endl;
                    cout << setw(60) << "*              ROOM BOOKING SCREEN           *" << endl;
                    cout << setw(60) << "**********************************************" << endl;
                    cout << endl;
                    int room_num, no_person;
                    double mob_num;


                    cout << endl;
                    cout << "Enter the Mobile number          :"; cin >> mob_num;

                    cout << "Enter the Room number          :"; cin >> room_num;

                    std::string sql = "select occupied_status from hotel_rooms_info  where room_number = (" + std::to_string(room_num) + ")";
                    work W(C);
                    result R(W.exec(sql));
                    result::const_iterator  c = R.begin();


                    if (c[0].as<string>() == "Yes" || c[0].as<string>() == "Booked")
                    {
                        cout << endl << "The Room has been already Reserved " << endl;
                        cout << "Please Try again... " << endl;
                        (void)_getch();
                        bookroom();
                    }

                    cout << "Enter Number of Person for accomodation   :"; cin >> no_person;


                    std::string sql1 = "insert into booking_info values(" + std::to_string(mob_num) + "," + std::to_string(room_num) + "," + std::to_string(no_person) + "," + std::to_string(b) + " )";
                    b++;

                    std::string sql2 = "update hotel_rooms_info set occupied_status = 'Booked'\
                where room_number = (" + std::to_string(room_num) + ")";




                    W.exec(sql1);
                    W.exec(sql2);
                    W.commit();
                    cout << "Do you want to you continue to Book ?... press [y/n]";
                    cin >> c1;
                    t++;

                }
                else
                {
                    cout << endl << endl;
                    cout << "A Guest can Only Book 2 Rooms" << endl;
                    (void)_getch();
                    guest_menu();

                }


            } while (c1 == 'y');

            cout << "Room Booked successfully" << endl;
        }
        else
        {
            cout << "Can't open database" << endl;

        }

    }
    catch (const std::exception& e) {
        cerr << e.what() << std::endl;

    }
    guest_menu();
}

void guest_console::cancelbooking()
{

    char c1;
    int t = 1;

    const char* sql1;
    system("CLS");
    try
    {
        connection C("dbname = hotel_rentel_management_system user = postgres password = qwerty port = 5432");
        if (C.is_open())
        {
            do
            {

                system("CLS");
                cout << setw(60) << "**********************************************" << endl;
                cout << setw(60) << "*              CANCEL BOOKING SCREEN         *" << endl;
                cout << setw(60) << "**********************************************" << endl;
                cout << endl;
                int room_num;
                double mob_num;


                cout << endl;
                cout << "Enter the Mobile number          :"; cin >> mob_num;
                cout << "Enter the Room number            :"; cin >> room_num;





                std::string sql = "delete from booking_info where mobile_Number = (" + std::to_string(mob_num) + ") and  room_allotment=(" + std::to_string(room_num) + ")";

                std::string sql1 = "update hotel_rooms_info set occupied_status = 'No'\
                            where room_number = (" + std::to_string(room_num) + ")";


                work W(C);

                W.exec(sql);
                W.exec(sql1);
                W.commit();
                if (t < 2)
                {
                    cout << endl;
                    cout << "Do you want to you cancel Booked Room again ?... press [y/n]";
                    cin >> c1;
                }
                else
                {

                    cout << endl;
                    cout << "Booked Room Cancelation done successfully" << endl;

                    (void)_getch();
                    guest_menu();


                }

                t++;
            } while (c1 == 'y');

            cout << "Booked Room Cancelation done successfully" << endl;
        }
        else
        {
            cout << "Can't open database" << endl;

        }

    }
    catch (const std::exception& e) {
        cerr << e.what() << std::endl;

    }
    guest_menu();
}

int guest_console::reserve()
{

    system("CLS");

    const char* sql1, * sql2, * sql3, * sql4;
    const char* sql5, * sql6, * sql7;
    int stay, room_all;
    try
    {
        connection C("dbname = hotel_rentel_management_system user = postgres password = qwerty port = 5432");
        if (C.is_open())
        {

            double mob_num;
            string check_in;

            do
            {
                system("CLS");
                cout << setw(60) << "**********************************************" << endl;
                cout << setw(60) << "*              RESERVATION OF ROOM           *" << endl;
                cout << setw(60) << "**********************************************" << endl;
                cout << endl;

                cout << "Enter Your Mobile Number       :"; cin >> mob_num;
                return mob_num;
                cout << "Enter the Room Number for accommodation    :"; cin >> room_all;

                std::string sql = "select occupied_status from hotel_rooms_info  where room_number = (" + std::to_string(room_all) + ")";
                work W(C);
                result R(W.exec(sql));
                result::const_iterator  c = R.begin();


                if (c[0].as<string>() == "Yes")
                {
                    cout << endl << "The Room has been already Reserved " << endl;
                    cout << "Please Try again... " << endl;
                    (void)_getch();
                    reserve();
                }
                else
                {
                    cout << "Enter the Check-IN Date  [yyyy-mm-dd]      :"; cin >> check_in;
                    cout << "Enter How many days of Stay                :"; cin >> stay;


                    std::string sql1 = "update guest_info set check_in_date =(" "'" + (check_in)+"'" + ") \
                    where mobile_number =(" + std::to_string(mob_num) + ")";
                    std::string sql2 = "update guest_info set no_days =(" + std::to_string(stay) + ") \
                    where mobile_number =(" + std::to_string(mob_num) + ")";

                    std::string sql3 = "update guest_info set room_alloted_number =(" + std::to_string(room_all) + ") \
                    where mobile_number =(" + std::to_string(mob_num) + ")";
                    std::string sql4 = "update hotel_rooms_info set occupied_status = 'Yes'\
                    where room_number = (" + std::to_string(room_all) + ")";

                    W.exec(sql1);
                    W.exec(sql2);
                    W.exec(sql3);
                    W.exec(sql4);

                    cout << endl;

                    W.commit();


                    cout << " Do you want to you continue to Reserve again... press (y/n)";
                    cin >> c1;
                }

            } while (c1 == 'y');

            cout << endl; cout << endl;
            cout << "Room Reserved successfully" << endl;
            (void)_getch();

            //automatic check-out
         //   std::string sql5 = "  SELECT DATE_PART('day', (current_date + 2)::timestamp - '2022-05-17 01:00:00'::timestamp  ) from guest_info\
                    where  mobile_number = 9898787873 ";


        }
        else
        {
            cout << "Can't open database" << endl;

        }

    }
    catch (const std::exception& e) {
        cerr << e.what() << std::endl;
    }

    guest_menu();

}

void guest_console::check_out()
{
    system("CLS");
    try
    {
        connection C("dbname = hotel_rentel_management_system user = postgres password = qwerty port = 5432");
        if (C.is_open())
        {
            double mob_num, room_all;
            string  check_out;


            do
            {
                system("CLS");
                cout << setw(60) << "**********************************************" << endl;
                cout << setw(60) << "*            GUEST Check-Out SCREEN          *" << endl;
                cout << setw(60) << "**********************************************" << endl;
                cout << endl;

                cout << "Enter the Alloted Room Number :"; cin >> room_all;
                cout << "Enter the Mobile Number for Checking-out  :"; cin >> mob_num;

                cout << "Enter the Check-OUT Date [yyyy-mm-dd]     :"; cin >> check_out;

                std::string sql = "update guest_info set check_out_date =(" "'" + (check_out)+"'" + ") \
                    where mobile_number =(" + std::to_string(mob_num) + ")";

                std::string sql1 = "update hotel_rooms_info  set occupied_status = 'No'\
                where room_number = (" + std::to_string(room_all) + ")";

                work W(C);
                W.exec(sql);
                W.exec(sql1);
                W.commit();
                cout << endl;
                cout << " Do you want to continue to Check-out for another room ... press (y/n)";
                cin >> c1;

            } while (c1 == 'y');
            cout << endl;
            cout << "Checked out successfully" << endl;
        }
        else
        {
            cout << "Can't open database" << endl;

        }

    }
    catch (const std::exception& e) {
        cerr << e.what() << std::endl;
    }
    guest_menu();
}