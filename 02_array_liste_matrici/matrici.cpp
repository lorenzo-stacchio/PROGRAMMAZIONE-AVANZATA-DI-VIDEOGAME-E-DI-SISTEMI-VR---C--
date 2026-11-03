// ARGOMENTO: matrici (array bidimensionali) e liste di liste
//
// - Un array 2D e' un "array di array": array[riga][colonna].
// - sizeof restituisce la dimensione in byte: dividendo si ottiene il numero di elementi.
// - Alternativa dinamica: std::list<std::list<int>> (ogni riga e' una lista).
//
// NOTA: lo "structured binding" (auto [a, b, c]) richiede C++17 (/std:c++17 con cl.exe).

#include <iostream>
#include <list>


int main()
    {
        std::cout <<"MATRICE" << std::endl;

        //array
        // int array[5][5] = {{1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}, {11, 12, 13, 14, 15}, {16, 17, 18, 19, 20}, {21, 22, 23, 24, 25}};
        int array[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

        // modalità scorrimento uno: doppio for con indici
        // numero righe   = sizeof(array)       / sizeof(array[0])    = 36 byte / 12 byte = 3
        // numero colonne = sizeof(array[0])    / sizeof(array[0][0]) = 12 byte / 4 byte  = 3
        for (int i = 0; i < (sizeof(array) / sizeof(array[0])); i++) //lunghezza ARRAY DIVISO LUNGHEZZA SINGOLO BLOCCO
        {
            for (int j = 0; j < sizeof(array[0])/sizeof(array[0][0]); j++) //lunghezza SINGOLO BLOCCO DIVISO SPAZIO IN MEMORIA SINGOLO ELEMENTO
            {
                std::cout << array[i][j] << " ";
            }
            std::cout << std::endl;
        }

        //modalità scorrimento due: for each + structured binding
        // ogni riga (array di 3 int) viene "spacchettata" in tre variabili
        for (auto [primo,secondo,terzo] : array)
        {
          std::cout << primo << " " << secondo << " " << terzo << " ";
        }
        std::cout << std::endl;

        // matrice come lista di liste
        std::cout << "MATRICE COME LISTA" << std::endl;
        std::list<std::list<int>> matrice;

        matrice.push_back({1, 2, 3});
        matrice.push_back({4, 5, 6});
        matrice.push_back({7, 8, 9});
        matrice.pop_back(); // Rimuove l'ultima riga

        // const auto& evita di copiare ogni riga (riferimento costante)
        for (const auto& riga : matrice)
        {
            for (int valore : riga)
            {
                std::cout << valore << " ";
            }
            std::cout << std::endl;
        }

        return 0;
    }
