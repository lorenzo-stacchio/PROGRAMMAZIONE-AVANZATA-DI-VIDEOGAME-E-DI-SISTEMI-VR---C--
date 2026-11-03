// ARGOMENTO: ricorsione di coda con moltissime chiamate (ottimizzazione del compilatore)
//
// Con 1.000.000.000 di chiamate ricorsive una ricorsione normale esaurirebbe lo stack
// (stack overflow). Con la ricorsione di coda e l'ottimizzazione /O2 il compilatore
// trasforma la ricorsione in un ciclo, quindi il programma termina senza crash.
//
// NOTA: il risultato stampato e' 0. Il fattoriale di numeri cosi' grandi supera
// enormemente il massimo di unsigned long long (overflow); dopo 64 fattori 2
// accumulati tutti i bit diventano zero. Il punto dell'esempio e' lo stack, non il valore.

#include <iostream>

// Ricorsione in coda: i parametri sono passati per valore
// (non per riferimento), così il frame del chiamante non serve più
// dopo la chiamata e il compilatore (con /O2) può riusarlo.

// acc = 1 e' un parametro di default: si puo' chiamare fattoriale_ricorsivo(n)
unsigned long long fattoriale_ricorsivo(unsigned int a, unsigned long long acc = 1){
    if (a == 0)
        return acc;
    return fattoriale_ricorsivo(a - 1, acc * a);
}


int main()
    {
    unsigned int b = 1000000000;
    std::cout << fattoriale_ricorsivo(b) << std::endl;
    }
