#ifndef BURGER_RACK
#define BURGER_RACK

class burgerRack {
private:
    queue <burger> rack;

public:
    void addBurger (burger brg) { rack.push(brg); }
    void takeBurger () { rack.pop(); }
    int getBurgerCount () { return rack.size(); }
};

#endif /*BURGER_RACK*/

