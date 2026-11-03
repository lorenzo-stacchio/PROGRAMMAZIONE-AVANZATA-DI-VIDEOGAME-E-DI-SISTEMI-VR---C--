// ARGOMENTO: dichiarazione vs definizione di funzioni e overloading
//
// - Dichiarazione (prototipo): dice al compilatore che la funzione esiste.
//   Si puo' ripetere piu' volte, purche' le firme siano compatibili.
// - Definizione: contiene il corpo della funzione. Deve essere unica.
// - Overloading: piu' funzioni con lo STESSO nome ma parametri DIVERSI.
//   (Da non confondere con l'overriding, che riguarda le classi e i metodi virtuali.)
// - Una funzione va dichiarata PRIMA di essere usata.

#include <iostream>
#include <string>
#include <limits>


void f(int a, const char* b); // dichiarazione

void f(int a, const char*) { // definizione senza uso variabile b (il nome si puo' omettere)
    /* ... */
}

// Dichiarazione ripetuta e compatibile con uso variabile b
void f(int a, const char* b);

// Overloading: stesso nome f, ma un solo parametro
void f(int a) {
    std::cout << "f(int a) called with a = " << a << std::endl;
};


void example() {
    f(3, "abc");   // chiama f(int, const char*)
    // g();        // ERRORE di compilazione: g non e' ancora stata dichiarata qui.
                   // Inoltre g non e' mai definita, quindi darebbe anche errore del linker.
}

void g();  // dichiarata troppo tardi per essere usata in example()

int main()
    {
        example();
    }
