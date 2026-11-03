// ARGOMENTO: le macro e il preprocessore
//
// Prima della compilazione vera e propria, il PREPROCESSORE legge le righe che
// iniziano con # e fa delle semplici SOSTITUZIONI DI TESTO:
//   #include  -> copia il contenuto di un file
//   #define   -> definisce una macro (un "trova e sostituisci")
//   #ifdef / #ifndef / #if / #else / #endif -> compilazione condizionale
//   #undef    -> cancella una macro
//
// Il preprocessore NON conosce il C++: non sa cosa sono tipi, variabili o funzioni.
// Per questo le macro sono potenti ma pericolose. In C++ moderno si preferiscono
// const/constexpr, funzioni inline e template; le macro restano utili per
// compilazione condizionale, include guard e messaggi con file/riga.

#include <iostream>
#include <cstdio>   // printf, usato nella macro variadica

#include "matematica.h"
#include "matematica.h"   // incluso DUE volte apposta: l'include guard evita errori

// ------------------------------------------------------------
// 1) MACRO "OGGETTO": una costante testuale
// ------------------------------------------------------------
#define PI 3.14159
#define SALUTO "Ciao dal preprocessore"
#define DIMENSIONE 5

// ------------------------------------------------------------
// 2) MACRO "FUNZIONE": con parametri
// ------------------------------------------------------------
// SBAGLIATA: senza parentesi la sostituzione rompe le precedenze
#define QUADRATO_SBAGLIATO(x) x * x
// MEZZA GIUSTA: parentesi sui parametri, ma non su tutta l'espressione
#define QUADRATO_MEZZO(x) (x) * (x)
// GIUSTA: parentesi su ogni parametro E sull'intera espressione
#define QUADRATO(x) ((x) * (x))

#define MAX(a, b) ((a) > (b) ? (a) : (b))

// ------------------------------------------------------------
// 3) OPERATORI SPECIALI: # (stringify) e ## (concatenazione)
// ------------------------------------------------------------
#define STRINGA(x) #x                 // trasforma il parametro in una stringa "x"
#define CONCATENA(a, b) a##b          // incolla due pezzi in un unico nome
#define STAMPA_VAR(v) std::cout << #v << " = " << (v) << std::endl

// ------------------------------------------------------------
// 4) MACRO SU PIU' RIGHE e il trucco do { ... } while (0)
// ------------------------------------------------------------
// Il backslash \ alla fine della riga continua la macro sulla riga successiva.
// do { } while (0) fa comportare la macro come UNA singola istruzione
// (funziona correttamente anche dentro un if senza graffe).
#define SCAMBIA(a, b)        \
    do {                     \
        auto tmp_ = (a);     \
        (a) = (b);           \
        (b) = tmp_;          \
    } while (0)

// ------------------------------------------------------------
// 5) MACRO VARIADICA: numero variabile di argomenti (...)
// ------------------------------------------------------------
// __VA_ARGS__ viene sostituito con tutti gli argomenti passati al posto di ...
#define STAMPA_FORMATTATO(formato, ...) std::printf(formato, __VA_ARGS__)

// ------------------------------------------------------------
// 6) COMPILAZIONE CONDIZIONALE
// ------------------------------------------------------------
// Prova a commentare questa riga: i messaggi di debug spariscono dal programma.
#define MODALITA_DEBUG

#ifdef MODALITA_DEBUG
    #define DEBUG_LOG(msg) std::cout << "[DEBUG riga " << __LINE__ << "] " << msg << std::endl
#else
    #define DEBUG_LOG(msg)   // si espande nel nulla: nessun costo nel programma finale
#endif

#define VERSIONE 2

int main()
{
    std::cout << "=== 1) Macro oggetto ===" << std::endl;
    // Il compilatore non vede mai PI: vede direttamente 3.14159
    double raggio = 2.0;
    std::cout << SALUTO << std::endl;
    std::cout << "Area cerchio di raggio 2 = " << PI * raggio * raggio << std::endl;
    int numeri[DIMENSIONE] = {1, 2, 3, 4, 5};   // diventa: int numeri[5]
    std::cout << "Ultimo elemento: " << numeri[DIMENSIONE - 1] << std::endl;

    std::cout << std::endl << "=== 2) Macro funzione e il problema delle parentesi ===" << std::endl;
    // QUADRATO_SBAGLIATO(2 + 3) diventa: 2 + 3 * 2 + 3 = 11  (non 25!)
    std::cout << "QUADRATO_SBAGLIATO(2 + 3) = " << QUADRATO_SBAGLIATO(2 + 3) << std::endl;
    // 100 / QUADRATO_MEZZO(5) diventa: 100 / (5) * (5) = 100  (non 4!)
    std::cout << "100 / QUADRATO_MEZZO(5)   = " << 100 / QUADRATO_MEZZO(5) << std::endl;
    // 100 / QUADRATO(5) diventa: 100 / ((5) * (5)) = 4  -> corretto
    std::cout << "QUADRATO(2 + 3)           = " << QUADRATO(2 + 3) << std::endl;
    std::cout << "100 / QUADRATO(5)         = " << 100 / QUADRATO(5) << std::endl;

    // Altro problema: i parametri possono essere valutati PIU' VOLTE
    int i = 5;
    int risultato = MAX(i++, 0);   // diventa: ((i++) > (0) ? (i++) : (0)) -> i++ eseguito 2 volte!
    std::cout << "MAX(i++, 0) = " << risultato << ", ma ora i vale " << i << " (non 6!)" << std::endl;

    // Dall'header matematica.h
    std::cout << "CUBO(3) = " << CUBO(3) << ", cubo(3) = " << cubo(3) << std::endl;

    std::cout << std::endl << "=== 3) Operatori # e ## ===" << std::endl;
    std::cout << STRINGA(ciao mondo) << std::endl;      // diventa: "ciao mondo"
    std::cout << STRINGA(1 + 2) << std::endl;           // diventa: "1 + 2" (non calcola!)

    int CONCATENA(valore, 1) = 10;   // diventa: int valore1 = 10;
    int CONCATENA(valore, 2) = 20;   // diventa: int valore2 = 20;
    STAMPA_VAR(valore1);             // stampa il NOME della variabile e il suo valore
    STAMPA_VAR(valore2);
    STAMPA_VAR(valore1 + valore2);

    std::cout << std::endl << "=== 4) Macro su piu' righe ===" << std::endl;
    int a = 1, b = 2;
    if (a < b)
        SCAMBIA(a, b);   // grazie a do/while(0) funziona anche senza graffe
    else
        std::cout << "niente da scambiare" << std::endl;
    std::cout << "dopo SCAMBIA: a = " << a << ", b = " << b << std::endl;

    std::cout << std::endl << "=== 5) Macro variadica ===" << std::endl;
    STAMPA_FORMATTATO("%s ha %d anni e %.1f di media\n", "Marco", 21, 27.5);

    std::cout << std::endl << "=== 6) Compilazione condizionale ===" << std::endl;
    DEBUG_LOG("questo messaggio esiste solo se MODALITA_DEBUG e' definita");

#if VERSIONE >= 2
    std::cout << "Compilato con VERSIONE >= 2" << std::endl;
#else
    std::cout << "Compilato con una versione vecchia" << std::endl;
#endif

    // Macro definite dal sistema: utili per scrivere codice per piu' piattaforme
#ifdef _WIN32
    std::cout << "Sistema: Windows" << std::endl;
#elif defined(__linux__)
    std::cout << "Sistema: Linux" << std::endl;
#else
    std::cout << "Sistema: altro" << std::endl;
#endif

#ifdef _MSC_VER
    std::cout << "Compilatore: MSVC versione " << _MSC_VER << std::endl;
#endif

    std::cout << std::endl << "=== 7) Macro predefinite ===" << std::endl;
    std::cout << "__FILE__ = " << __FILE__ << std::endl;   // file sorgente corrente
    std::cout << "__LINE__ = " << __LINE__ << std::endl;   // riga corrente
    std::cout << "__DATE__ = " << __DATE__ << std::endl;   // data di compilazione
    std::cout << "__TIME__ = " << __TIME__ << std::endl;   // ora di compilazione
    std::cout << "__func__ = " << __func__ << std::endl;   // nome della funzione (non e' una macro, ma e' simile)
    // NOTA: su MSVC __cplusplus vale 199711 a meno di compilare con /Zc:__cplusplus
    std::cout << "__cplusplus = " << __cplusplus << std::endl;

    std::cout << std::endl << "=== 8) #undef ===" << std::endl;
#undef PI
    // Da qui PI non esiste piu': std::cout << PI;  -> ERRORE di compilazione
    // L'alternativa C++ ha un tipo e rispetta gli scope:
    constexpr double PI = 3.14159265358979;
    std::cout << "constexpr PI = " << PI << std::endl;

    return 0;
}
