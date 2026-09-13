#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "BankSystem.h"

// Simple search through the vector.
// Returns pointer to the found account so we can modify it directly.
BankAccount* BankSystem::findAccount(int accountNumber)
{
    for (int i = 0; i < (int)accounts.size(); i++)
    {
        if (accounts[i].getAccountNumber() == accountNumber)
        {
            return &accounts[i];
        }
    }
    return NULL;
}

void BankSystem::showMenu()
{
    cout << endl;
    cout << "========================================" << endl;
    cout << "          BANK ACCOUNT SYSTEM" << endl;
    cout << "========================================" << endl;
    cout << endl;
    cout << "1. Create Account" << endl;
    cout << "2. Deposit Money" << endl;
    cout << "3. Withdraw Money" << endl;
    cout << "4. Check Balance" << endl;
    cout << "5. Display Account Details" << endl;
    cout << "6. Search Account" << endl;
    cout << "7. Display All Accounts" << endl;
    cout << "8. Transfer Money" << endl;
    cout << "9. Transaction History" << endl;
    cout << "10. Exit" << endl;
    cout << endl;
    cout << "Enter your choice: ";
}

void BankSystem::createAccount()
{
    int accountNumber;
    string name;
    double initialDeposit;

    cout << "Enter account number: ";
    cin >> accountNumber;

    if (cin.fail() || accountNumber <= 0)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid account number." << endl;
        return;
    }

    // Account number must be unique.
    if (findAccount(accountNumber) != NULL)
    {
        cout << "Account number already exists." << endl;
        cin.ignore(1000, '\n');
        return;
    }

    cin.ignore(1000, '\n'); // clear newline before getline
    cout << "Enter account holder name: ";
    getline(cin, name);

    if (name == "")
    {
        cout << "Account holder name cannot be empty." << endl;
        return;
    }

    cout << "Enter initial deposit: ";
    cin >> initialDeposit;

    if (cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid amount." << endl;
        return;
    }

    if (initialDeposit < 0)
    {
        cout << "Initial deposit cannot be negative." << endl;
        return;
    }

    // Create the OBJECT and store it in our vector.
    BankAccount newAccount(accountNumber, name, initialDeposit);

    // Record the first transaction only if money was deposited.
    if (initialDeposit > 0)
    {
        newAccount.addTransaction("Deposit", initialDeposit, "Initial Deposit");
    }

    accounts.push_back(newAccount);
    saveToFile();

    cout << "Account created successfully." << endl;
}

void BankSystem::depositMoney()
{
    int accountNumber;
    double amount;

    cout << "Enter account number: ";
    cin >> accountNumber;

    if (cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid account number." << endl;
        return;
    }

    BankAccount* account = findAccount(accountNumber);
    if (account == NULL)
    {
        cout << "Account not found." << endl;
        return;
    }

    cout << "Enter amount: ";
    cin >> amount;

    if (cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid amount." << endl;
        return;
    }

    if (amount <= 0)
    {
        cout << "Amount must be greater than 0." << endl;
        return;
    }

    account->deposit(amount);
    saveToFile();

    cout << "Rs." << amount << " deposited successfully." << endl;
    cout << "Current balance: Rs." << account->getBalance() << endl;
}

void BankSystem::withdrawMoney()
{
    int accountNumber;
    double amount;

    cout << "Enter account number: ";
    cin >> accountNumber;

    if (cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid account number." << endl;
        return;
    }

    BankAccount* account = findAccount(accountNumber);
    if (account == NULL)
    {
        cout << "Account not found." << endl;
        return;
    }

    cout << "Enter amount: ";
    cin >> amount;

    if (cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid amount." << endl;
        return;
    }

    if (amount <= 0)
    {
        cout << "Amount must be greater than 0." << endl;
        return;
    }

    bool success = account->withdraw(amount);
    if (success)
    {
        saveToFile();
        cout << "Rs." << amount << " withdrawn successfully." << endl;
        cout << "Current balance: Rs." << account->getBalance() << endl;
    }
    // If not successful, withdraw() already printed "Insufficient balance."
}

void BankSystem::checkBalance()
{
    int accountNumber;
    cout << "Enter account number: ";
    cin >> accountNumber;

    if (cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid account number." << endl;
        return;
    }

    BankAccount* account = findAccount(accountNumber);
    if (account == NULL)
    {
        cout << "Account not found." << endl;
        return;
    }

    cout << "Current Balance: Rs." << account->getBalance() << endl;
}

void BankSystem::displayAccount()
{
    int accountNumber;
    cout << "Enter account number: ";
    cin >> accountNumber;

    if (cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid account number." << endl;
        return;
    }

    BankAccount* account = findAccount(accountNumber);
    if (account == NULL)
    {
        cout << "Account not found." << endl;
        return;
    }

    account->displayAccountDetails();
}

void BankSystem::searchAccount()
{
    // Searching is the same as displaying: find by account number.
    int accountNumber;
    cout << "Enter account number to search: ";
    cin >> accountNumber;

    if (cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid account number." << endl;
        return;
    }

    BankAccount* account = findAccount(accountNumber);
    if (account == NULL)
    {
        cout << "Account not found." << endl;
        return;
    }

    account->displayAccountDetails();
}

void BankSystem::displayAllAccounts()
{
    if (accounts.size() == 0)
    {
        cout << "No accounts found." << endl;
        return;
    }

    cout << "========================================" << endl;
    cout << "             ALL ACCOUNTS" << endl;
    cout << "========================================" << endl;
    cout << endl;

    cout << left << setw(15) << "Account No."
         << setw(20) << "Holder Name"
         << "Balance" << endl;

    for (int i = 0; i < (int)accounts.size(); i++)
    {
        cout << left << setw(15) << accounts[i].getAccountNumber()
             << setw(20) << accounts[i].getAccountHolderName()
             << "Rs." << accounts[i].getBalance() << endl;
    }

    cout << endl;
    cout << "========================================" << endl;
}

void BankSystem::transferMoney()
{
    int senderNumber, receiverNumber;
    double amount;

    cout << "Enter sender account number: ";
    cin >> senderNumber;

    if (cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid account number." << endl;
        return;
    }

    cout << "Enter receiver account number: ";
    cin >> receiverNumber;

    if (cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid account number." << endl;
        return;
    }

    if (senderNumber == receiverNumber)
    {
        cout << "Sender and receiver accounts must be different." << endl;
        return;
    }

    BankAccount* sender = findAccount(senderNumber);
    BankAccount* receiver = findAccount(receiverNumber);

    if (sender == NULL || receiver == NULL)
    {
        cout << "Account not found." << endl;
        return;
    }

    cout << "Enter amount: ";
    cin >> amount;

    if (cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid amount." << endl;
        return;
    }

    if (amount <= 0)
    {
        cout << "Amount must be greater than 0." << endl;
        return;
    }

    // First take money from sender (fails if insufficient balance).
    bool success = sender->transferOut(amount, receiverNumber);
    if (!success)
    {
        return;
    }

    // Then give money to receiver.
    receiver->transferIn(amount, senderNumber);
    saveToFile();

    cout << "Transfer successful." << endl;
    cout << "Sender Balance   : Rs." << sender->getBalance() << endl;
    cout << "Receiver Balance : Rs." << receiver->getBalance() << endl;
}

void BankSystem::displayTransactions()
{
    int accountNumber;
    cout << "Enter account number: ";
    cin >> accountNumber;

    if (cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid account number." << endl;
        return;
    }

    BankAccount* account = findAccount(accountNumber);
    if (account == NULL)
    {
        cout << "Account not found." << endl;
        return;
    }

    account->displayTransactionHistory();
}

// Save format (simple text, '|' separates fields):
//   accounts.txt:     101|Shravan|5500
//   transactions.txt: 101|Deposit|5000|Initial Deposit
void BankSystem::saveToFile()
{
    ofstream accFile("accounts.txt");
    ofstream transFile("transactions.txt");

    for (int i = 0; i < (int)accounts.size(); i++)
    {
        accFile << accounts[i].getAccountNumber() << "|"
                << accounts[i].getAccountHolderName() << "|"
                << accounts[i].getBalance() << endl;

        vector<Transaction> history = accounts[i].getTransactions();
        for (int j = 0; j < (int)history.size(); j++)
        {
            transFile << accounts[i].getAccountNumber() << "|"
                      << history[j].getType() << "|"
                      << history[j].getAmount() << "|"
                      << history[j].getDescription() << endl;
        }
    }

    accFile.close();
    transFile.close();
}

// Helper: split one line like "101|Deposit|5000|Initial Deposit"
// into separate pieces using '|' as separator.
static bool splitLine(string line, string parts[], int expectedParts)
{
    int found = 0;
    string current = "";

    for (int i = 0; i < (int)line.length(); i++)
    {
        if (line[i] == '|')
        {
            if (found >= expectedParts - 1)
            {
                return false;
            }
            parts[found] = current;
            found++;
            current = "";
        }
        else
        {
            current = current + line[i];
        }
    }
    parts[found] = current;
    found++;

    return (found == expectedParts);
}

void BankSystem::loadFromFile()
{
    cout << "Loading account data..." << endl;

    ifstream accFile("accounts.txt");
    if (!accFile.is_open())
    {
        // No file yet = first run. That is normal, not an error.
        return;
    }

    string line;
    while (getline(accFile, line))
    {
        if (line == "")
        {
            continue;
        }

        string parts[3];
        if (!splitLine(line, parts, 3))
        {
            continue; // skip broken lines
        }

        int accNo = stoi(parts[0]);
        string name = parts[1];
        double bal = stod(parts[2]);

        BankAccount acc(accNo, name, bal);
        accounts.push_back(acc);
    }
    accFile.close();

    ifstream transFile("transactions.txt");
    if (!transFile.is_open())
    {
        return;
    }

    while (getline(transFile, line))
    {
        if (line == "")
        {
            continue;
        }

        string parts[4];
        if (!splitLine(line, parts, 4))
        {
            continue; // skip broken lines
        }

        int accNo = stoi(parts[0]);
        string type = parts[1];
        double amount = stod(parts[2]);
        string desc = parts[3];

        BankAccount* acc = findAccount(accNo);
        if (acc != NULL)
        {
            // addTransaction only adds history, it does NOT change balance.
            // Balance was already loaded from accounts.txt, so this is correct.
            acc->addTransaction(type, amount, desc);
        }
    }
    transFile.close();
}

void BankSystem::run()
{
    loadFromFile();

    int choice = 0;

    while (true)
    {
        showMenu();
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid choice. Please try again." << endl;
            continue;
        }

        if (choice == 1)
        {
            createAccount();
        }
        else if (choice == 2)
        {
            depositMoney();
        }
        else if (choice == 3)
        {
            withdrawMoney();
        }
        else if (choice == 4)
        {
            checkBalance();
        }
        else if (choice == 5)
        {
            displayAccount();
        }
        else if (choice == 6)
        {
            searchAccount();
        }
        else if (choice == 7)
        {
            displayAllAccounts();
        }
        else if (choice == 8)
        {
            transferMoney();
        }
        else if (choice == 9)
        {
            displayTransactions();
        }
        else if (choice == 10)
        {
            cout << "Saving account data..." << endl;
            saveToFile();
            cout << "Data saved successfully." << endl;
            cout << "Thank you for using Bank Account System." << endl;
            break;
        }
        else
        {
            cout << "Invalid choice. Please try again." << endl;
        }
    }
}
