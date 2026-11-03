// ARGOMENTO: ricorsione semplice e ricorsione di coda
//
// - Ricorsione: una funzione che chiama se' stessa. Serve sempre un CASO BASE.
// - Ricorsione NON di coda: dopo la chiamata ricorsiva c'e' ancora lavoro da fare
//   (la moltiplicazione), quindi ogni chiamata deve restare in memoria sullo stack.
// - Ricorsione DI CODA: la chiamata ricorsiva e' l'ultima operazione; il risultato
//   parziale viaggia nell'accumulatore (acc). Il compilatore puo' trasformarla in un ciclo.

#include <iostream>


// ricorsione non di coda
// fattoriale(3) = 3 * fattoriale(2) = 3 * 2 * fattoriale(1) = 3 * 2 * 1 * fattoriale(0) = 6
int fattoriale(int x){
    if (x == 0)
        return 1;  // caso base
    else
        return x * fattoriale(x - 1);
}

// ricorsione di coda
// fattoriale_coda(3, 1) -> (2, 3) -> (1, 6) -> (0, 6) -> 6
int fattoriale_coda(int x, int acc) {
    if (x == 0)
        return acc;  // caso base: l'accumulatore contiene gia' il risultato
    else
        return fattoriale_coda(x - 1, x * acc);
}

int main()
    {
        int fatt = fattoriale(3);
        std::cout << "Fattoriale di 3: " << fatt << std::endl;

        int fatt_coda = fattoriale_coda(3, 1);
        std::cout << "Fattoriale di 3 (ricorsione di coda): " << fatt_coda << std::endl;
    }
