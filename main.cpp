#include "BankSystem.h"

// Program entry point.
// It only creates a BankSystem object and starts it.
// All real work happens inside BankSystem::run().
int main()
{
    BankSystem bank;
    bank.run();
    return 0;
}
