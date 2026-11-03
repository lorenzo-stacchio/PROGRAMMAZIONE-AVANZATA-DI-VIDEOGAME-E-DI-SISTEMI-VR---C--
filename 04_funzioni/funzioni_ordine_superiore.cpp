#include <iostream>

// Una funzione di ordine superiore e' una funzione che:
//   - riceve un'altra funzione come parametro, oppure
//   - restituisce una funzione come risultato.
// In C/C++ "classico" lo si fa con i PUNTATORI A FUNZIONE.

// --- Funzioni "semplici" da passare in giro ---
int somma(int a, int b) { return a + b; }
int prodotto(int a, int b) { return a * b; }
int massimo(int a, int b) { return a > b ? a : b; }

int doppio(int x) { return x * 2; }
int quadrato(int x) { return x * x; }

bool pari(int x) { return x % 2 == 0; }

// --- 1) Funzione che RICEVE un puntatore a funzione ---
// Sintassi: tipo_ritorno (*nome)(tipi_parametri)
int applica(int (*operazione)(int, int), int a, int b)
{
    return operazione(a, b);   // chiamo la funzione puntata
}

// --- 2) "map": applica f a ogni elemento dell'array ---
void trasforma(int array[], int n, int (*f)(int))
{
    for (int i = 0; i < n; i++) {
        array[i] = f(array[i]);
    }
}

// --- 3) "filter": stampa solo gli elementi che soddisfano il predicato ---
void stampa_se(const int array[], int n, bool (*predicato)(int))
{
    for (int i = 0; i < n; i++) {
        if (predicato(array[i])) {
            std::cout << array[i] << " ";
        }
    }
    std::cout << std::endl;
}

// --- 4) "reduce": riduce l'array a un solo valore ---
int riduci(const int array[], int n, int iniziale, int (*op)(int, int))
{
    int risultato = iniziale;
    for (int i = 0; i < n; i++) {
        risultato = op(risultato, array[i]);
    }
    return risultato;
}

// --- 5) Funzione che RESTITUISCE un puntatore a funzione ---
// Con un alias (using) la sintassi diventa molto piu' leggibile.
using OpBinaria = int (*)(int, int);

OpBinaria scegli_operazione(char simbolo)
{
    switch (simbolo) {
        case '+': return somma;
        case '*': return prodotto;
        default:  return massimo;
    }
}

void stampa(const int array[], int n)
{
    for (int i = 0; i < n; i++) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}

int main()
{
    // Puntatore a funzione base: il nome della funzione "decade" a puntatore
    int (*p)(int, int) = somma;     // equivalente a: = &somma;
    std::cout << "p(3, 4) = " << p(3, 4) << std::endl;
    std::cout << "Indirizzo di somma: " << (void*)somma << std::endl << std::endl;

    // 1) Passare funzioni diverse alla stessa funzione
    std::cout << "applica(somma, 3, 4)     = " << applica(somma, 3, 4) << std::endl;
    std::cout << "applica(prodotto, 3, 4)  = " << applica(prodotto, 3, 4) << std::endl;
    std::cout << "applica(massimo, 3, 4)   = " << applica(massimo, 3, 4) << std::endl << std::endl;

    // 2) map
    int array[] = {1, 2, 3, 4, 5};
    const int n = 5;
    std::cout << "Array originale:   ";
    stampa(array, n);

    trasforma(array, n, doppio);
    std::cout << "Dopo doppio:       ";
    stampa(array, n);

    trasforma(array, n, quadrato);
    std::cout << "Dopo quadrato:     ";
    stampa(array, n);

    // 3) filter
    int numeri[] = {1, 2, 3, 4, 5, 6, 7, 8};
    std::cout << std::endl << "Solo i pari:       ";
    stampa_se(numeri, 8, pari);

    // 4) reduce
    std::cout << "Somma totale:      " << riduci(numeri, 8, 0, somma) << std::endl;
    std::cout << "Prodotto totale:   " << riduci(numeri, 8, 1, prodotto) << std::endl;
    std::cout << "Massimo:           " << riduci(numeri, 8, numeri[0], massimo) << std::endl << std::endl;

    // 5) Funzione che restituisce una funzione
    OpBinaria op = scegli_operazione('*');
    std::cout << "scegli_operazione('*')(6, 7) = " << op(6, 7) << std::endl;

    // Array di puntatori a funzione: una piccola "tabella" di operazioni
    OpBinaria tabella[] = {somma, prodotto, massimo};
    const char* nomi[] = {"somma", "prodotto", "massimo"};
    for (int i = 0; i < 3; i++) {
        std::cout << nomi[i] << "(10, 5) = " << tabella[i](10, 5) << std::endl;
    }

    // Bonus: una lambda SENZA cattura si converte automaticamente
    // in puntatore a funzione, quindi si puo' passare alle stesse funzioni.
    std::cout << std::endl << "Con una lambda (a - b): "
              << applica([](int a, int b) { return a - b; }, 10, 3) << std::endl;

    return 0;
}
