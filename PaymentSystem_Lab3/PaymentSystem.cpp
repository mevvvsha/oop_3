#include "PaymentSystem.h"

using namespace std;

// Статична змінна для валюти.
static const string currencyName = "UAH";


// ================= TRANSACTION =================

// Ініціалізація статичного поля.
int Transaction::transactionCount = 0;

// Конструктор без параметрів.
Transaction::Transaction()
    : id(++transactionCount),
    currency(currencyName),
    date("Невідома дата"),
    amount(0),
    type("Невідомий тип") {
}

// Конструктор з параметрами.
Transaction::Transaction(const string& date,
    double amount,
    const string& type)
    : id(++transactionCount),
    currency(currencyName),
    date(date),
    amount(amount),
    type(type) {
}

// Конструктор копіювання.
Transaction::Transaction(const Transaction& other)
    : id(++transactionCount),
    currency(currencyName),
    date(other.date),
    amount(other.amount),
    type(other.type) {
}

// Виведення інформації про транзакцію.
void Transaction::display() const {
    cout << "ID: " << id << endl;
    cout << "Дата: " << date << endl;
    cout << "Сума: " << amount << " " << currency << endl;
    cout << "Тип: " << type << endl;
    cout << "------------------------" << endl;
}

double Transaction::getAmount() const {
    return amount;
}

// Статичний метод.
int Transaction::getTransactionCount() {
    return transactionCount;
}


// ================= CREDIT CARD =================

CreditCard::CreditCard()
    : cardNumber("0000000000000000"),
    creditLimit(0),
    blocked(false) {
}

CreditCard::CreditCard(const string& number, double limit)
    : cardNumber(number),
    creditLimit(limit),
    blocked(false) {
}

CreditCard::CreditCard(const CreditCard& other)
    : cardNumber(other.cardNumber),
    creditLimit(other.creditLimit),
    blocked(other.blocked) {
}

void CreditCard::block() {
    blocked = true;
    cout << "Кредитну картку заблоковано." << endl;
}

void CreditCard::unblock() {
    blocked = false;
    cout << "Кредитну картку розблоковано." << endl;
}

bool CreditCard::isBlocked() const {
    return blocked;
}

double CreditCard::getCreditLimit() const {
    return creditLimit;
}

void CreditCard::setCreditLimit(double limit) {
    creditLimit = limit;
}

void CreditCard::display() const {
    cout << "Номер картки: " << cardNumber << endl;
    cout << "Кредитний ліміт: " << creditLimit << " UAH" << endl;
    cout << "Статус: " << (blocked ? "Заблокована" : "Активна") << endl;
}


// ================= CLIENT =================

// Ініціалізація статичного поля.
int Client::clientCount = 0;

// Конструктор без параметрів.
Client::Client()
    : name("Невідомий клієнт"),
    accountNumber("000000"),
    balance(0),
    card(),
    accountActive(true),
    requestedLimit(0) {
    clientCount++;
}

// Конструктор з параметрами.
Client::Client(const string& name,
    const string& accountNumber,
    double balance,
    const CreditCard& card)
    : name(name),
    accountNumber(accountNumber),
    balance(balance),
    card(card),
    accountActive(true),
    requestedLimit(0) {
    clientCount++;
}

// Конструктор копіювання.
Client::Client(const Client& other)
    : name(other.name),
    accountNumber(other.accountNumber),
    balance(other.balance),
    card(other.card),
    history(other.history),
    accountActive(other.accountActive),
    requestedLimit(other.requestedLimit) {
    clientCount++;
}

// Оплата замовлення.
void Client::payOrder(double amount, const string& date) {
    if (!accountActive) {
        cout << "Рахунок неактивний!" << endl;
        return;
    }

    if (card.isBlocked()) {
        cout << "Картка заблокована!" << endl;
        return;
    }

    if (amount <= 0) {
        cout << "Некоректна сума платежу!" << endl;
        return;
    }

    double commission = amount * 0.02;
    double total = amount + commission;

    if (balance + card.getCreditLimit() < total) {
        cout << "Недостатньо коштів!" << endl;
        return;
    }

    balance -= total;

    history.push_back(Transaction(date, total, "Оплата замовлення"));

    cout << "Замовлення оплачено." << endl;
    cout << "Комісія: " << commission << " UAH" << endl;
}

// Переказ коштів на інший рахунок.
void Client::transfer(double amount, const string& date) {
    if (!accountActive || card.isBlocked()) {
        cout << "Операція неможлива!" << endl;
        return;
    }

    if (amount <= 0) {
        cout << "Некоректна сума переказу!" << endl;
        return;
    }

    double commission = amount * 0.01;
    double total = amount + commission;

    if (balance + card.getCreditLimit() < total) {
        cout << "Недостатньо коштів для переказу!" << endl;
        return;
    }

    balance -= total;

    history.push_back(Transaction(date, total, "Переказ коштів"));

    cout << "Переказ виконано." << endl;
    cout << "Комісія: " << commission << " UAH" << endl;
}

// Блокування картки клієнтом.
void Client::blockCard() {
    card.block();
}

// Скасування рахунку.
void Client::cancelAccount() {
    accountActive = false;
    cout << "Рахунок клієнта скасовано." << endl;
}

// Запит на зміну кредитного ліміту.
void Client::requestCreditLimit(double newLimit) {
    if (newLimit <= 0) {
        cout << "Некоректний кредитний ліміт!" << endl;
        return;
    }

    requestedLimit = newLimit;
    cout << "Запит на зміну кредитного ліміту надіслано." << endl;
}

// Додавання транзакції.
void Client::addTransaction(const Transaction& transaction) {
    history.push_back(transaction);
}

// Перегляд історії.
void Client::displayHistory() const {
    cout << "\nІСТОРІЯ ПЛАТЕЖІВ\n";

    if (history.empty()) {
        cout << "Історія платежів порожня." << endl;
        return;
    }

    for (const Transaction& transaction : history) {
        transaction.display();
    }
}

// Інформація про клієнта.
void Client::displayInfo() const {
    cout << "\nІНФОРМАЦІЯ ПРО КЛІЄНТА\n";
    cout << "Ім'я: " << name << endl;
    cout << "Номер рахунку: " << accountNumber << endl;
    cout << "Баланс: " << balance << " UAH" << endl;
    cout << "Рахунок: " << (accountActive ? "Активний" : "Скасований") << endl;

    card.display();
}

double Client::getBalance() const {
    return balance;
}

double Client::getCreditLimit() const {
    return card.getCreditLimit();
}

double Client::getRequestedLimit() const {
    return requestedLimit;
}

bool Client::isCardBlocked() const {
    return card.isBlocked();
}

bool Client::isAccountActive() const {
    return accountActive;
}

void Client::setBalance(double newBalance) {
    balance = newBalance;
}

// Статичний метод.
int Client::getClientCount() {
    return clientCount;
}


// ================= ADMINISTRATOR =================

Administrator::Administrator()
    : name("Адміністратор") {
}

Administrator::Administrator(const string& name)
    : name(name) {
}

Administrator::Administrator(const Administrator& other)
    : name(other.name) {
}

// Адміністратор переглядає історію.
void Administrator::viewHistory(const Client& client) const {
    cout << "\nАдміністратор " << name
        << " переглядає історію платежів." << endl;

    client.displayHistory();
}

// Блокування картки через перевищення кредиту.
void Administrator::blockCardForCreditOverrun(Client& client) const {
    if (client.getBalance() < -client.getCreditLimit()) {
        cout << "Перевищено кредитний ліміт!" << endl;
        client.blockCard();
    }
    else {
        cout << "Перевищення кредитного ліміту немає." << endl;
    }
}

// Підтвердження зміни кредитного ліміту.
void Administrator::approveCreditLimit(Client& client) const {
    if (client.getRequestedLimit() > 0) {
        client.displayInfo();

        cout << "Адміністратор " << name
            << " схвалив зміну кредитного ліміту." << endl;
    }
    else {
        cout << "Немає активного запиту." << endl;
    }
}

// Відхилення зміни кредитного ліміту.
void Administrator::rejectCreditLimit(Client& client) const {
    cout << "Адміністратор " << name
        << " відхилив запит на зміну кредитного ліміту." << endl;
}


// ================= PAYMENT PLAN =================

PaymentPlan::PaymentPlan()
    : totalAmount(0),
    numberOfPayments(0) {
}

PaymentPlan::PaymentPlan(double amount, int payments)
    : totalAmount(amount),
    numberOfPayments(payments) {
    createPlan();
}

PaymentPlan::PaymentPlan(const PaymentPlan& other)
    : totalAmount(other.totalAmount),
    numberOfPayments(other.numberOfPayments),
    installments(other.installments),
    dueDates(other.dueDates) {
}

// Створення графіка платежів.
void PaymentPlan::createPlan() {
    installments.clear();
    dueDates.clear();

    if (numberOfPayments <= 0 || totalAmount <= 0) {
        cout << "Неможливо створити план платежів." << endl;
        return;
    }

    double payment = totalAmount / numberOfPayments;

    for (int i = 0; i < numberOfPayments; i++) {
        installments.push_back(payment);

        dueDates.push_back("Місяць " + to_string(i + 1));
    }
}

// Виведення графіка платежів.
void PaymentPlan::displayPlan() const {
    cout << "\nПЛАН ОПЛАТИ ЧАСТИНАМИ\n";
    cout << "Загальна сума: " << totalAmount << " UAH" << endl;

    for (size_t i = 0; i < installments.size(); i++) {
        cout << "Платіж " << i + 1 << ": "
            << installments[i] << " UAH"
            << ", дата: " << dueDates[i] << endl;
    }
}


// ================= FREE FUNCTIONS =================

// Вільна функція, яка приймає об'єкт класу Client.
void calculateAvailableFunds(const Client& client) {
    double availableFunds = client.getBalance();

    if (client.isAccountActive() && !client.isCardBlocked()) {
        availableFunds += client.getCreditLimit();
    }

    cout << "\nДоступні кошти клієнта: "
        << availableFunds << " UAH" << endl;
}

// Функція, яка повертає об'єкт класу Client.
Client createNewClient() {
    CreditCard card("1111222233334444", 5000);

    Client client("Новий клієнт", "ACC-2026", 10000, card);

    cout << "\nСтворено нового клієнта." << endl;
    cout << "Його баланс: " << client.getBalance() << " UAH" << endl;

    return client;
}