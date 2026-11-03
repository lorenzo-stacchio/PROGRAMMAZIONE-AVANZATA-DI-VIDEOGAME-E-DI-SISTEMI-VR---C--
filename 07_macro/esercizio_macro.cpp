// ESERCIZIO: le macro
//
// TRACCIA
// Scrivi le seguenti macro e verifica che il main stampi i risultati attesi.
//
//   1) ARRAY_SIZE(arr)      -> numero di elementi di un array statico (usa sizeof)
//   2) MIN(a, b)            -> il minore tra a e b (attenzione alle parentesi!)
//   3) CLAMP(x, lo, hi)     -> "blocca" x tra lo e hi, usando MIN e MAX
//   4) RIPETI(n)            -> ripete l'istruzione successiva n volte (un for nascosto)
//   5) CONTROLLA(cond, msg) -> se cond e' falsa stampa "ERRORE <file>:<riga>: <msg>"
//                              (usa __FILE__, __LINE__ e il trucco do/while(0))
//   6) LOG(msg)             -> stampa "[LOG] <msg>" SOLO se e' definita ABILITA_LOG,
//                              altrimenti non fa nulla
//   7) DEFINISCI_GETTER(tipo, nome) -> genera una funzione "tipo get_nome()" che
//                              restituisce la variabile globale g_nome (usa ##)
//
// Prova poi a:
//   - commentare #define ABILITA_LOG e vedere i LOG sparire
//   - togliere le parentesi esterne da MIN e calcolare 10 - MIN(3, 4)
//
// SOLUZIONE (sotto)

#include <iostream>

// 1) sizeof(arr) = byte totali, sizeof((arr)[0]) = byte di un elemento
//    Funziona SOLO su array veri, non su puntatori (un array passato a una funzione
//    diventa un puntatore e sizeof restituirebbe la dimensione del puntatore).
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

// 2) parentesi su ogni parametro e su tutta l'espressione
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

// 3) prima taglio sotto (MAX con lo), poi sopra (MIN con hi)
#define CLAMP(x, lo, hi) MIN(MAX((x), (lo)), (hi))

// 4) l'istruzione dopo RIPETI(n) diventa il corpo del for
#define RIPETI(n) for (int rip_ = 0; rip_ < (n); ++rip_)

// 5) #cond trasforma la condizione in testo, cosi' si vede quale e' fallita
#define CONTROLLA(cond, msg)                                              \
    do {                                                                  \
        if (!(cond)) {                                                    \
            std::cout << "ERRORE " << __FILE__ << ":" << __LINE__         \
                      << ": " << msg << " (condizione: " #cond ")"        \
                      << std::endl;                                       \
        }                                                                 \
    } while (0)

// 6) compilazione condizionale
#define ABILITA_LOG

#ifdef ABILITA_LOG
    #define LOG(msg) std::cout << "[LOG] " << msg << std::endl
#else
    #define LOG(msg) do { } while (0)
#endif

// 7) ## incolla i pezzi: get_##nome con nome=eta diventa get_eta
#define DEFINISCI_GETTER(tipo, nome) \
    tipo get_##nome() { return g_##nome; }

int g_eta = 30;
double g_altezza = 1.80;

DEFINISCI_GETTER(int, eta)          // genera: int get_eta() { return g_eta; }
DEFINISCI_GETTER(double, altezza)   // genera: double get_altezza() { return g_altezza; }

int main()
{
    LOG("Inizio programma");

    // 1) ARRAY_SIZE
    int voti[] = {18, 24, 30, 27, 21};
    std::cout << "Numero di voti: " << ARRAY_SIZE(voti) << "   (atteso 5)" << std::endl;

    // 2) MIN
    std::cout << "MIN(3, 4) = " << MIN(3, 4) << "   (atteso 3)" << std::endl;
    std::cout << "10 - MIN(3, 4) = " << 10 - MIN(3, 4) << "   (atteso 7)" << std::endl;

    // 3) CLAMP: utile ad esempio per tenere un voto tra 18 e 30
    std::cout << "CLAMP(15, 18, 30) = " << CLAMP(15, 18, 30) << "   (atteso 18)" << std::endl;
    std::cout << "CLAMP(25, 18, 30) = " << CLAMP(25, 18, 30) << "   (atteso 25)" << std::endl;
    std::cout << "CLAMP(35, 18, 30) = " << CLAMP(35, 18, 30) << "   (atteso 30)" << std::endl;

    // 4) RIPETI
    std::cout << "RIPETI(3): ";
    RIPETI(3) std::cout << "ciao ";
    std::cout << "  (atteso: ciao ciao ciao)" << std::endl;

    // Uso combinato: media dei voti
    int somma = 0;
    for (unsigned int i = 0; i < ARRAY_SIZE(voti); i++) {
        somma += voti[i];
    }
    double media = static_cast<double>(somma) / ARRAY_SIZE(voti);
    LOG("Media calcolata: " << media);   // msg puo' contenere anche altri <<

    // 5) CONTROLLA: la prima passa in silenzio, la seconda stampa l'errore
    CONTROLLA(media >= 18, "la media deve essere sufficiente");
    CONTROLLA(media == 30, "la media non e' 30");

    // 7) getter generati dalla macro
    std::cout << "get_eta() = " << get_eta() << ", get_altezza() = " << get_altezza() << std::endl;

    LOG("Fine programma");
    return 0;
}
