#include "Transaction.h"

// Constructor uses an initializer list (the part after ':').
// It simply copies the given values into our private variables.
Transaction::Transaction(string type, double amount, string description)
    : type(type), amount(amount), description(description)
{
    // Nothing else to do. Object is ready after this.
}

string Transaction::getType()
{
    return type;
}

double Transaction::getAmount()
{
    return amount;
}

string Transaction::getDescription()
{
    return description;
}
