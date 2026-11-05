#include "PaymentSystem.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Ukrainian");

    cout << "================================" << endl;
    cout << "       ПЛАТІЖНА СИСТЕМА" << endl;
    cout << "================================" << endl;


    // 1. Демонстрація конструкторів класу Transaction.

    Transaction transaction1;

    Transaction transaction2(
        "05.11.2026", 1500, "Оплата товару"
    );

    Transaction transaction3(transaction2);


    // 2. Демонстрація конструкторів класу CreditCard.

    CreditCard card1;

    CreditCard card2("1234567812345678", 10000);

    CreditCard card3(card2);


    // 3. Демонстрація конструкторів класу Client.

    Client client1;

    Client client2(
        "Анастасія",
        "ACC-12345",
        20000,
        card2
    );

    Client client3(client2);


    // 4. Демонстрація конструкторів класу Administrator.

    Administrator admin1;

    Administrator admin2("Головний адміністратор");

    Administrator admin3(admin2);


    // 5. Демонстрація конструкторів класу PaymentPlan.

    PaymentPlan plan1;

    PaymentPlan plan2(12000, 4);

    PaymentPlan plan3(plan2);


    // 6. Оплата замовлення клієнтом.

    cout << "\n--- ОПЛАТА ЗАМОВЛЕННЯ ---" << endl;

    client2.payOrder(3000, "05.11.2026");


    // 7. Переказ коштів іншому клієнту.

    cout << "\n--- ПЕРЕКАЗ КОШТІВ ---" << endl;

    client2.transfer(2000, "05.11.2026");


    // 8. Перегляд інформації про клієнта.

    client2.displayInfo();


    // 9. Перегляд історії платежів клієнтом.

    client2.displayHistory();


    // 10. Перегляд історії адміністратором.

    admin2.viewHistory(client2);


    // 11. Запит на зміну кредитного ліміту.

    cout << "\n--- ЗМІНА КРЕДИТНОГО ЛІМІТУ ---" << endl;

    client2.requestCreditLimit(15000);

    admin2.approveCreditLimit(client2);


    // 12. Перевірка перевищення кредитного ліміту.

    cout << "\n--- ПЕРЕВІРКА КРЕДИТНОГО ЛІМІТУ ---" << endl;

    client2.setBalance(-12000);

    admin2.blockCardForCreditOverrun(client2);


    // 13. Відображення плану оплати частинами.

    cout << "\n--- ОПЛАТА ЧАСТИНАМИ ---" << endl;

    plan2.displayPlan();


    // 14. Виклик вільної функції з об'єктом класу Client.

    calculateAvailableFunds(client2);


    // 15. Виклик функції, яка повертає об'єкт класу Client.

    cout << "\n--- СТВОРЕННЯ НОВОГО КЛІЄНТА ---" << endl;

    Client newClient = createNewClient();

    newClient.displayInfo();


    // 16. Вказівник на об'єкт класу Client.

    cout << "\n--- ВКАЗІВНИК НА ОБ'ЄКТ ---" << endl;

    Client* clientPointer = &client2;

    clientPointer->displayInfo();


    // 17. Створення об'єкта в динамічній пам'яті.

    cout << "\n--- ДИНАМІЧНА ПАМ'ЯТЬ ---" << endl;

    Client* dynamicClient = new Client(
        "Динамічний клієнт",
        "ACC-999",
        5000,
        card2
    );

    dynamicClient->displayInfo();

    delete dynamicClient;

    dynamicClient = nullptr;


    // 18. Масив об'єктів.

    cout << "\n--- МАСИВ ОБ'ЄКТІВ ---" << endl;

    Client clients[2];

    clients[0].displayInfo();
    clients[1].displayInfo();


    // 19. Статичні поля та статичні методи.

    cout << "\n--- СТАТИЧНІ ДАНІ ---" << endl;

    cout << "Кількість створених клієнтів: "
        << Client::getClientCount() << endl;

    cout << "Кількість створених транзакцій: "
        << Transaction::getTransactionCount() << endl;


    // 20. Скасування рахунку клієнта.

    cout << "\n--- СКАСУВАННЯ РАХУНКУ ---" << endl;

    client2.cancelAccount();

    client2.displayInfo();


    cout << "\n================================" << endl;
    cout << "       КІНЕЦЬ ПРОГРАМИ" << endl;
    cout << "================================" << endl;

    return 0;
}