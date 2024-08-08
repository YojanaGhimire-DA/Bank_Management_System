#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

// Account class
class Account {
private:
    int accountNumber;
    string accountHolderName;
    double balance;

public:
    Account(int accNo, string name, double initialBalance) {
        accountNumber = accNo;
        accountHolderName = name;
        balance = initialBalance;
    }

    int getAccountNumber() const {
        return accountNumber;
    }

    string getAccountHolderName() const {
        return accountHolderName;
    }

    double getBalance() const {
        return balance;
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposited: $" << amount << endl;
        } else {
            cout << "Invalid deposit amount!" << endl;
        }
    }

    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Withdrawn: $" << amount << endl;
        } else {
            cout << "Invalid withdrawal amount or insufficient balance!" << endl;
        }
    }

    void displayAccountDetails() const {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Account Holder: " << accountHolderName << endl;
        cout << "Balance: $" << balance << endl;
    }
};

// Bank class
class Bank {
private:
    vector<Account> accounts;
    int nextAccountNumber;

public:
    Bank() : nextAccountNumber(1) {}

    void createAccount(string name, double initialBalance) {
        if (initialBalance < 0) {
            cout << "Initial balance cannot be negative!" << endl;
            return;
        }
        Account newAccount(nextAccountNumber++, name, initialBalance);
        accounts.push_back(newAccount);
        cout << "Account created successfully!" << endl;
    }

    Account* findAccount(int accountNumber) {
        for (auto& account : accounts) {
            if (account.getAccountNumber() == accountNumber) {
                return &account;
            }
        }
        return nullptr;
    }

    const Account* findAccount(int accountNumber) const {  // Const version of findAccount
        for (const auto& account : accounts) {
            if (account.getAccountNumber() == accountNumber) {
                return &account;
            }
        }
        return nullptr;
    }

    void depositToAccount(int accountNumber, double amount) {
        Account* account = findAccount(accountNumber);
        if (account != nullptr) {
            account->deposit(amount);
        } else {
            cout << "Account not found!" << endl;
        }
    }

    void withdrawFromAccount(int accountNumber, double amount) {
        Account* account = findAccount(accountNumber);
        if (account != nullptr) {
            account->withdraw(amount);
        } else {
            cout << "Account not found!" << endl;
        }
    }

    void displayAccountDetails(int accountNumber) const {
        const Account* account = findAccount(accountNumber);
        if (account != nullptr) {
            account->displayAccountDetails();
        } else {
            cout << "Account not found!" << endl;
        }
    }
};

// Main function
int main() {
    Bank bank;
    int choice;
    string name;
    double amount;
    int accountNumber;

    do {
        cout << "\n--- Bank Management System ---" << endl;
        cout << "1. Create Account" << endl;
        cout << "2. Deposit" << endl;
        cout << "3. Withdraw" << endl;
        cout << "4. Display Account Details" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter account holder's name: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
                getline(cin, name);
                cout << "Enter initial balance: ";
                cin >> amount;
                bank.createAccount(name, amount);
                break;
            case 2:
                cout << "Enter account number: ";
                cin >> accountNumber;
                cout << "Enter amount to deposit: ";
                cin >> amount;
                bank.depositToAccount(accountNumber, amount);
                break;
            case 3:
                cout << "Enter account number: ";
                cin >> accountNumber;
                cout << "Enter amount to withdraw: ";
                cin >> amount;
                bank.withdrawFromAccount(accountNumber, amount);
                break;
            case 4:
                cout << "Enter account number: ";
                cin >> accountNumber;
                bank.displayAccountDetails(accountNumber);
                break;
            case 5:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
        }
    } while (choice != 5);

    return 0;
}
