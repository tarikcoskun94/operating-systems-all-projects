#ifndef FUNCTIONS
#define FUNCTIONS

void countWorkingTime (int seconds) { // Dükkanın kaç saniye çalışacağı buradan kontrol edilir :)
    stringstream stream;
    int timeCycle = 5;

    for (int i = seconds; i > 0; i-=5) {
        stream << "---------------------------------------------------------------------------------REMAINING WORKING TIME: " << i << endl; 
        cout << stream.str();
        stream.str(string());
        if (i < 5) timeCycle = i;
        this_thread::sleep_for(std::chrono::milliseconds(timeCycle * 1000));
    }
}

void initializeSemaphore (int rackHolderCount, int cashierCount) { // semaforlar yapılandırılıyor
    sem_init(&emptyRackSem,0, rackHolderCount);
    sem_init(&fullRackSem, 0, 0);

    sem_init(&freeCashier,0,cashierCount);
    sem_init(&readyCashier, 0, 0);
}

#endif /*FUNCTIONS*/

