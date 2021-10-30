#ifndef CUSTOMER
#define CUSTOMER

class customer {
private:
    string name;
    stringstream stream;
    int orderSpeed;

public:
    static int customerCount;

    customer () {  customerCount++; this->name = "NO NAME-" + to_string(customerCount); }

    customer (string name) { customerCount++; this->name = name;}

    void order (){
        sem_wait(&freeCashier); // boştaki kasiyerlerden birini alır.

        this->orderSpeed = ((rand() % 6) + 2); // 2 - 7 saniye arası bir sipariş süresi belirler

        stream << "CUSTOMER " << name << "\t" << ": " << "I'd like to order! - One burger please. Time it will take: " << orderSpeed << " Second(s)" << endl; 
        cout << stream.str();

        this_thread::sleep_for(std::chrono::milliseconds(orderSpeed * 1000)); // Sipariş sürecini temsilen süre geçiriliyor.

        sem_post(&readyCashier); // kasiyerin uyanması için.
    }

    ~customer () {}
};

int customer::customerCount = 0; 

#endif /*CUSTOMER*/

