// ARGOMENTO: ricorsione su una sotto-parte di std::list usando gli iteratori
//
// Un iteratore e' un "segnaposto" che indica un elemento del contenitore.
// L'intervallo [begin, end) include begin ed ESCLUDE end (convenzione della STL).
// Passando solo due iteratori non si copia la lista (a differenza di
// esplora_lista_ricorsiva.cpp).

#include <iostream>
#include <list>
#include <iterator> // Per std::next

// Funzione ricorsiva che esplora e stampa la sotto-parte di una std::list
// const_iterator: permette di leggere gli elementi ma non di modificarli
void printSubList(std::list<int>::const_iterator begin, std::list<int>::const_iterator end) {
    // Caso base: se l'iteratore d'inizio ha raggiunto la fine della sotto-parte, si ferma
    if (begin == end) {
        std::cout << std::endl;
        return;
    }

    // Azione: stampa l'elemento corrente della lista (*begin = valore puntato)
    std::cout << *begin << " ";

    // Chiamata ricorsiva in coda (Tail Call): passiamo all'elemento successivo
    printSubList(std::next(begin), end);
}

int main() {
    // Creiamo una std::list di esempio
    std::list<int> numeri = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};

    // Definiamo i confini della sotto-parte.
    // Esempio: vogliamo stampare dal terzo elemento (30) fino al settimo (70) incluso.
    // Usiamo std::next perché std::list non supporta l'operatore '+' (es. numeri.begin() + 2)
    auto sottoParteInizio = std::next(numeri.begin(), 2); // Salta 2 elementi, punta a 30
    auto sottoParteFine   = std::next(numeri.begin(), 7); // Salta 7 elementi, punta a 80 (escluso)

    std::cout << "Stampa della sotto-parte di std::list: ";
    printSubList(sottoParteInizio, sottoParteFine); // stampa: 30 40 50 60 70

    return 0;
}
