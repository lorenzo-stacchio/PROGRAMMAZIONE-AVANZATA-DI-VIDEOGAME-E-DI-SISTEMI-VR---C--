// ARGOMENTO: funzioni lambda
//
// Una lambda e' una funzione anonima scritta "al volo":
//   [cattura](parametri) { corpo }
// Qui la usiamo come criterio di ordinamento per std::sort.

#include <iostream>
#include <string>
#include <limits>
#include <cstdint>
#include <algorithm> // std::sort

int main()
    {
        int array[] = {7, 2, 5, 1};
        std::cout << "Array originale: ";
        for (int i = 0; i < 4; i++) {
            std::cout << array[i] << " ";
        }
        std::cout << std::endl;

        // [] = nessuna variabile catturata dall'esterno.
        // Restituisce true se a deve venire prima di b -> ordine decrescente.
        auto lambda = [](int a, int b) { return a > b; };
        // std::sort(inizio, fine, comparatore): array + 4 punta "uno dopo" l'ultimo elemento
        std::sort(array, array + 4, lambda);

        std::cout << "Array ordinato: ";
        for (int i = 0; i < 4; i++) {
            std::cout << array[i] << " ";
        }
        std::cout << std::endl;

    }
