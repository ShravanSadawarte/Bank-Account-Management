#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
using namespace std;

// Transaction class represents ONE banking transaction.
// Example: Deposit of Rs.5000 with description "Initial Deposit".
// This is a simple data class (it only stores data and lets us read it).
class Transaction
{
private:
    string type;        // Example: "Deposit", "Withdrawal", "Transfer"
    double amount;      // Example: 5000
    string description; // Example: "Initial Deposit", "Cash Deposit"

public:
    // Constructor: creates a Transaction object with given values.
    Transaction(string type, double amount, string description);

    // Getters: allow other classes to READ private data safely.
    string getType();
    double getAmount();
    string getDescription();
};

#endif
