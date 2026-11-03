// ARGOMENTO: puntatori, referenze e modi di passare i parametri a una funzione
//
// - Referenza (int &r = a): un altro nome per la stessa variabile.
// - Puntatore (int *p = &a): una variabile che contiene l'INDIRIZZO di a;
//   con *p si accede al valore puntato (dereferenziazione).
// - Passaggio per valore: la funzione lavora su una COPIA.
// - Passaggio per referenza / puntatore: la funzione puo' modificare l'originale.
// - Referenza costante: niente copia, ma nessuna modifica permessa.

#include <iostream>
#include <string>
#include <limits>


void passaggio_per_valore(int a) {
    std::cout << "passaggio_per_valore: a = " << a << std::endl;
    a = 10; // Modifica locale, non influisce sul chiamante
}

void passaggio_per_referenza(int &a) {
    std::cout << "passaggio_per_referenza: a = " << a << std::endl;
    a = 10; // Modifica il valore originale
}

void passaggio_per_referenza_constante(const int &a) {
    std::cout << "passaggio_per_referenza_constante: a = " << a << std::endl;
    // a = 10; // Errore: non è possibile modificare a
}

void passaggio_per_puntatore(int *a) {
    std::cout << "passaggio_per_puntatore: a = " << *a << std::endl;
    *a = 10; // Modifica il valore originale
}


// a per valore (copia), b per referenza (originale)
void funzione(int a, int &b) {
    a = 10;
    b = 20;
}



int main()
    {
        int a = 5;
        int &b = a;   // b e' un alias di a
        int *c = &a;  // c contiene l'indirizzo di a
        int &d = *c;  // d e' un alias della variabile puntata da c, cioe' di a

        std::cout << "a = " << a << std::endl;
        std::cout << "b = " << b << std::endl;
        std::cout << "c puntatore = " << c << std::endl;         // stampa un indirizzo
        std::cout << "c dereferenced = " << *c << std::endl;     // stampa 5
        std::cout << "d = " << d << std::endl;
        //TEST COSA STAMPA QUESTO?
        // Risposta: "1 20" -> x e' passato per valore (non cambia),
        //                     y per referenza (diventa 20)
        int x = 1;
        int y = 2;
        funzione(x, y);
        std::cout << x << " " << y;
    }
