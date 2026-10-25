#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>

using namespace std;

const int MAX_ATTEMPTS = 3;
const double MAX_DEPOSIT = 1000000.00;
const double MAX_BALANCE = 999999999.99;

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

double readDouble()
{
    string text = trim(readLine());

    if (text.empty() || text.length() > 15)
    {
        return -1.0;
    }

    int dotCount = 0;
    int digitCount = 0;
    int digitsAfterDot = 0;

    for (int i = 0; i < (int)text.length(); i++)
    {
        char c = text[i];

        if (c == '.')
        {
            dotCount++;
        }
        else if (c >= '0' && c <= '9')
        {
            digitCount++;

            if (dotCount == 1)
            {
                digitsAfterDot++;
            }
        }
        else
        {
            return -1.0;
        }
    }

    if (dotCount > 1 || digitCount == 0 || digitsAfterDot > 2)
    {
        return -1.0;
    }

    return stod(text);
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
    int bills100 = 20;
    int bills500 = 10;
    int bills1000 = 10;

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
                cout << "\n------------------------------" << endl;
                cout << "            DEPOSIT" << endl;
                cout << "------------------------------" << endl;
                cout << "Enter deposit amount: PHP ";

                double depositAmount = readDouble();

                if (depositAmount <= 0)
                {
                    cout << "\nInvalid deposit amount." << endl;
                    cout << "Enter a number greater than zero with at most 2 decimal places." << endl;
                }
                else if (depositAmount > MAX_DEPOSIT)
                {
                    cout << "\nDeposit declined." << endl;
                    cout << "Maximum per deposit: PHP " << formatMoney(MAX_DEPOSIT) << endl;
                }
                else if (balance + depositAmount > MAX_BALANCE)
                {
                    cout << "\nDeposit declined." << endl;
                    cout << "Maximum account balance: PHP " << formatMoney(MAX_BALANCE) << endl;
                }
                else
                {
                    balance = round((balance + depositAmount) * 100) / 100;

                    cout << "\nDeposit successful." << endl;
                    cout << "Amount Deposited: PHP " << formatMoney(depositAmount) << endl;
                    cout << "New Balance:      PHP " << formatMoney(balance) << endl;
                }
                break;
            }

            case 3:
            {
                int withdrawalAmount;

                cout << "\n------------------------------" << endl;
                cout << "           WITHDRAW" << endl;
                cout << "------------------------------" << endl;
                cout << "Enter withdrawal amount: PHP ";

                withdrawalAmount = readInt();

                if (withdrawalAmount <= 0)
                {
                    cout << "\nInvalid withdrawal amount." << endl;
                    cout << "Withdrawal must be a whole number greater than zero." << endl;
                    break;
                }

                if (withdrawalAmount % 100 != 0)
                {
                    cout << "\nInvalid withdrawal amount." << endl;
                    cout << "Amount must be a multiple of PHP 100." << endl;
                    break;
                }

                if (withdrawalAmount > balance)
                {
                    cout << "\nTransaction declined." << endl;
                    cout << "Insufficient account balance." << endl;
                    break;
                }

                int atmCash = bills100 * 100 + bills500 * 500 + bills1000 * 1000;

                if (withdrawalAmount > atmCash)
                {
                    cout << "\nTransaction declined." << endl;
                    cout << "Insufficient cash in the ATM." << endl;
                    break;
                }

                int use100 = 0;
                int use500 = 0;
                int use1000 = 0;

                int dispensingMethod;

                do
                {
                    cout << "\nSelect cash dispensing method:" << endl;
                    cout << "[1] PHP 100 bills" << endl;
                    cout << "[2] PHP 500 bills" << endl;
                    cout << "[3] PHP 1000 bills" << endl;
                    cout << "Enter choice: ";

                    dispensingMethod = readInt();

                    if (dispensingMethod < 1 || dispensingMethod > 3)
                    {
                        cout << "Invalid choice. Please select 1 to 3." << endl;
                    }
                } while (dispensingMethod < 1 || dispensingMethod > 3);

                int denomination;
                int available;

                if (dispensingMethod == 1)
                {
                    denomination = 100;
                    available = bills100;
                }
                else if (dispensingMethod == 2)
                {
                    denomination = 500;
                    available = bills500;
                }
                else
                {
                    denomination = 1000;
                    available = bills1000;
                }

                if (withdrawalAmount % denomination != 0)
                {
                    cout << "\nUnable to dispense PHP " << withdrawalAmount << endl;
                    cout << "using PHP " << denomination << " bills." << endl;
                    cout << "Transaction cancelled." << endl;
                    break;
                }

                int requiredBills = withdrawalAmount / denomination;

                if (requiredBills > available)
                {
                    cout << "\nInsufficient PHP " << denomination << " bills in the ATM." << endl;
                    cout << "Transaction cancelled." << endl;
                    break;
                }

                if (dispensingMethod == 1)
                {
                    use100 = requiredBills;
                }
                else if (dispensingMethod == 2)
                {
                    use500 = requiredBills;
                }
                else
                {
                    use1000 = requiredBills;
                }

                cout << "\nDispensing cash..." << endl;

                for (int i = 1; i <= use1000; i++)
                {
                    cout << "Bill " << i << ": PHP 1000" << endl;
                }

                for (int i = 1; i <= use500; i++)
                {
                    cout << "Bill " << use1000 + i << ": PHP 500" << endl;
                }

                for (int i = 1; i <= use100; i++)
                {
                    cout << "Bill " << use1000 + use500 + i << ": PHP 100" << endl;
                }

                cout << "\nCash Breakdown:" << endl;
                if (use1000 > 0)
                {
                    cout << "PHP 1000 x " << use1000 << " = PHP " << use1000 * 1000 << endl;
                }
                if (use500 > 0)
                {
                    cout << "PHP 500  x " << use500 << " = PHP " << use500 * 500 << endl;
                }
                if (use100 > 0)
                {
                    cout << "PHP 100  x " << use100 << " = PHP " << use100 * 100 << endl;
                }

                balance = round((balance - withdrawalAmount) * 100) / 100;
                bills100 = bills100 - use100;
                bills500 = bills500 - use500;
                bills1000 = bills1000 - use1000;

                cout << "\nWithdrawal successful." << endl;
                cout << "Amount Withdrawn:  PHP " << formatMoney(withdrawalAmount) << endl;
                cout << "Remaining Balance: PHP " << formatMoney(balance) << endl;
                cout << "Please take your cash." << endl;

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
