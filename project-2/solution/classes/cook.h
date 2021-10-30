#ifndef COOK
#define COOK

class cook {
private:
    string name;
    stringstream stream;
    int workingSpeed;

public:
    cook () { this->name = "NO NAME"; }

    cook (string name) { this->name = name; }

    void makeBurger (burgerRack& theRack){
        while (!endOfTheWorkingTime) {
            sem_wait(&emptyRackSem); // wait ile rack'in boş alanından bir tane eksilttiğimiz temsil edilir. Üretici-tükeci arasındaki band dolu/boş haberleşmesi için.

            this->workingSpeed = ((rand() % 6) + 5); // 5 - 10 saniye arası bir çalışma süresi belirler

            stream << name << " CHEF" << "\t" << ": " << "Burger is being prepared. Time it will take: " << workingSpeed << " Second(s)" << endl; 
            cout << stream.str();
            stream.str(string());

            this_thread::sleep_for(std::chrono::milliseconds(workingSpeed * 1000)); // İş yapmayı temsilen süre geçiriliyor.

            lock_guard<mutex> lock (producerConsumerMtx); // Bu lock, hem aşağıdaki satırlara process içinde bir nevi atomiklik sağlıyor, hem de üretici-tükeci sırasını sağlıyor.
            {
            burger preparedBurger;

            theRack.addBurger(preparedBurger);

            stream << name << " CHEF" << "\t" << ": " << "Burger is ready!" << endl;
            cout << stream.str();

            sem_post(&fullRackSem); // post ile rack'in boş alanından bir tanesini doldurduğumuz temsil edilir. Üretici-tükeci arasındaki band dolu/boş haberleşmesi için.
            } // Kullanılan lock scope tabanlı bir lock olduğu için, scope dışına çıkarken unlock yapılıyor.

            stream.str(string());
        }
    }

    ~cook () {};
};

#endif /*COOK*/

