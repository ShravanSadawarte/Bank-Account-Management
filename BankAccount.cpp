#include <iostream>
#include <iomanip>
#include "BankAccount.h"

// Constructor: initialize the object with starting values.
// The part after ':' is called an initializer list.
BankAccount::BankAccount(int accountNumber, string accountHolderName, double balance)
    : accountNumber(accountNumber), accountHolderName(accountHolderName), balance(balance)
{
    // NOTE: we do NOT add an "Initial Deposit" transaction here.
    // BankSystem::createAccount() adds it, so loading from file
    // does not create a duplicate entry.
}

int BankAccount::getAccountNumber()
{
    return accountNumber;
}

string BankAccount::getAccountHolderName()
{
    return accountHolderName;
}

double BankAccount::getBalance()
{
    return balance;
}

vector<Transaction> BankAccount::getTransactions()
{
    return transactions;
}

void BankAccount::addTransaction(string type, double amount, string description)
{
    // Create a Transaction object and store it in our vector.
    Transaction t(type, amount, description);
    transactions.push_back(t);
}

// ABSTRACTION: the user just calls deposit(2000).
// They do not need to know HOW balance and history are updated inside.
void BankAccount::deposit(double amount)
{
    if (amount <= 0)
    {
        cout << "Amount must be greater than 0." << endl;
        return;
    }

    balance = balance + amount;
    addTransaction("Deposit", amount, "Cash Deposit");
}

bool BankAccount::withdraw(double amount)
{
    if (amount <= 0)
    {
        cout << "Amount must be greater than 0." << endl;
        return false;
    }

    if (amount > balance)
    {
        cout << "Insufficient balance." << endl;
        return false;
    }

    balance = balance - amount;
    addTransaction("Withdrawal", amount, "Cash Withdrawal");
    return true;
}

// Used by BankSystem when transferring money OUT of this account.
bool BankAccount::transferOut(double amount, int toAccountNumber)
{
    if (amount <= 0)
    {
        cout << "Amount must be greater than 0." << endl;
        return false;
    }

    if (amount > balance)
    {
        cout << "Insufficient balance." << endl;
        return false;
    }

    balance = balance - amount;

    string message = "Transfer to Account " + to_string(toAccountNumber);
    addTransaction("Transfer", amount, message);
    return true;
}

// Used by BankSystem when receiving money INTO this account.
void BankAccount::transferIn(double amount, int fromAccountNumber)
{
    balance = balance + amount;

    string message = "Received from Account " + to_string(fromAccountNumber);
    addTransaction("Transfer", amount, message);
}

void BankAccount::displayAccountDetails()
{
    cout << "================================" << endl;
    cout << "       ACCOUNT DETAILS" << endl;
    cout << "================================" << endl;
    cout << "Account Number : " << accountNumber << endl;
    cout << "Account Holder : " << accountHolderName << endl;
    cout << "Balance        : Rs." << balance << endl;
    cout << "================================" << endl;
}

void BankAccount::displayTransactionHistory()
{
    cout << "========================================" << endl;
    cout << "        TRANSACTION HISTORY" << endl;
    cout << "========================================" << endl;
    cout << "Account Number: " << accountNumber << endl;
    cout << endl;

    if (transactions.size() == 0)
    {
        cout << "No transactions available." << endl;
        cout << "========================================" << endl;
        return;
    }

    cout << left << setw(13) << "Type"
         << setw(13) << "Amount"
         << "Description" << endl;

    for (int i = 0; i < (int)transactions.size(); i++)
    {
        string amountText = "Rs." + to_string((int)transactions[i].getAmount());

        // If amount has paise (decimal part), show full value instead.
        // Keeps the table simple for beginners while staying correct.
        if (transactions[i].getAmount() != (int)transactions[i].getAmount())
        {
            amountText = "Rs." + to_string(transactions[i].getAmount());
        }

        cout << left << setw(13) << transactions[i].getType()
             << setw(13) << amountText
             << transactions[i].getDescription() << endl;
    }

    cout << "========================================" << endl;
}
