#ifndef BANKSYSTEM_H
#define BANKSYSTEM_H

#include <vector>
#include "BankAccount.h"
using namespace std;

// BankSystem manages MANY BankAccount objects.
// It handles the menu, user input, searching, and file saving/loading.
class BankSystem
{
private:
    // COMPOSITION: BankSystem CONTAINS many BankAccount objects.
    vector<BankAccount> accounts;

    // Helper: find an account by number.
    // Returns a pointer to the account, or NULL if not found.
    // (We use a simple loop — no complicated algorithm.)
    BankAccount* findAccount(int accountNumber);

    // Helper: show the main menu.
    void showMenu();

    // Helpers: load data when program starts, save when data changes.
    void loadFromFile();
    void saveToFile();

public:
    // Main menu actions (one method per menu option).
    void createAccount();
    void depositMoney();
    void withdrawMoney();
    void checkBalance();
    void displayAccount();
    void searchAccount();
    void displayAllAccounts();
    void transferMoney();
    void displayTransactions();

    // Starts the application (menu loop). Called from main().
    void run();
};

#endif
