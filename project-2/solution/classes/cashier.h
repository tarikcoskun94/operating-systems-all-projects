#ifndef CASHIER
#define CASHIER

class cashier {
private:
    string name;
    stringstream stream;
    int workingSpeed;

public:
    cashier () { this->name = "NO NAME";}

    cashier (string name) { this->name = name;}

    void takeBurger (burgerRack& theRack){
        while (!endOfTheWorkingTime) {
            stream << "CASHIER " << name << "\t" << ": " << "I can get an order here!"<< endl;
            cout << stream.str();
            stream.str(string());

            sem_wait(&readyCashier); // Müşteri talebi olana kadar uyur.

            sem_wait(&fullRackSem); // wait ile rack'in dolu alanından bir tane eksilttiğimiz temsil edilir. Üretici-tükeci arasındaki band dolu/boş haberleşmesi için.

            this->workingSpeed = ((rand() % 5) + 1); // 1 - 5 saniye arası bir çalışma süresi belirler

            stream << "CASHIER " << name << "\t" << ": " << "Order is being prepared. Time it will take: " << workingSpeed << " Second(s)" << endl; 
            cout << stream.str();
            stream.str(string());

            this_thread::sleep_for(std::chrono::milliseconds(workingSpeed * 1000)); // İş yapmayı temsilen süre geçiriliyor.

            lock_guard<mutex> lock (producerConsumerMtx); // Bu lock, hem aşağıdaki satırlara process içinde bir nevi atomiklik sağlıyor, hem de üretici-tükeci sırasını sağlıyor.
            {
            theRack.takeBurger();

            stream << "CASHIER " << name << "\t" << ": " << "Order is ready!" << endl;
            cout << stream.str();

            sem_post(&emptyRackSem); // post ile rack'in boş alanını bir tane artırdığımız temsil edilir. Üretici-tükeci arasındaki band dolu/boş haberleşmesi için.
            sem_post(&freeCashier); // Kasiyerin işinin bittiği, müsait olduğu bilgisi veriliyor.
            } // Kullanılan lock scope tabanlı bir lock olduğu için, scope dışına çıkarken unlock yapılıyor.

            stream.str(string());          
        }
    }

    ~cashier () {};
};

#endif /*CASHIER*/

