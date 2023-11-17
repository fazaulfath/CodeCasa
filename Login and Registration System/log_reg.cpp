#include<iostream>
#include<fstream>
#include<string>
using namespace std;

void reg();
void login();
void forgot();
void updatePassword(const string& username);

int main();

void reg() 
{
    string rUserid, rpassword, rid, rpass;
    cout << "\n----------------------------------------------------\n";
    cout << "Enter Username and Password for Registration\n";
    cout << "----------------------------------------------------\n";
    cout << "Enter Username:";
    cin >> rUserid;

    ifstream checkIfExists("records.txt");
    string existingUsername;
    bool usernameExists = false;
    while (checkIfExists >> existingUsername >> rpass) 
    {
        if (existingUsername == rUserid) 
        {
            usernameExists = true;
            break;
        }
    }
    checkIfExists.close();

    if (usernameExists) 
    {
        cout << "\tUsername already exists! Please choose another one.\n";
        reg(); // Prompt user to enter a different username
    } 
    else 
    {
        cout << "Enter the Password:";
        cin >> rpassword;

        ofstream f1("records.txt", ios::app);
        f1 << rUserid << ' ' << rpassword << endl;
        cout << "\n\t Registration was successful!\n";
        main();
    }
}

void login() 
{
    int count = 0;
    string userId, password, id, pass;
    cout << "----------------------------------------------------\n";
    cout << "\tPlease enter Username and Password:\n";
    cout << "----------------------------------------------------\n";
    cout << "Username:";
    cin >> userId;
    cout << "Password:";
    cin >> password;

    ifstream input("records.txt");
    while (input >> id >> pass)
    {
        if (id == userId && pass == password) 
        {
            count = 1;
        }
    }
    input.close();
    if (count == 1) 
    {
        cout << "\nYour Login is Successful\nThanks for logging in!\n";
    } 
    else 
    {
        cout << "\nUsername or Password is incorrect.\n";
        cout << "Please register if you don't have an account.\n";
    }
    main();
}

void forgot() 
{
    string userid;
    cout << "Enter the username for which you want to update the password: ";
    cin >> userid;

    updatePassword(userid);

    main();
}

void updatePassword(const string& username) 
{
    int count = 0;
    string id, pass, newPassword;

    fstream file("records.txt", ios::in | ios::out);

    while (file >> id >> pass) 
    {
        if (id == username) 
        {
            count = 1;
            cout << "Enter your new password: ";
            cin >> newPassword;

            // Move the file pointer to the position where the password starts
            file.seekp(static_cast<long long>(file.tellg()) - pass.length() - 1);
            file << newPassword; // Overwrite the existing password
            file.flush();
            cout << "\nPassword updated successfully!\n";
            break;
        }
    }

    file.close();

    if (count == 0) 
    {
        cout << "\t\t\tSorry, the provided username was not found!\n";
    }
}

int main() 
{
    int c;
    cout << "____________________________________________________\n" << endl;
    cout << "              Welcome to Login Page                 \n";
    cout << "____________________________________________________\n\n";
    cout << "----------- Menu -----------\n";
    cout << "1. Register\n";
    cout << "2. Login\n";
    cout << "3. Forgot Password\n";
    cout << "4. Exit\n";
    cout << "Enter Your Choice:";
    cin >> c;

    switch (c) 
    {
        case 1:
            reg();
            break;
        case 2:
            login();
            break;
        case 3:
            forgot();
            break;
        case 4:
            cout << "\t\t\t Thank you!!!\n\n   " << endl;
            break;
        default:
            system("cls");
            cout << "\t\t Please Select Valid Option:" << endl;
            main();
    }
    return 0;
}
