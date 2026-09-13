#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include <string>
#include <vector>
#include "Transaction.h"
using namespace std;

// BankAccount class represents ONE bank account.
// This is the main OOP example:
//   - Data (account number, name, balance) is kept PRIVATE (encapsulation).
//   - Other code can only use PUBLIC methods like deposit() and withdraw().
class BankAccount
{
private:
    int accountNumber;
    string accountHolderName;

    // Private data protects the account balance.
    // It can only be changed through public methods like deposit().
    // This way nobody can do: account.balance = 999999; directly.
    double balance;

    // COMPOSITION: a BankAccount CONTAINS many Transaction objects.
    // Each account keeps its own history.
    vector<Transaction> transactions;

public:
    // Constructor: creates an account with a number, name and starting balance.
    BankAccount(int accountNumber, string accountHolderName, double balance);

    // Getters: safe way to READ private data.
    int getAccountNumber();
    string getAccountHolderName();
    double getBalance();

    // Returns all transactions (needed only for saving to file).
    vector<Transaction> getTransactions();

    // Adds money to the balance and records a "Deposit" transaction.
    void deposit(double amount);

    // Removes money if possible and records a "Withdrawal" transaction.
    // Returns true if withdrawal worked, false if it failed.
    bool withdraw(double amount);

    // Adds any transaction to the history list.
    // Used for "Initial Deposit" and for loading history from file.
    void addTransaction(string type, double amount, string description);

    // Special helpers for transfers so history shows "Transfer"
    // instead of a normal deposit/withdrawal.
    // transferOut: removes money from THIS account (sender side).
    bool transferOut(double amount, int toAccountNumber);
    // transferIn: adds money to THIS account (receiver side).
    void transferIn(double amount, int fromAccountNumber);

    // Display helpers.
    void displayAccountDetails();
    void displayTransactionHistory();
};

#endif
