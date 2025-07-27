#include <bits/stdc++.h>
using namespace std;

// Transaction class
class Transaction {
public:
    string type;   // Deposit, Withdrawal, Transfer
    double amount;
    string date;

    Transaction(string t, double amt) {
        type = t;
        amount = amt;

        // Get current date/time
        time_t now = time(0);
        date = ctime(&now);
        date.pop_back(); // remove newline
    }

    void displayTransaction() {
        cout << date << " | " << type << " | Amount: $" << amount << endl;
    }
};

// Account class
class Account {
private:
    int accountNumber;
    double balance;
    vector<Transaction> transactions;

public:
    Account(int accNo) {
        accountNumber = accNo;
        balance = 0.0;
    }

    int getAccountNumber() {
        return accountNumber;
    }

    double getBalance() {
        return balance;
    }

    void deposit(double amount) {
        balance += amount;
        transactions.push_back(Transaction("Deposit", amount));
        cout << "Deposit successful. New balance: $" << balance << endl;
    }

    void withdraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
            transactions.push_back(Transaction("Withdrawal", amount));
            cout << "Withdrawal successful. New balance: $" << balance << endl;
        } else {
            cout << "Insufficient balance!" << endl;
        }
    }

    void transfer(Account &receiver, double amount) {
        if (amount <= balance) {
            balance -= amount;
            receiver.balance += amount;
            transactions.push_back(Transaction("Transfer Sent", amount));
            receiver.transactions.push_back(Transaction("Transfer Received", amount));
            cout << "Transfer successful. Your new balance: $" << balance << endl;
        } else {
            cout << "Insufficient balance for transfer!" << endl;
        }
    }

    void displayAccountInfo() {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Current Balance: $" << balance << endl;
        cout << "Transaction History:" << endl;
        if (transactions.empty()) {
            cout << "No transactions yet." << endl;
        } else {
            for (auto &t : transactions) {
                t.displayTransaction();
            }
        }
    }
};

// Customer class
class Customer {
private:
    string name;
    int customerID;
    Account account;

public:
    Customer(string n, int id, int accNo) : account(accNo) {
        name = n;
        customerID = id;
    }

    int getCustomerID() {
        return customerID;
    }

    Account& getAccount() {
        return account;
    }

    void displayCustomerInfo() {
        cout << "\n--- Customer Information ---" << endl;
        cout << "Customer Name: " << name << endl;
        cout << "Customer ID: " << customerID << endl;
        account.displayAccountInfo();
    }
};

// Find customer by ID
Customer* findCustomerByID(vector<Customer> &customers, int id) {
    for (auto &c : customers) {
        if (c.getCustomerID() == id) {
            return &c;
        }
    }
    return nullptr;
}

// Main Program
int main() {
    vector<Customer> customers;
    int choice, customerID, accountNumber;
    string name;

    cout << "=== Welcome to Simple Banking System ===" << endl;

    do {
        cout << "\nMenu:\n";
        cout << "1. Create New Customer\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Transfer Funds\n";
        cout << "5. View Account Information\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter Customer Name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter Customer ID: ";
            cin >> customerID;
            cout << "Enter Account Number: ";
            cin >> accountNumber;
            customers.push_back(Customer(name, customerID, accountNumber));
            cout << "Customer account created successfully!\n";
            break;

        case 2:
            cout << "Enter Customer ID for Deposit: ";
            cin >> customerID;
            if (Customer *cust = findCustomerByID(customers, customerID)) {
                double amt;
                cout << "Enter amount to deposit: ";
                cin >> amt;
                cust->getAccount().deposit(amt);
            } else {
                cout << "Customer not found!" << endl;
            }
            break;

        case 3:
            cout << "Enter Customer ID for Withdrawal: ";
            cin >> customerID;
            if (Customer *cust = findCustomerByID(customers, customerID)) {
                double amt;
                cout << "Enter amount to withdraw: ";
                cin >> amt;
                cust->getAccount().withdraw(amt);
            } else {
                cout << "Customer not found!" << endl;
            }
            break;

        case 4:
            int receiverID;
            cout << "Enter Sender Customer ID: ";
            cin >> customerID;
            cout << "Enter Receiver Customer ID: ";
            cin >> receiverID;
            if (Customer *sender = findCustomerByID(customers, customerID)) {
                if (Customer *receiver = findCustomerByID(customers, receiverID)) {
                    double amt;
                    cout << "Enter amount to transfer: ";
                    cin >> amt;
                    sender->getAccount().transfer(receiver->getAccount(), amt);
                } else {
                    cout << "Receiver not found!" << endl;
                }
            } else {
                cout << "Sender not found!" << endl;
            }
            break;

        case 5:
            cout << "Enter Customer ID to view info: ";
            cin >> customerID;
            if (Customer *cust = findCustomerByID(customers, customerID)) {
                cust->displayCustomerInfo();
            } else {
                cout << "Customer not found!" << endl;
            }
            break;

        case 6:
            cout << "Exiting... Thank you for using our system!" << endl;
            break;

        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 6);

    return 0;
}
