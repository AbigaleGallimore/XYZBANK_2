#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// Base Class: Account 
class Account {
// UML specifies #balance: double, 
protected:
    double balance;

public:
    // Constructor 
    Account(double init_balance) {
        // Validation logic 
        if (init_balance >= 1000.00) {
            balance = init_balance;
        } else {
            balance = 0.0;
            cout << "Account Warning: Initial balance invalid (set to $0.00)." << endl;
        }
    }

    // Default constructor 
    Account() : balance(0.0) {}

    void setBalance(double b) { balance = b; }

    double getBalance() const { return balance; }

    bool deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            return true;
        }
        return false;
    }

    // withdraw (Debit) function - Declared virtual for overriding in ChequingAccount 
    // Returns bool 
    virtual bool withdraw(double amount) {
        if (amount > balance || amount <= 0) {
            cout << "Debit amount exceeded account balance or is invalid." << endl;
            return false;
        }
        balance -= amount;
        return true;
    }

    // Virtual destructor for proper cleanup in an inheritance hierarchy
    virtual ~Account() {}
};

// Derived Class 1: SavingsAccount 
class SavingsAccount : public Account {
private:
    // Data member for interest rate 
    float interestRate; // Stored as a decimal (e.g., 0.05 for 5%)

public:
    // Constructor inheriting from Account and taking rate parameter 
    SavingsAccount(double init_balance, float rate)
        // Call base class constructor
        : Account(init_balance), interestRate(rate) {
         
    }

    // Member function to calculate interest
    double CalculateInterest() {
        // Determine amount by multiplying the interest rate by the account balance 
        return balance * interestRate;
    }
};

// Derived Class 2: ChequingAccount 
class ChequingAccount : public Account {
private:
    // Data member for transaction fee 
    double transactionFee;

public:
    // Constructor inheriting from Account and taking fee parameter 
    ChequingAccount(double init_balance, double fee)
        // Call base class constructor
        : Account(init_balance), transactionFee(fee) {}

    // Redefine/Override the withdraw function 
    bool withdraw(double amount) override {
        // Calculate required total deduction (amount + fee)
        double total_deduction = amount + transactionFee;

        // Check if the total deduction exceeds the balance ) 
        if (total_deduction > balance || amount <= 0) {
            cout << "Chequing Debit Failed: Insufficient funds or invalid amount." << endl;
            // No fee is charged if the transaction is unsuccessful
            return false;
        }

        // Transaction is successful: subtract the total deduction (amount + fee) 
        balance -= total_deduction;
        cout << "Chequing Debit Successful. Fee charged: $" 
             << fixed << setprecision(2) << transactionFee << "." << endl;
        return true;
    }
};


// Test Program (main function)
int main() {
    // Set output to fixed-point notation with 2 decimal places for currency
    cout << fixed << setprecision(2);
    cout << "--- Inheritance Test Program ---" << endl;
    
    // --- Test SavingsAccount --- 
    cout << "\n*** Testing SavingsAccount ***" << endl;
    
    // Create SavingsAccount object 
    SavingsAccount mySavings(2000.00, 0.045);
    cout << "Initial Savings Balance: $" << mySavings.getBalance() << endl;

    // Test Deposit 
    mySavings.deposit(500.00);
    cout << "Balance after $500 Deposit: $" << mySavings.getBalance() << endl;

    // Calculate Interest [cite: 62]
    double earnedInterest = mySavings.CalculateInterest();
    cout << "Calculated Interest Earned: $" << earnedInterest << endl;

    // Add interest to the SavingsAccount object 
    mySavings.deposit(earnedInterest);
    cout << "Final Savings Balance (after interest added): $" << mySavings.getBalance() << endl;
    
    // Test Withdrawal 
    mySavings.withdraw(100.00);
    cout << "Balance after $100 Withdraw: $" << mySavings.getBalance() << endl;


    // --- Test ChequingAccount --- 
    cout << "\n*** Testing ChequingAccount ***" << endl;
    
    // Create ChequingAccount object 
    ChequingAccount myChequing(1000.00, 5.00);
    cout << "Initial Chequing Balance (Fee: $5.00): $" << myChequing.getBalance() << endl;

    // Test Successful Withdrawal
    myChequing.withdraw(50.00); // 50.00 + 5.00 fee = 55.00 deducted
    cout << "Balance after $50 Debit: $" << myChequing.getBalance() << endl;
    
    // Test Withdrawal Failure
    myChequing.withdraw(1000.00); // Current balance is 945.00. 1000 + 5 = 1005.00 required.
    cout << "Balance after Failed Debit Attempt: $" << myChequing.getBalance() << endl; // Should remain 945.00

    cout << "\n--- Test Program Complete ---" << endl;
    
    return 0;
}