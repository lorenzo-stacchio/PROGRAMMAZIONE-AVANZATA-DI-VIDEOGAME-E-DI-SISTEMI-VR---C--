/// TO COMPLETE
#include <iostream>

class Corsa{
    public:
    void bruciaCalorie(){
        std::cout << "Brucia calorie" << std::endl;
    }
};

class Baseball{
    public:
    void bruciaCalorie(){
        std::cout << "Brucia calorie" << std::endl;
    }
};

//CHIAMATE LA FUNZIONE BRUCIA CALORIE nella corsa nel baseball
// in una funzione "test";

class CorsaNelBaseball: public Corsa, public Baseball{
    public:
    void bruciaCalorie(){
        std::cout << "Brucia calorie nella corsa nel baseball" << std::endl;
    }
    void test(){
        Corsa::bruciaCalorie();
        // Baseball::bruciaCalorie();
        // bruciaCalorie();
    }
};


int main()
{
   

}