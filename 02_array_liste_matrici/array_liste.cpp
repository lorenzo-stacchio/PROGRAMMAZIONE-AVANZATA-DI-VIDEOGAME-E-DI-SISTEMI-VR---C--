// ARGOMENTO: array statici e std::list
//
// - Array: dimensione fissa, elementi contigui in memoria, accesso con [indice].
// - std::list: lista doppiamente concatenata, cresce/si riduce dinamicamente,
//   inserimento/rimozione veloci in testa e in coda, ma niente accesso con [].

#include <iostream>
#include <list>

int main()
    {
        //array di 5 interi inizializzato con una lista di valori
        int array[5] = {1, 2, 3, 4, 5};

        //for each loop (range-based for): i assume a turno il valore di ogni elemento
        for (int i : array)
        {
            std::cout << i << " ";
        }

        //liste con pacchetto list
        std::list<int> lista;

        // append in C++ list
        lista.push_back(1);  // lista: 1
        lista.push_back(2);  // lista: 1 2
        lista.push_back(3);  // lista: 1 2 3
        lista.pop_back();    // Rimuove l'ultimo elemento  -> 1 2
        lista.pop_front();   // Rimuove il primo elemento  -> 2


        for (int valore : lista)
        {
            std::cout << valore << " ";
        }
        std::cout << std::endl;

        return 0;
    }
