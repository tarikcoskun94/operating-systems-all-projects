#include "headers/Prj2header.h"
#include "headers/sharedVariables.h"
#include "headers/functions.h"

#include "classes/burger.h"
#include "classes/burgerRack.h"
#include "classes/cook.h"
#include "classes/cashier.h"
#include "classes/customer.h"



int main () {
    int workingTime; // Programın çalışma süresini kullanıcıdan almak için.

    thread* cookThreads = new thread[COOK_COUNT]; // Aşçılar için thread dizisi.
    string chefNames[COOK_COUNT] = {"Mehmet", "Danilo", "Somer", "Hazer"}; // Aşçı isimleri :)

    thread* cashierThreads = new thread[CASHIER_COUNT]; // Kasiyerler için thread dizisi.
    string cashierNames[CASHIER_COUNT] = {"Tarik", "Alexis"}; // Kasiyer isimleri :)

    thread* customerThreads = new thread[CUSTOMER_COUNT]; // Müşteriler için thread dizisi.
    string customerNames[CUSTOMER_COUNT] = {"Acun", "Cem", "Şeyma", "Serenay"}; // Müşteri isimleri :)



    srand(time(0)); // Program içinde, farklı farklı rastgele sayıların üretilmesini aktifleştirir.

    cout << "Enter working time in seconds: "; cin >> workingTime; cout << endl << endl; // Kullanıcıdan çalışma süresi alınır.

    burgerRack theRack; 

    initializeSemaphore(RACK_HOLDER_COUNT, CASHIER_COUNT); // Tüm semaphoreları yapılandırmayı başlatır.

    thread startWork (countWorkingTime, workingTime); // Çalışma süresini kontrol eden thread başlatılır. Yani dükkan açılıyor.

    for (int i = 0; i < COOK_COUNT; i++) { // Aşçıarın threadleri yaratılır.
        cookThreads[i] = thread(&cook::makeBurger, new cook(chefNames[i]), ref(theRack));
    }

    for (int i = 0; i < CASHIER_COUNT; i++) { // Kasiyerlerin threadleri yaratılır.
        cashierThreads[i] = thread(&cashier::takeBurger, new cashier(cashierNames[i]), ref(theRack));
    }

    for (int i = 0; i < CUSTOMER_COUNT; i++) { // Müşterilerin threadleri yaratılır.
        customerThreads[i] = thread(&customer::order, new customer(customerNames[i]));
    }



    for (int i = 0; i < COOK_COUNT; i++) { // Aşçı threadler için join işlemi.
        cookThreads[i].join();
    }

    for (int i = 0; i < CASHIER_COUNT; i++) { // Kasiyer threadler için join işlemi.
        cashierThreads[i].join();
    }

    for (int i = 0; i < CUSTOMER_COUNT; i++) { // Müşterilerin threadleri yaratılır.
        customerThreads[i].join();
    }

    startWork.join(); // Çalışma süresi threadi için join. Dükkan kapanıyor.

    cout << "Burgers on the rack: " << theRack.getBurgerCount() << endl;

    return 0;
}
