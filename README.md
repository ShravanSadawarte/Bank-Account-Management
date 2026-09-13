# Bank Account Management System

A simple **console-based banking system in C++**, built to learn
**Object-Oriented Programming (OOP)** with a realistic example.

No GUI, no database, no external libraries.
Only C++, STL `vector`, and text files.

---

## Features

1. Create Account
2. Deposit Money
3. Withdraw Money
4. Check Balance
5. Display Account Details
6. Search Account (by account number)
7. Display All Accounts
8. Transfer Money between accounts
9. Transaction History per account
10. File persistence (`accounts.txt`, `transactions.txt`)

---

## OOP Concepts Used

### Classes
A class is a blueprint. This project has 3 classes:
- `BankAccount` — blueprint for one bank account.
- `Transaction` — blueprint for one transaction.
- `BankSystem` — blueprint for the whole banking app.

### Objects
An object is one real thing made from a class:
```cpp
BankAccount account1(101, "Shravan", 5000);
BankAccount account2(102, "Rahul", 8000);
```
Each object has its own number, name, balance, and history.

### Encapsulation
Important data is `private`:
```cpp
private:
    double balance;
```
Nobody can change it directly. It can only be changed
through public methods like `deposit()` and `withdraw()`.
This prevents mistakes like setting a negative balance by accident.

### Constructors
A constructor runs automatically when an object is created
and sets its starting values:
```cpp
BankAccount(int accountNumber, string accountHolderName, double balance);
Transaction(string type, double amount, string description);
```

### Abstraction
The user just calls:
```cpp
account.deposit(2000);
```
They do not need to know HOW the balance and history
are updated inside. The complexity is hidden.

### Composition
A `BankAccount` CONTAINS many `Transaction` objects:
```cpp
vector<Transaction> transactions;
```
And `BankSystem` CONTAINS many `BankAccount` objects:
```cpp
vector<BankAccount> accounts;
```
This "has-a" relationship is called composition.

> Inheritance is intentionally NOT used here.
> There is no natural parent/child relationship
> (a bank account is not a special kind of transaction),
> so forcing inheritance would only make learning harder.

---

## Technologies

```
C++
OOP (Classes, Objects, Encapsulation, Abstraction, Composition)
STL vector
File Handling (ifstream / ofstream)
```

---

## Project Structure

```
BankAccountSystem/
│
├── main.cpp            Program entry point, starts BankSystem
│
├── Transaction.h       Transaction class declaration
├── Transaction.cpp     Transaction method implementations
│
├── BankAccount.h       BankAccount class declaration
├── BankAccount.cpp     BankAccount method implementations
│
├── BankSystem.h        BankSystem class declaration
├── BankSystem.cpp      BankSystem implementation (menu + logic + files)
│
├── accounts.txt        Saved accounts (auto-created)
├── transactions.txt    Saved transactions (auto-created)
│
└── README.md           This file
```

File purposes:

```
Transaction.h  ->  WHAT a Transaction is (variables + method names)
Transaction.cpp -> HOW Transaction methods work

BankAccount.h  ->  WHAT a BankAccount is
BankAccount.cpp -> HOW deposit/withdraw/display work

BankSystem.h   ->  WHAT the BankSystem can do
BankSystem.cpp -> HOW menu, search, transfer, files work

main.cpp       -> Creates BankSystem object and calls run()
```

Data file formats (simple text, `|` separates fields):

```
accounts.txt:      101|Shravan|5500
transactions.txt:  101|Deposit|5000|Initial Deposit
```

---

## How to Run

### Linux / macOS

```bash
g++ main.cpp BankAccount.cpp Transaction.cpp BankSystem.cpp -o bank
./bank
```

### Windows (MinGW g++)

```bash
g++ main.cpp BankAccount.cpp Transaction.cpp BankSystem.cpp -o bank.exe
bank.exe
```

### Windows (Visual Studio Developer Prompt)

```bash
cl main.cpp BankAccount.cpp Transaction.cpp BankSystem.cpp
main.exe
```

> Note: amounts are shown as `Rs.` instead of `₹`
> so the program works on every terminal without font/encoding issues.

---

## Sample Usage

```
Enter account number: 101
Enter account holder name: Shravan
Enter initial deposit: 5000
Account created successfully.

Enter account number: 101
Enter amount: 2000
Rs.2000 deposited successfully.
Current balance: Rs.7000

Enter account number: 101
Enter amount: 1500
Rs.1500 withdrawn successfully.
Current balance: Rs.5500

Enter sender account number: 101
Enter receiver account number: 102
Enter amount: 2000
Transfer successful.
Sender Balance   : Rs.3500
Receiver Balance : Rs.10000
```

---

## How to Study This Project Class by Class

1. Read `Transaction.h` + `Transaction.cpp` first (smallest class).
2. Then read `BankAccount.h` + `BankAccount.cpp`
   (how one account works: balance + history).
3. Then read `BankSystem.h` + `BankSystem.cpp`
   (how many accounts are managed, menu, files).
4. Finally read `main.cpp` (only 3 lines of real logic).

---

## Possible Improvements (after you understand this version)

- Add Savings / Current account types (to learn inheritance).
- Add timestamps to transactions.
- Hide PIN/password input.
- Replace `double` with integer paise to avoid rounding issues.
- Validate names (no digits) and larger input ranges.
