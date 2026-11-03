// ARGOMENTO: ricorsione su una std::list (versione con copia della lista)
//
// Esercizio:
// Implementare una funzione ricorsiva
// che permette di esplorare una sotto-parte di
// una lista di interi
// e che semplicemente la stampi a video
//
// Idea: stampo il primo elemento, lo tolgo e richiamo la funzione sul resto.
// NOTA: la lista e' passata per VALORE, quindi ogni chiamata ne fa una copia
// (semplice da capire ma costoso). Vedi list_subparts.cpp per la versione
// con iteratori, che non copia nulla e permette di scegliere la sotto-parte.

#include <iostream>
#include <list>

void esploraSottoParte(std::list<int> numeri){
    // caso base: lista vuota -> vado a capo e mi fermo
    if (numeri.empty()) {
        std::cout << std::endl;
        return;
    }
    int a = numeri.front();  // primo elemento
    numeri.pop_front();      // lo rimuovo dalla copia locale
    std::cout << a << " ";
    return esploraSottoParte(numeri);  // ricorsione sul resto della lista
}

int main()
    {
        std::list<int> numeri = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
        esploraSottoParte(numeri);
    }
