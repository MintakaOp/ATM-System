#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

const int MAX_ATTEMPTS = 3;

string readLine()
{
    string line;

    if (!getline(cin, line))
    {
        cout << "\n[System] Input closed. Exiting ATM." << endl;
        exit(0);
    }

    return line;
}

string trim(const string& text)
{
    size_t first = text.find_first_not_of(" \t\r\n");

    if (first == string::npos)
    {
        return "";
    }

    size_t last = text.find_last_not_of(" \t\r\n");
    return text.substr(first, last - first + 1);
}

int main()
{
    string accountName = "Juan Dela Cruz";
    int accountNumber = 20260001;
    string pin = "1234";

    cout << "\n========================================" << endl;
    cout << "             CSDC BANK ATM" << endl;
    cout << "========================================" << endl;
    cout << "Account: " << accountName << endl;
    cout << "Account Number: " << accountNumber << endl;

    int attempts = 0;
    bool authenticated = false;

    while (attempts < MAX_ATTEMPTS && !authenticated)
    {
        string enteredPin;
        cout << "Enter PIN: ";
        enteredPin = trim(readLine());

        if (enteredPin == pin)
        {
            authenticated = true;
            cout << "PIN correct. Login successful!" << endl;
        }
        else
        {
            attempts++;
            cout << "\nIncorrect PIN." << endl;
            cout << "Attempts remaining: " << MAX_ATTEMPTS - attempts << endl << endl;
        }
    }

    if (!authenticated)
    {
        cout << "Too many incorrect attempts." << endl;
        cout << "ATM session terminated." << endl;
        return 0;
    }

    cout << "\nWelcome, " << accountName << "." << endl;

    return 0;
}
