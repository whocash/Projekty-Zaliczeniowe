#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
// User class to represent bank customers
class User {
private:
    std::string username;
    std::string password;
    double accountBalance;
    std::vector<std::string> transactionHistory;

public:
    User(const std::string& uname, const std::string& pwd, double balance)
        : username(uname), password(pwd), accountBalance(balance) {}

    const std::string& getUsername() const {
        return username;
    }

    double getAccountBalance() const {
        return accountBalance;
    }

    const std::vector<std::string>& getTransactionHistory() const {
        return transactionHistory;
    }

    bool authenticate(const std::string& pwd) const {
        return password == pwd;
    }

    void deposit(double amount) {
        accountBalance += amount;
        transactionHistory.push_back("Deposit: +" + std::to_string(amount));
    }

    bool withdraw(double amount) {
        if (amount > accountBalance) {
            std::cout << "Insufficient funds!\n";
            return false;
        } else {
            accountBalance -= amount;
            transactionHistory.push_back("Withdrawal: -" + std::to_string(amount));
            return true;
        }
    }
};
void loadingAnimation() {
    const char spinner[] = "|/-\\";  // Characters for the spinner animation
    constexpr int numFrames = 4;

    std::cout << "Loading ";

    for (int i = 0; i < 20; ++i) {
        std::cout << spinner[i % numFrames] << " ";
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::cout << "\b\b";  // Move the cursor back two positions
    }

    std::cout << "Done!\n";
}


std::string generateRandomTransaction() {
    static const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int length = rand() % 10 + 5;

    std::string transaction;
    for (int i = 0; i < length; ++i) {
        transaction += charset[rand() % (sizeof(charset) - 1)];
    }

    return transaction;
}
struct Transaction {
    std::string description;
    double amount;
};

// Function to generate a list of random transactions
std::vector<Transaction> generateRandomTransactions(int numTransactions) {
    std::vector<std::string> descriptions = {
        "Online Purchase",
        "ATM Withdrawal",
        "Grocery Shopping",
        "Restaurant Bill",
        "Utilities Payment",
        "Gas Station",
        "E-commerce Order",
        "Entertainment",
        "Clothing Purchase",
        "Coffee Shop",
    };

    std::vector<Transaction> transactions;


    std::srand(static_cast<unsigned>(std::time(0)));

    for (int i = 0; i < numTransactions; ++i) {
        // Get a random description
        std::string randomDescription = descriptions[std::rand() % descriptions.size()];

        // Generate a random transaction amount
        double randomAmount = static_cast<double>(std::rand() % 1000) / 10.0; // Random amount between 0.0 and 100.0

        // Create a Transaction object and add it to the list
        Transaction transaction{randomDescription, randomAmount};
        transactions.push_back(transaction);
    }

    return transactions;
}
// Function to interact with the user
void userInteraction(User& user) {
    int choice;

    do {
        std::cout << "\n1. Display Account Information\n";
        std::cout << "2. Make a Deposit\n";
        std::cout << "3. Make a Withdrawal\n";
        std::cout << "4. Check History\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::system("cls");
                std::cout << "\nAccount Information:\n";
                std::cout << "Username: " << user.getUsername() << "\n";
                std::cout << "Balance: $" << user.getAccountBalance() << "\n";

                break;

            case 2:
                double depositAmount;
                std::cout << "\nEnter deposit amount: $";
                std::cin >> depositAmount;
                user.deposit(depositAmount);
                 loadingAnimation();

                std::cout << "Deposit completed.\n";
                 std::this_thread::sleep_for(std::chrono::milliseconds(1000));
 std::system("cls");
                break;

            case 3:
                double withdrawalAmount;
                std::cout << "\nEnter withdrawal amount: $";
                std::cin >> withdrawalAmount;
                if (user.withdraw(withdrawalAmount)) {
                         loadingAnimation();

                    std::cout << "Withdrawal completed.\n";
                     std::this_thread::sleep_for(std::chrono::milliseconds(1000));
 std::system("cls");
                }
                break;

            case 4:{
                std::system("cls");
                 int numTransactions = 5;
          for (const auto& transaction : user.getTransactionHistory()) {
                    std::cout << transaction << "\n";
                }
    std::vector<Transaction> randomTransactions = generateRandomTransactions(numTransactions);
    for (const auto& transaction : randomTransactions) {
        std::cout << transaction.description << "  -" << transaction.amount << "\n";

}} break;
                case 5:
                    {
                std::cout << "Exiting program.\n";}
                break;

            default:
                std::cout << "Invalid choice. Please try again.\n";
                 std::this_thread::sleep_for(std::chrono::milliseconds(1000));
 std::system("cls");
        }
    } while (choice != 5);
}

int main() {

    srand(static_cast<unsigned>(time(0)));


    User user("StudentSan", "password123", rand() % 5000 + 1000); // Random balance between $1000 and $6000


    std::string inputPassword;
    std::cout << "Enter password to log in: ";
    std::cin >> inputPassword;
     std::system("cls");
 loadingAnimation();
 std::this_thread::sleep_for(std::chrono::milliseconds(1000));
 std::system("cls");
    if (user.authenticate(inputPassword)) {
        std::cout << "Login successful. Welcome, " << user.getUsername() << "!\n";


        for (int i = 0; i < 3; ++i) {
            if (rand() % 2 == 0) {
                double amount = static_cast<double>(rand() % 500 + 100); // Random amount between $100 and $600
                user.deposit(amount);
            } else {
                double amount = static_cast<double>(rand() % 300 + 50); // Random amount between $50 and $350
                user.withdraw(amount);
            }
        }


        userInteraction(user);

    } else {
        std::cout << "Login failed. Incorrect password.\n";
    }

    return 0;
}
