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

bool isAllDigits(const string& text)
{
    if (text.empty())
    {
        return false;
    }

    for (int i = 0; i < (int)text.length(); i++)
    {
        if (text[i] < '0' || text[i] > '9')
        {
            return false;
        }
    }

    return true;
}

int readInt()
{
    string text = trim(readLine());

    if (!isAllDigits(text) || text.length() > 9)
    {
        return -1;
    }

    return stoi(text);
}

string formatMoney(double amount)
{
    long long cents = (long long)(amount * 100 + 0.5);
    long long pesos = cents / 100;
    int centavos = (int)(cents % 100);

    string digits = to_string(pesos);
    string result = "";
    int count = 0;

    for (int i = (int)digits.length() - 1; i >= 0; i--)
    {
        result = digits[i] + result;
        count++;

        if (count % 3 == 0 && i > 0)
        {
            result = "," + result;
        }
    }

    string centavoText = to_string(centavos);
    if (centavos < 10)
    {
        centavoText = "0" + centavoText;
    }

    return result + "." + centavoText;
}

int main()
{
    string accountName = "Juan Dela Cruz";
    int accountNumber = 20260001;
    string pin = "1234";
    double balance = 10000.00;

    cout << "\n========================================" << endl;
    cout << "             CSDC BANK ATM" << endl;
    cout << "========================================" << endl;

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

    int choice;
    bool exitATM = false;

    do
    {
        cout << "\n========================================" << endl;
        cout << "             CSDC BANK ATM" << endl;
        cout << "========================================" << endl;
        cout << "Account: " << accountName << endl;
        cout << "Account Number: " << accountNumber << endl;
        cout << "\n[1] Balance Inquiry" << endl;
        cout << "[2] Deposit" << endl;
        cout << "[3] Withdraw" << endl;
        cout << "[4] Fast Cash" << endl;
        cout << "[5] Change PIN" << endl;
        cout << "[6] Exit" << endl;
        cout << "\nEnter choice: ";

        choice = readInt();

        switch (choice)
        {
            case 1:
            {
                cout << "\n------------------------------" << endl;
                cout << "        BALANCE INQUIRY" << endl;
                cout << "------------------------------" << endl;
                cout << "Current Balance: PHP " << formatMoney(balance) << endl;
                break;
            }

            case 2:
            {
                cout << "\nDeposit is coming soon." << endl;
                break;
            }

            case 3:
            {
                cout << "\nWithdraw is coming soon." << endl;
                break;
            }

            case 4:
            {
                cout << "\nFast Cash is coming soon." << endl;
                break;
            }

            case 5:
            {
                cout << "\nChange PIN is coming soon." << endl;
                break;
            }

            case 6:
            {
                exitATM = true;
                break;
            }

            default:
            {
                cout << "\nInvalid selection." << endl;
                cout << "Please choose an option from 1 to 6." << endl;
            }
        }

    } while (!exitATM);

    cout << "\n========================================" << endl;
    cout << "         TRANSACTION COMPLETE" << endl;
    cout << "========================================" << endl;
    cout << "Thank you for using CSDC Bank ATM." << endl;
    cout << "Please take your card." << endl;
    cout << "Have a nice day!" << endl;

    return 0;
}
