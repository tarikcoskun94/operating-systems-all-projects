#ifndef GLOBALS
#define GLOBALS

bool endOfTheWorkingTime = false;

mutex producerConsumerMtx; // cook ve cashier arasındaki karşılıklı dışlama için

sem_t emptyRackSem; // Burger rackin doluluğu için
sem_t fullRackSem; // ...

sem_t freeCashier; // Müşteri-Kasiyer arası iletişim
sem_t readyCashier; // ...

#endif /*GLOBALS*/

