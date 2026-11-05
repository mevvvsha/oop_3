#pragma once

#include <iostream>
#include <string>
#include <vector>

// Клас Transaction — зберігає інформацію про транзакцію.
class Transaction {
private:
    const int id;
    const std::string& currency;
    std::string date;
    double amount;
    std::string type;

    static int transactionCount;

public:
    // Конструктор без параметрів.
    Transaction();

    // Конструктор з параметрами.
    Transaction(const std::string& date, double amount,
        const std::string& type);

    // Конструктор копіювання.
    Transaction(const Transaction& other);

    void display() const;
    double getAmount() const;

    // Статичний метод.
    static int getTransactionCount();
};


// Клас CreditCard — інформація про кредитну картку.
class CreditCard {
private:
    std::string cardNumber;
    double creditLimit;
    bool blocked;

public:
    CreditCard();
    CreditCard(const std::string& number, double limit);
    CreditCard(const CreditCard& other);

    void block();
    void unblock();
    bool isBlocked() const;
    double getCreditLimit() const;
    void setCreditLimit(double limit);
    void display() const;
};


// Клас Client — інформація та дії клієнта.
class Client {
private:
    std::string name;
    std::string accountNumber;
    double balance;
    CreditCard card;
    std::vector<Transaction> history;
    bool accountActive;
    double requestedLimit;

public:
    Client();
    Client(const std::string& name,
        const std::string& accountNumber,
        double balance,
        const CreditCard& card);

    Client(const Client& other);

    void payOrder(double amount, const std::string& date);
    void transfer(double amount, const std::string& date);
    void blockCard();
    void cancelAccount();

    void requestCreditLimit(double newLimit);
    void addTransaction(const Transaction& transaction);

    void displayHistory() const;
    void displayInfo() const;

    double getBalance() const;
    double getCreditLimit() const;
    double getRequestedLimit() const;

    bool isCardBlocked() const;
    bool isAccountActive() const;

    void setBalance(double newBalance);

    // Статичне поле та статичний метод.
    static int clientCount;
    static int getClientCount();
};


// Клас Administrator — дії адміністратора.
class Administrator {
private:
    std::string name;

public:
    Administrator();
    Administrator(const std::string& name);
    Administrator(const Administrator& other);

    void viewHistory(const Client& client) const;
    void blockCardForCreditOverrun(Client& client) const;
    void approveCreditLimit(Client& client) const;
    void rejectCreditLimit(Client& client) const;
};


// Клас PaymentPlan — оплата частинами.
class PaymentPlan {
private:
    double totalAmount;
    int numberOfPayments;
    std::vector<double> installments;
    std::vector<std::string> dueDates;

public:
    PaymentPlan();
    PaymentPlan(double amount, int payments);
    PaymentPlan(const PaymentPlan& other);

    void createPlan();
    void displayPlan() const;
};


// Вільна функція, яка приймає об'єкт класу Client.
void calculateAvailableFunds(const Client& client);

// Функція, яка повертає об'єкт класу Client.
Client createNewClient();