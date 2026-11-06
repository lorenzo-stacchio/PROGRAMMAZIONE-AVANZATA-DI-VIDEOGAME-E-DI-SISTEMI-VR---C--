// ARGOMENTO: overloading (sovraccarico) di metodi e operatori
//
// OVERLOADING = piu' funzioni con lo STESSO NOME ma PARAMETRI DIVERSI
// (numero o tipo). Il compilatore sceglie quale chiamare guardando gli argomenti,
// a TEMPO DI COMPILAZIONE. Il solo tipo di ritorno diverso NON basta.

// POLIMORFISMO STATICO: il compilatore sceglie quale funzione chiamare a tempo di compilazione.

// OVERLOADING DEGLI OPERATORI: si puo' ridefinire il significato di +, -, ==, <<, ...
// per i propri tipi, scrivendo funzioni chiamate operator+, operator==, ecc.
// 
// Da non confondere con l'OVERRIDING (vedi 04_ereditarieta_overriding.cpp):
// una classe derivata RIDEFINISCE un metodo virtuale della classe base.

#include <iostream>
#include <string>

class Calcolatrice {
public:
    // Stesso nome "somma", parametri diversi
    int somma(int a, int b) const {
        std::cout << "  [somma(int, int)]       ";
        return a + b;
    }
    int somma(int a, int b, int c) const {
        std::cout << "  [somma(int, int, int)]  ";
        return a + b + c;
    }
    double somma(double a, double b) const {
        std::cout << "  [somma(double, double)] ";
        return a + b;
    }
    std::string somma(const std::string& a, const std::string& b) const {
        std::cout << "  [somma(string, string)] ";
        return a + b;
    }
    // double somma(int a, int b) const;  // ERRORE: differisce solo per il tipo di ritorno
};

class Vettore2D {
private:
    double x, y;

public:
    // Overloading anche dei costruttori
    Vettore2D() : x(0), y(0) {}
    Vettore2D(double x, double y) : x(x), y(y) {}

    // v1 + v2  ->  v1.operator+(v2)
    Vettore2D operator+(const Vettore2D& altro) const {
        return Vettore2D(x + altro.x, y + altro.y);
    }

    Vettore2D operator-(const Vettore2D& altro) const {
        return Vettore2D(x - altro.x, y - altro.y);
    }

    // v * 2.0  ->  moltiplicazione per uno scalare
    Vettore2D operator*(double k) const {
        return Vettore2D(x * k, y * k);
    }

    // v1 += v2: modifica l'oggetto e restituisce una referenza a se' stesso
    // (cosi' si possono concatenare: a += b += c)
    Vettore2D& operator+=(const Vettore2D& altro) {
        x += altro.x;
        y += altro.y;
        return *this;
    }

    bool operator==(const Vettore2D& altro) const {
        return x == altro.x && y == altro.y;
    }

    // friend: funzione esterna alla classe che puo' accedere ai membri privati.
    // operator<< non puo' essere un metodo, perche' a sinistra c'e' std::cout, non un Vettore2D.
    friend std::ostream& operator<<(std::ostream& os, const Vettore2D& v);
};

std::ostream& operator<<(std::ostream& os, const Vettore2D& v) {
    os << "(" << v.x << ", " << v.y << ")";
    return os;   // restituisco lo stream per poter concatenare cout << a << b
}

// 2.0 * v: a sinistra c'e' un double, quindi serve una funzione esterna
Vettore2D operator*(double k, const Vettore2D& v) {
    return v * k;   // riuso l'operatore gia' definito
}

int main()
{
    std::cout << "=== Overloading dei metodi ===" << std::endl;
    Calcolatrice calc;
    std::cout << calc.somma(2, 3) << std::endl;
    std::cout << calc.somma(2, 3, 4) << std::endl;
    std::cout << calc.somma(2.5, 3.1) << std::endl;
    std::cout << calc.somma(std::string("Ciao "), std::string("mondo")) << std::endl;
    // calc.somma(2, 3.1);  // ERRORE: ambiguo, non sa se convertire verso int o double

    std::cout << std::endl << "=== Overloading degli operatori ===" << std::endl;
    Vettore2D a(1, 2);
    Vettore2D b(3, 4);
    Vettore2D zero;   // costruttore di default

    std::cout << "a = " << a << ", b = " << b << ", zero = " << zero << std::endl;
    std::cout << "a + b   = " << a + b << std::endl;
    std::cout << "b - a   = " << b - a << std::endl;
    std::cout << "a * 3   = " << a * 3 << std::endl;
    std::cout << "3 * a   = " << 3 * a << std::endl;
    std::cout << std::boolalpha;
    std::cout << "a == b  ? " << (a == b) << std::endl;
    std::cout << "a + b == Vettore2D(4, 6) ? " << (a + b == Vettore2D(4, 6)) << std::endl;

    a += b;
    std::cout << "dopo a += b, a = " << a << std::endl;

    return 0;
}
