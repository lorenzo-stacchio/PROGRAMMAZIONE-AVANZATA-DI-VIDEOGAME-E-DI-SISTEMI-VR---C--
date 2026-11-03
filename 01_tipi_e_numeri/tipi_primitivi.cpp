// ARGOMENTO: i tipi primitivi del C++ e come si usano
//
// - Interi:            short, int, long, long long (+ versioni unsigned)
// - Caratteri:         char (in realta' e' un piccolo intero)
// - Booleani:          bool (true / false)
// - Virgola mobile:    float, double, long double
// - Tipi a dimensione fissa: <cstdint> (int8_t, int32_t, uint64_t, ...)
// - sizeof, limiti dei tipi, letterali, conversioni, const/constexpr, auto
//
// Le dimensioni indicate nei commenti sono quelle tipiche su Windows 64 bit (MSVC):
// lo standard garantisce solo dei minimi, per questo esiste <cstdint>.

#include <iostream>
#include <limits>    // std::numeric_limits
#include <cstdint>   // int8_t, int32_t, uint64_t, ...
#include <iomanip>   // std::setprecision

int main()
{
    // ------------------------------------------------------------
    // 1) DICHIARAZIONE E INIZIALIZZAZIONE
    // ------------------------------------------------------------
    std::cout << "=== 1) Dichiarazione e inizializzazione ===" << std::endl;

    int a = 10;      // inizializzazione "classica" con =
    int b(20);       // inizializzazione con parentesi tonde
    int c{30};       // inizializzazione con graffe (consigliata da C++11)
    int d{};         // graffe vuote -> valore zero
    // int e;        // ATTENZIONE: variabile locale NON inizializzata, valore casuale!

    // Le graffe impediscono le conversioni con perdita di dati:
    // int f{3.7};   // ERRORE di compilazione (narrowing)
    int g = 3.7;     // compila, ma tronca a 3 (il compilatore da' un warning)

    std::cout << "a=" << a << " b=" << b << " c=" << c << " d=" << d << " g=" << g << std::endl;

    // ------------------------------------------------------------
    // 2) INTERI E LORO DIMENSIONI
    // ------------------------------------------------------------
    std::cout << std::endl << "=== 2) Interi: sizeof e limiti ===" << std::endl;

    // sizeof(tipo) restituisce la dimensione in BYTE (1 byte = 8 bit)
    std::cout << "short:     " << sizeof(short)     << " byte, da " << std::numeric_limits<short>::min()
              << " a " << std::numeric_limits<short>::max() << std::endl;
    std::cout << "int:       " << sizeof(int)       << " byte, da " << std::numeric_limits<int>::min()
              << " a " << std::numeric_limits<int>::max() << std::endl;
    std::cout << "long:      " << sizeof(long)      << " byte (su Windows uguale a int!)" << std::endl;
    std::cout << "long long: " << sizeof(long long) << " byte, max " << std::numeric_limits<long long>::max() << std::endl;

    // unsigned: niente numeri negativi, ma il doppio dei positivi
    std::cout << "unsigned int: da " << std::numeric_limits<unsigned int>::min()
              << " a " << std::numeric_limits<unsigned int>::max() << std::endl;

    // ------------------------------------------------------------
    // 3) TIPI A DIMENSIONE FISSA (<cstdint>)
    // ------------------------------------------------------------
    std::cout << std::endl << "=== 3) Tipi a dimensione fissa ===" << std::endl;

    int8_t   piccolo = 100;          // esattamente 8 bit con segno  (-128 .. 127)
    uint8_t  byte    = 255;          // esattamente 8 bit senza segno (0 .. 255)
    int32_t  medio   = 2000000000;   // esattamente 32 bit
    uint64_t grande  = 18000000000000000000ULL; // esattamente 64 bit senza segno

    // int8_t/uint8_t sono in realta' char: per stamparli come numeri serve un cast
    std::cout << "int8_t:   " << static_cast<int>(piccolo) << std::endl;
    std::cout << "uint8_t:  " << static_cast<int>(byte)    << std::endl;
    std::cout << "int32_t:  " << medio  << std::endl;
    std::cout << "uint64_t: " << grande << std::endl;

    // ------------------------------------------------------------
    // 4) LETTERALI: come scrivere i numeri nel codice
    // ------------------------------------------------------------
    std::cout << std::endl << "=== 4) Letterali ===" << std::endl;

    int decimale    = 255;
    int esadecimale = 0xFF;          // prefisso 0x -> base 16
    int ottale      = 0377;          // prefisso 0  -> base 8 (attenzione: 010 vale 8!)
    int binario     = 0b11111111;    // prefisso 0b -> base 2 (C++14)
    int milione     = 1'000'000;     // l'apostrofo separa le cifre (C++14), solo estetico

    std::cout << decimale << " " << esadecimale << " " << ottale << " " << binario
              << " (sono tutti 255)" << std::endl;
    std::cout << "milione = " << milione << std::endl;

    // Suffissi: indicano il tipo del letterale
    auto l1 = 10u;     // unsigned int
    auto l2 = 10LL;    // long long
    auto l3 = 3.14f;   // float  (senza f sarebbe double)
    auto l4 = 3.14;    // double
    auto l5 = 1.5e3;   // notazione scientifica: 1.5 * 10^3 = 1500.0
    std::cout << "sizeof(10u)=" << sizeof(l1) << " sizeof(10LL)=" << sizeof(l2)
              << " sizeof(3.14f)=" << sizeof(l3) << " sizeof(3.14)=" << sizeof(l4)
              << " 1.5e3=" << l5 << std::endl;

    // ------------------------------------------------------------
    // 5) OPERAZIONI ARITMETICHE SUGLI INTERI
    // ------------------------------------------------------------
    std::cout << std::endl << "=== 5) Aritmetica intera ===" << std::endl;

    int x = 17, y = 5;
    std::cout << "17 + 5 = " << x + y << std::endl;
    std::cout << "17 - 5 = " << x - y << std::endl;
    std::cout << "17 * 5 = " << x * y << std::endl;
    std::cout << "17 / 5 = " << x / y << "   <- divisione INTERA: la parte decimale si perde" << std::endl;
    std::cout << "17 % 5 = " << x % y << "   <- modulo: il resto della divisione" << std::endl;
    std::cout << "17.0 / 5 = " << 17.0 / y << " <- se uno dei due e' double, la divisione e' decimale" << std::endl;

    // Operatori composti e incremento
    int n = 10;
    n += 5;   // n = n + 5  -> 15
    n *= 2;   // n = n * 2  -> 30
    n -= 4;   // n = n - 4  -> 26
    n /= 2;   // n = n / 2  -> 13
    std::cout << "n dopo += *= -= /= : " << n << std::endl;

    int i = 5;
    std::cout << "i++ restituisce " << i++ << " (poi i vale " << i << ")" << std::endl; // post-incremento
    std::cout << "++i restituisce " << ++i << " (prima incrementa)" << std::endl;       // pre-incremento

    // ------------------------------------------------------------
    // 6) OVERFLOW
    // ------------------------------------------------------------
    std::cout << std::endl << "=== 6) Overflow ===" << std::endl;

    // Unsigned: superato il massimo si riparte da 0 (comportamento definito, "wrap around")
    unsigned int u = std::numeric_limits<unsigned int>::max();
    u = u + 1;
    std::cout << "max unsigned + 1 = " << u << std::endl;

    unsigned int zero = 0;
    zero = zero - 1;
    std::cout << "0u - 1 = " << zero << "   <- attenzione nei cicli con unsigned!" << std::endl;

    // Signed: l'overflow e' "undefined behavior" (il programma puo' fare qualsiasi cosa),
    // quindi NON va mai provocato. Soluzione: usare un tipo piu' grande.
    int grandeInt = 2000000000;
    long long prodotto = static_cast<long long>(grandeInt) * 2; // converto PRIMA di moltiplicare
    std::cout << "2'000'000'000 * 2 in long long = " << prodotto << std::endl;

    // ------------------------------------------------------------
    // 7) VIRGOLA MOBILE: float, double, long double
    // ------------------------------------------------------------
    std::cout << std::endl << "=== 7) Virgola mobile ===" << std::endl;

    float  pf = 1.0f / 3.0f;   // ~7 cifre significative, 4 byte
    double pd = 1.0  / 3.0;    // ~15-16 cifre significative, 8 byte (il piu' usato)
    long double pl = 1.0L / 3.0L; // su MSVC e' uguale a double

    std::cout << std::setprecision(20);  // mostro piu' cifre del normale
    std::cout << "float:       " << pf << " (" << sizeof(float)  << " byte)" << std::endl;
    std::cout << "double:      " << pd << " (" << sizeof(double) << " byte)" << std::endl;
    std::cout << "long double: " << pl << " (" << sizeof(long double) << " byte)" << std::endl;

    // I decimali non sono rappresentati esattamente in binario
    double somma = 0.1 + 0.2;
    std::cout << "0.1 + 0.2 = " << somma << std::endl;
    std::cout << "0.1 + 0.2 == 0.3 ? " << std::boolalpha << (somma == 0.3) << std::endl;
    std::cout << std::setprecision(6);   // torno alla precisione di default
    // -> per confrontare i double usare una tolleranza (vedi confronto_float_nan.cpp)

    // Valori speciali
    double infinito = std::numeric_limits<double>::infinity();
    double nan      = std::numeric_limits<double>::quiet_NaN();
    std::cout << "infinito = " << infinito << ", NaN = " << nan << std::endl;

    // ------------------------------------------------------------
    // 8) CHAR: un carattere e' un numero
    // ------------------------------------------------------------
    std::cout << std::endl << "=== 8) char ===" << std::endl;

    char lettera = 'A';                      // apici singoli per un carattere
    std::cout << "lettera = " << lettera << ", codice ASCII = " << static_cast<int>(lettera) << std::endl;

    char successiva = lettera + 1;           // aritmetica sui caratteri
    std::cout << "'A' + 1 = " << successiva << std::endl;

    char cifra = '7';
    int valoreCifra = cifra - '0';           // trucco classico: da carattere a numero
    std::cout << "'7' - '0' = " << valoreCifra << std::endl;

    // Caratteri speciali (sequenze di escape)
    std::cout << "Tab:\t|  Virgolette: \"  Backslash: \\  Apice: \'" << std::endl;

    // ------------------------------------------------------------
    // 9) BOOL
    // ------------------------------------------------------------
    std::cout << std::endl << "=== 9) bool ===" << std::endl;

    bool vero = true;
    bool falso = false;
    std::cout << std::noboolalpha << "senza boolalpha: " << vero << " " << falso << std::endl;
    std::cout << std::boolalpha   << "con boolalpha:   " << vero << " " << falso << std::endl;

    // Qualsiasi numero diverso da 0 diventa true
    bool daNumero = 42;   // il compilatore avvisa del troncamento (warning voluto)
    bool daZero = 0;
    std::cout << "bool(42) = " << daNumero << ", bool(0) = " << daZero << std::endl;

    // Operatori logici e di confronto
    std::cout << "5 > 3 && 2 > 4 : " << (5 > 3 && 2 > 4) << "  (AND)" << std::endl;
    std::cout << "5 > 3 || 2 > 4 : " << (5 > 3 || 2 > 4) << "  (OR)" << std::endl;
    std::cout << "!(5 > 3)       : " << !(5 > 3) << " (NOT)" << std::endl;

    // ------------------------------------------------------------
    // 10) CONVERSIONI TRA TIPI (cast)
    // ------------------------------------------------------------
    std::cout << std::endl << "=== 10) Conversioni ===" << std::endl;

    // Implicita: il compilatore converte da solo
    double dd = 7;            // int -> double: nessuna perdita
    int    ii = 7.9;          // double -> int: TRONCA (non arrotonda!) -> 7  (warning voluto)
    std::cout << "double dd = 7 -> " << dd << ";  int ii = 7.9 -> " << ii << std::endl;

    // Esplicita con static_cast (il modo consigliato in C++)
    int totale = 7, quanti = 2;
    double media = static_cast<double>(totale) / quanti;  // 3.5 invece di 3
    std::cout << "media = " << media << std::endl;

    // Cast in stile C: funziona ma e' meno sicuro e meno leggibile
    double mediaC = (double)totale / quanti;
    std::cout << "mediaC = " << mediaC << std::endl;

    // Mescolare signed e unsigned e' pericoloso: -1 diventa un numero enorme
    int negativo = -1;
    unsigned int positivo = 1;
    std::cout << "-1 < 1u ? " << (negativo < static_cast<int>(positivo)) << " (con cast corretto)" << std::endl;
    std::cout << "-1 convertito in unsigned = " << static_cast<unsigned int>(negativo) << std::endl;

    // ------------------------------------------------------------
    // 11) CONST, CONSTEXPR E AUTO
    // ------------------------------------------------------------
    std::cout << std::endl << "=== 11) const, constexpr, auto ===" << std::endl;

    const int giorniSettimana = 7;          // non modificabile dopo l'inizializzazione
    // giorniSettimana = 8;                 // ERRORE di compilazione
    constexpr double PI = 3.14159265358979; // costante calcolata a tempo di COMPILAZIONE
    constexpr int secondiInUnGiorno = 24 * 60 * 60; // calcolato dal compilatore

    std::cout << "giorni = " << giorniSettimana << ", PI = " << PI
              << ", secondi in un giorno = " << secondiInUnGiorno << std::endl;

    // auto: il tipo viene dedotto dal valore assegnato
    auto intero = 42;       // int
    auto reale = 42.0;      // double
    auto carattere = 'x';   // char
    auto booleano = true;   // bool
    std::cout << "auto: " << intero << " " << reale << " " << carattere << " " << booleano << std::endl;

    return 0;
}
