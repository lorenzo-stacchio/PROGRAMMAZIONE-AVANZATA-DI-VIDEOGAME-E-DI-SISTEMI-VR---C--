// ARGOMENTO: template (i "generics" del C++) e polimorfismo parametrico
//
// POLIMORFISMO PARAMETRICO = scrivere UNA volta del codice che funziona con
// MOLTI tipi, lasciando il tipo come PARAMETRO. In C++ si fa con i TEMPLATE:
//
//     template <typename T>
//     T massimo(T a, T b) { return (a > b) ? a : b; }
//
// T e' un segnaposto: quando scrivo massimo(3, 7) il compilatore GENERA una
// versione con T = int; con massimo(2.5, 1.0) ne genera un'altra con T = double.
// Questo si chiama ISTANZIAZIONE e avviene a TEMPO DI COMPILAZIONE.
//
// Differenza con i generics di Java/C#:
//   - in Java esiste UNA sola versione del codice e il tipo viene "cancellato"
//     (type erasure): funziona solo con oggetti, non con int/double.
//   - in C++ ogni tipo usato produce una COPIA del codice, specializzata per
//     quel tipo: nessun costo a runtime, funziona anche con i tipi primitivi,
//     ma l'eseguibile cresce (code bloat) e gli errori sono piu' lunghi da leggere.
//
// Due polimorfismi a confronto (vedi 04_ereditarieta_overriding.cpp):
//   - polimorfismo per SOTTOTIPO (virtual): i tipi devono avere una base comune,
//     la funzione si sceglie a RUNTIME tramite la vtable.
//   - polimorfismo PARAMETRICO (template): i tipi NON devono avere nulla in comune,
//     basta che supportino le operazioni usate nel codice (es. l'operatore >).
//     Tutto viene deciso a COMPILAZIONE.
//
// Compila con il C++14 di default di MSVC. La sezione finale cita i "concepts"
// del C++20, che servono a rendere espliciti i requisiti sul tipo T.

#include <iostream>
#include <string>
#include <vector>
#include <type_traits>   // std::is_arithmetic, usato con static_assert

// ---------------------------------------------------------------------------
// 1. TEMPLATE DI FUNZIONE
// ---------------------------------------------------------------------------

// "typename" e "class" qui sono sinonimi: template <class T> e' identico.
template <typename T>
T massimo(T a, T b) {
    return (a > b) ? a : b;
}

// Piu' parametri di tipo: T e U possono essere diversi
template <typename T, typename U>
void stampaCoppia(const T& primo, const U& secondo) {
    std::cout << "(" << primo << ", " << secondo << ")" << std::endl;
}

// Un template funziona con QUALSIASI contenitore che abbia begin()/end()
// e con qualsiasi elemento che supporti +=. Nessuna classe base richiesta.
template <typename Contenitore>
void stampaTutti(const Contenitore& c) {
    std::cout << "[ ";
    for (const auto& elem : c) {
        std::cout << elem << " ";
    }
    std::cout << "]" << std::endl;
}

// static_assert: blocco la compilazione con un messaggio CHIARO se il tipo
// non e' adatto, invece di un errore illeggibile dentro il template.
template <typename T>
double media(const std::vector<T>& valori) {
    static_assert(std::is_arithmetic<T>::value, "media() richiede un tipo numerico");
    if (valori.empty()) return 0.0;
    double somma = 0.0;
    for (const T& v : valori) somma += v;
    return somma / valori.size();
}

// ---------------------------------------------------------------------------
// 2. TEMPLATE DI CLASSE
// ---------------------------------------------------------------------------

// Una scatola che contiene un valore di tipo qualsiasi
template <typename T>
class Scatola {
private:
    T contenuto;

public:
    explicit Scatola(const T& valore) : contenuto(valore) {}

    const T& apri() const { return contenuto; }
    void sostituisci(const T& nuovo) { contenuto = nuovo; }

    void descrivi() const {
        std::cout << "  Scatola che contiene: " << contenuto << std::endl;
    }
};

// Parametri NON di tipo: oltre ai tipi si possono passare COSTANTI note a
// compilazione (qui la capacita'). Pila<int, 3> e Pila<int, 5> sono tipi DIVERSI.
// Il secondo parametro ha un valore di default.
template <typename T, int CAPACITA = 4>
class Pila {
private:
    T elementi[CAPACITA];   // array a dimensione fissa: niente new/delete
    int quanti = 0;

public:
    bool push(const T& valore) {
        if (quanti == CAPACITA) {
            std::cout << "  push(" << valore << ") rifiutato: pila piena" << std::endl;
            return false;
        }
        elementi[quanti++] = valore;
        return true;
    }

    // Restituisce false se la pila e' vuota, altrimenti mette in "out" la cima
    bool pop(T& out) {
        if (quanti == 0) return false;
        out = elementi[--quanti];
        return true;
    }

    int dimensione() const { return quanti; }
    static int capacita() { return CAPACITA; }
};

// Due parametri di tipo, come std::pair o la coppia chiave/valore di std::map
template <typename K, typename V>
struct Coppia {
    K chiave;
    V valore;
};

// Un template di funzione che lavora su un template di classe
template <typename K, typename V>
std::ostream& operator<<(std::ostream& os, const Coppia<K, V>& c) {
    os << c.chiave << " -> " << c.valore;
    return os;
}

// ---------------------------------------------------------------------------
// 3. SPECIALIZZAZIONE: un comportamento diverso per tipi particolari
// ---------------------------------------------------------------------------

// Template "generico"
template <typename T>
class Descrittore {
public:
    static std::string descrivi(const T&) { return "un valore generico"; }
};

// SPECIALIZZAZIONE TOTALE: per T = bool scrivo una versione apposita
template <>
class Descrittore<bool> {
public:
    static std::string descrivi(const bool& b) { return b ? "vero" : "falso"; }
};

// SPECIALIZZAZIONE PARZIALE: per QUALSIASI puntatore T*
// (possibile solo con i template di classe, non con quelli di funzione)
template <typename T>
class Descrittore<T*> {
public:
    static std::string descrivi(T* const& p) {
        return p ? "un puntatore valido" : "un puntatore nullo";
    }
};

// ---------------------------------------------------------------------------
// 4. TEMPLATE VARIADICI: un numero qualsiasi di argomenti, di tipi qualsiasi
// ---------------------------------------------------------------------------

// Caso base della "ricorsione" (vedi 05_ricorsione): un solo argomento
template <typename T>
T sommaTutti(T ultimo) {
    return ultimo;
}

// Caso generale: prendo il primo, sommo il resto. "Resto..." e' un PACK di tipi.
// Ogni chiamata e' una funzione DIVERSA generata a compilazione: non c'e'
// vera ricorsione a runtime.
template <typename T, typename... Resto>
T sommaTutti(T primo, Resto... resto) {
    return primo + sommaTutti(resto...);
}

// ---------------------------------------------------------------------------
// Un tipo nostro, per mostrare che i template funzionano anche con le classi
// ---------------------------------------------------------------------------

struct Punteggio {
    std::string giocatore;
    int punti;

    // massimo() usa ">": basta definirlo e Punteggio diventa "compatibile"
    bool operator>(const Punteggio& altro) const { return punti > altro.punti; }
};

std::ostream& operator<<(std::ostream& os, const Punteggio& p) {
    os << p.giocatore << " (" << p.punti << ")";
    return os;
}

struct SenzaConfronto {
    int x;
};

int main()
{
    std::cout << "=== 1. Template di funzione ===" << std::endl;
    std::cout << "massimo(3, 7)          = " << massimo(3, 7) << std::endl;          // T = int
    std::cout << "massimo(2.5, 1.0)      = " << massimo(2.5, 1.0) << std::endl;      // T = double
    std::cout << "massimo('a', 'z')      = " << massimo('a', 'z') << std::endl;      // T = char
    std::cout << "massimo<string>(...)   = "
              << massimo<std::string>("mela", "pera") << std::endl;                  // T esplicito

    // massimo(3, 4.5);           // ERRORE: T dedotto sia come int sia come double
    std::cout << "massimo<double>(3, 4.5) = " << massimo<double>(3, 4.5) << std::endl; // soluzione: T esplicito

    Punteggio anna{"Anna", 1200};
    Punteggio luca{"Luca", 950};
    std::cout << "massimo(anna, luca)    = " << massimo(anna, luca) << std::endl;    // T = Punteggio

    SenzaConfronto s1{1}, s2{2};
    (void)s1; (void)s2;
    // massimo(s1, s2);           // ERRORE: SenzaConfronto non ha operator>
    // Il template impone REQUISITI IMPLICITI sul tipo: scoperti solo all'istanziazione.

    std::cout << std::endl;
    stampaCoppia(1, "uno");
    stampaCoppia(3.14, 'p');
    stampaCoppia(std::string("vite"), 3);

    std::vector<int> numeri = {4, 8, 15, 16, 23, 42};
    std::vector<std::string> armi = {"spada", "arco", "bastone"};
    stampaTutti(numeri);
    stampaTutti(armi);
    std::cout << "media(numeri) = " << media(numeri) << std::endl;
    // media(armi);               // ERRORE: "media() richiede un tipo numerico" (static_assert)

    std::cout << std::endl << "=== 2. Template di classe ===" << std::endl;
    // Per le classi in C++14 il tipo va scritto tra < > (dal C++17 puo' essere dedotto)
    Scatola<int> scatolaNumero(42);
    Scatola<std::string> scatolaTesto("pozione");
    Scatola<Punteggio> scatolaPunteggio(anna);
    scatolaNumero.descrivi();
    scatolaTesto.descrivi();
    scatolaPunteggio.descrivi();
    scatolaTesto.sostituisci("elisir");
    std::cout << "  dopo sostituisci: " << scatolaTesto.apri() << std::endl;

    // Scatola<int> e Scatola<std::string> sono due CLASSI DIVERSE, senza relazione:
    // scatolaNumero = scatolaTesto;   // ERRORE: tipi incompatibili

    std::cout << std::endl;
    Pila<std::string, 3> inventario;   // capacita' 3
    inventario.push("spada");
    inventario.push("scudo");
    inventario.push("mappa");
    inventario.push("torcia");         // rifiutato
    std::cout << "  inventario: " << inventario.dimensione()
              << "/" << Pila<std::string, 3>::capacita() << std::endl;
    std::string oggetto;
    while (inventario.pop(oggetto)) {
        std::cout << "  pop -> " << oggetto << std::endl;   // esce in ordine inverso (LIFO)
    }

    Pila<double> pilaDefault;          // CAPACITA usa il default (4)
    std::cout << "  Pila<double> ha capacita' di default " << pilaDefault.capacita() << std::endl;

    std::cout << std::endl;
    Coppia<std::string, int> livello{"livello", 3};
    Coppia<int, double> moltiplicatore{2, 1.5};
    std::cout << "  " << livello << std::endl;
    std::cout << "  " << moltiplicatore << std::endl;

    std::cout << std::endl << "=== 3. Specializzazione ===" << std::endl;
    int vite = 3;
    int* puntatore = &vite;
    int* nullo = nullptr;
    std::cout << "  42      e' " << Descrittore<int>::descrivi(42) << std::endl;           // generico
    std::cout << "  true    e' " << Descrittore<bool>::descrivi(true) << std::endl;        // totale
    std::cout << "  &vite   e' " << Descrittore<int*>::descrivi(puntatore) << std::endl;   // parziale
    std::cout << "  nullptr e' " << Descrittore<int*>::descrivi(nullo) << std::endl;       // parziale

    std::cout << std::endl << "=== 4. Template variadici ===" << std::endl;
    std::cout << "  sommaTutti(1, 2, 3, 4)        = " << sommaTutti(1, 2, 3, 4) << std::endl;
    std::cout << "  sommaTutti(0.5, 0.25, 0.125)  = " << sommaTutti(0.5, 0.25, 0.125) << std::endl;
    std::string a = "fuoco", b = "+", c = "ghiaccio";
    std::cout << "  sommaTutti(a, b, c)           = " << sommaTutti(a, b, c) << std::endl;

    // sommaTutti(std::string("a"), "b", "c");   // ERRORE: "impossibile aggiungere due puntatori"
    // La somma parte dal FONDO: prima "b" + "c", cioe' const char* + const char*.
    // Il template si istanzia con i tipi VERI degli argomenti, non con quelli che "intendevi".

    // NOTA: i template vanno DEFINITI (non solo dichiarati) dove vengono usati,
    // perche' il compilatore deve vederne il corpo per generare il codice.
    // Per questo, in un progetto vero, stanno interamente nei file .h.
    //
    // NOTA (C++20): i "concepts" rendono espliciti i requisiti su T, ad esempio
    //     template <std::totally_ordered T> T massimo(T a, T b);
    // e l'errore su SenzaConfronto direbbe subito "vincolo non soddisfatto".
    // Per provarli serve /std:c++20.

    return 0;
}
