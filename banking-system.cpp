#include <iostream>
#include <cstring>
using namespace std;

class BankAccount
{

private:
    int accountNumber;
    char accountHolderName[50];
    double balance;

public:
    BankAccount(int accNumber, char accHolder[], double amount)
    {
        accountNumber = accNumber;
        strcpy(accountHolderName, accHolder);
        balance = amount;
    }

    void deposit(double amount)
    {
        balance = balance + amount;
    }
    void withdraw(double amount)
    {
        if (balance >= amount)
        {
            balance = balance - amount;
            cout << "Withdrawing...." << endl;
        }
        else
        {
            cout << "Not enough Balance..." << endl;
        }
    }

    int getaccountNumber()
    {
        return accountNumber;
    }

    double getBalance()
    {
        return balance;
    }
    char *getaccountHolderName()
    {
        return accountHolderName;
    }

    void displayAccountInfo()
    {
        cout << "Account Number : " << getaccountNumber() << endl;
        cout << "Account Holder : " << getaccountHolderName() << endl;
        cout << "Balance : " << getBalance() << endl;
    }
    virtual void calculateInterest()
    {
    }
};

class SavingsAccount : public BankAccount
{
private:
    double interestRate;

public:
    SavingsAccount(int accNumber, char accHolder[], double amount, double rate)
        : BankAccount(accNumber, accHolder, amount)
    {
        interestRate = rate;
    }

    void calculateInterest() override
    {
        double interest;

        interest = getBalance() * (interestRate / 100);

        cout << "Interest : " << interest << endl;
    }
};

class CheckingAccount : public BankAccount
{
private:
    double overdraftLimit;

public:
    CheckingAccount(int accNumber, char accHolder[], double amount, double overdraft)
        : BankAccount(accNumber, accHolder, amount)
    {
        overdraftLimit = overdraft;
    }
    void checkOverdraft(double amount)
    {
        if (amount <= getBalance() + overdraftLimit)
        {
            cout << "Withdrawal allowed." << endl;
        }
        else
        {
            cout << "Overdraft limit exceeded." << endl;
        }
    }
};

class FixedDepositAccount : public BankAccount
{
private:
    int term;

public:
    FixedDepositAccount(int accNumber, char accHolder[], double amount, int term)
        : BankAccount(accNumber, accHolder, amount)
    {
        this->term = term;
    }
    void calculateInterest() override
    {
        double interestRate = 7.0;

        double interest = getBalance() * (interestRate / 100) * (term / 12.0);

        cout << "Fixed Deposit Interest : " << interest << endl;
    }
};
int main()
{
    BankAccount *account = nullptr;

    SavingsAccount *savings = nullptr;
    CheckingAccount *checking = nullptr;
    FixedDepositAccount *fixed = nullptr;

    int choice;

    do
    {
        cout << "\n===== BANKING SYSTEM =====" << endl;
        cout << "1. Create Savings Account" << endl;
        cout << "2. Create Checking Account" << endl;
        cout << "3. Create Fixed Deposit Account" << endl;
        cout << "4. Deposit" << endl;
        cout << "5. Withdraw" << endl;
        cout << "6. Display Account Info" << endl;
        cout << "7. Calculate Interest" << endl;
        cout << "8. Check Overdraft" << endl;
        cout << "9. Exit" << endl;

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            int accNumber;
            char accHolder[50];
            double amount;
            double rate;

            cout << "Enter Account Number: ";
            cin >> accNumber;

            cout << "Enter Account Holder Name: ";
            cin >> accHolder;

            cout << "Enter Starting Balance: ";
            cin >> amount;

            cout << "Enter Interest Rate: ";
            cin >> rate;

            savings = new SavingsAccount(accNumber, accHolder, amount, rate);

            account = savings;

            cout << "Savings Account Created." << endl;

            break;
        }

        case 2:
        {
            int accNumber;
            char accHolder[50];
            double amount;
            double overdraft;

            cout << "Enter Account Number: ";
            cin >> accNumber;

            cout << "Enter Account Holder Name: ";
            cin >> accHolder;

            cout << "Enter Starting Balance: ";
            cin >> amount;

            cout << "Enter Overdraft Limit: ";
            cin >> overdraft;

            checking = new CheckingAccount(
                accNumber,
                accHolder,
                amount,
                overdraft);

            account = checking;

            cout << "Checking Account Created." << endl;

            break;
        }

        case 3:
        {
            int accNumber;
            char accHolder[50];
            double amount;
            int term;

            cout << "Enter Account Number: ";
            cin >> accNumber;

            cout << "Enter Account Holder Name: ";
            cin >> accHolder;

            cout << "Enter Starting Balance: ";
            cin >> amount;

            cout << "Enter Term in Months: ";
            cin >> term;

            fixed = new FixedDepositAccount(
                accNumber,
                accHolder,
                amount,
                term);

            account = fixed;

            cout << "Fixed Deposit Account Created." << endl;

            break;
        }

        case 4:
        {
            if (account != nullptr)
            {
                double amount;

                cout << "Enter Deposit Amount: ";
                cin >> amount;

                account->deposit(amount);
            }
            else
            {
                cout << "Create an account first." << endl;
            }

            break;
        }

        case 5:
        {
            if (account != nullptr)
            {
                double amount;

                cout << "Enter Withdrawal Amount: ";
                cin >> amount;

                account->withdraw(amount);
            }
            else
            {
                cout << "Create an account first." << endl;
            }

            break;
        }

        case 6:
        {
            if (account != nullptr)
            {
                account->displayAccountInfo();
            }
            else
            {
                cout << "Create an account first." << endl;
            }

            break;
        }

        case 7:
        {
            if (account != nullptr)
            {
                account->calculateInterest();
            }
            else
            {
                cout << "Create an account first." << endl;
            }

            break;
        }

        case 8:
        {
            if (checking != nullptr)
            {
                double amount;

                cout << "Enter Withdrawal Amount: ";
                cin >> amount;

                checking->checkOverdraft(amount);
            }
            else
            {
                cout << "Create a Checking Account first." << endl;
            }

            break;
        }

        case 9:
            cout << "Exiting..." << endl;
            break;

        default:
            cout << "Invalid choice." << endl;
        }

    } while (choice != 9);

    delete savings;
    delete checking;
    delete fixed;

    return 0;
}