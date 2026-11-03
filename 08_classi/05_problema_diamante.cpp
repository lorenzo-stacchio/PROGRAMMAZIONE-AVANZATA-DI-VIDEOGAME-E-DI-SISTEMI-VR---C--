// ARGOMENTO: ereditarieta' multipla e problema del diamante
//
// In C++ una classe puo' derivare da PIU' classi:  class C : public A, public B
//
// Il "diamante" nasce quando due classi derivano dalla stessa base
// e una quarta classe deriva da entrambe:
//
//              Dispositivo
//              /         \    .
//          Scanner     Stampante
//              \         /
//            Multifunzione
// (il punto serve: un \ a fine riga, anche in un commento, unisce la riga alla successiva)
//
// PROBLEMA: senza accorgimenti, Multifunzione contiene DUE copie di Dispositivo
// (una passando da Scanner, una da Stampante). Quindi:
//   - accedere a un membro di Dispositivo e' AMBIGUO (quale delle due copie?)
//   - i dati sono duplicati e possono andare fuori sincrono
//
// SOLUZIONE: EREDITARIETA' VIRTUALE  ->  class Scanner : virtual public Dispositivo
// Le classi che ereditano virtualmente condividono UNA SOLA copia della base.
// Regola: la base virtuale viene costruita direttamente dalla classe PIU' DERIVATA
// (Multifunzione), e le chiamate al suo costruttore fatte da Scanner/Stampante vengono ignorate.

#include <iostream>
#include <string>

// ============================================================
// VERSIONE 1: SENZA ereditarieta' virtuale (il problema)
// ============================================================
namespace senza_virtual {

class Dispositivo {
public:
    int id;
    Dispositivo(int id) : id(id) {
        std::cout << "  costruito Dispositivo con id " << id << std::endl;
    }
    void accendi() const {
        std::cout << "  Dispositivo " << id << " acceso" << std::endl;
    }
};

class Scanner : public Dispositivo {
public:
    Scanner() : Dispositivo(1) {}
    void scansiona() const { std::cout << "  Scansione in corso..." << std::endl; }
};

class Stampante : public Dispositivo {
public:
    Stampante() : Dispositivo(2) {}
    void stampa() const { std::cout << "  Stampa in corso..." << std::endl; }
};

class Multifunzione : public Scanner, public Stampante {
public:
    Multifunzione() {}   // costruisce Scanner (-> Dispositivo 1) e Stampante (-> Dispositivo 2)
};

} // namespace senza_virtual

// ============================================================
// VERSIONE 2: CON ereditarieta' virtuale (la soluzione)
// ============================================================
namespace con_virtual {

class Dispositivo {
public:
    int id;
    Dispositivo(int id) : id(id) {
        std::cout << "  costruito Dispositivo con id " << id << std::endl;
    }
    virtual ~Dispositivo() {}

    void accendi() const {
        std::cout << "  Dispositivo " << id << " acceso" << std::endl;
    }
    virtual void descrivi() const {
        std::cout << "  Dispositivo generico" << std::endl;
    }
};

class Scanner : virtual public Dispositivo {
public:
    Scanner() : Dispositivo(1) {}   // ignorato se Scanner fa parte di una Multifunzione
    void scansiona() const { std::cout << "  Scansione in corso..." << std::endl; }
    void descrivi() const override { std::cout << "  Sono uno scanner" << std::endl; }
};

class Stampante : virtual public Dispositivo {
public:
    Stampante() : Dispositivo(2) {}  // ignorato se Stampante fa parte di una Multifunzione
    void stampa() const { std::cout << "  Stampa in corso..." << std::endl; }
    void descrivi() const override { std::cout << "  Sono una stampante" << std::endl; }
};

class Multifunzione : public Scanner, public Stampante {
public:
    // La classe piu' derivata costruisce DIRETTAMENTE la base virtuale
    Multifunzione() : Dispositivo(3) {}

    // Scanner e Stampante ridefiniscono entrambe descrivi(): quale vale per Multifunzione?
    // E' ambiguo, quindi qui DOBBIAMO ridefinirlo (altrimenti errore di compilazione).
    void descrivi() const override {
        std::cout << "  Sono una multifunzione, cioe':" << std::endl;
        Scanner::descrivi();     // posso comunque richiamare le versioni dei genitori
        Stampante::descrivi();
    }
};

} // namespace con_virtual

int main()
{
    std::cout << "=== SENZA ereditarieta' virtuale ===" << std::endl;
    senza_virtual::Multifunzione m1;   // nota: Dispositivo viene costruito DUE volte

    // m1.accendi();   // ERRORE: "accendi" e' ambiguo (Scanner::Dispositivo o Stampante::Dispositivo?)
    // m1.id = 5;      // ERRORE: anche "id" e' ambiguo

    // Bisogna specificare il percorso:
    m1.Scanner::accendi();     // usa la copia di Dispositivo dentro Scanner   (id 1)
    m1.Stampante::accendi();   // usa la copia di Dispositivo dentro Stampante (id 2)
    m1.scansiona();
    m1.stampa();
    std::cout << "  -> due id diversi nello stesso oggetto: " << m1.Scanner::id
              << " e " << m1.Stampante::id << std::endl;

    std::cout << std::endl << "=== CON ereditarieta' virtuale ===" << std::endl;
    con_virtual::Multifunzione m2;     // Dispositivo costruito UNA sola volta, con id 3

    m2.accendi();              // nessuna ambiguita': c'e' una sola copia di Dispositivo
    m2.id = 42;                // anche l'accesso diretto funziona
    std::cout << "  id visto da Scanner: " << m2.Scanner::id
              << ", da Stampante: " << m2.Stampante::id << " (stessa variabile)" << std::endl;
    m2.scansiona();
    m2.stampa();

    std::cout << std::endl << "=== Polimorfismo con il diamante ===" << std::endl;
    con_virtual::Dispositivo* d = &m2;   // senza virtual questa conversione sarebbe ambigua
    d->descrivi();

    std::cout << std::endl << "sizeof senza virtual: " << sizeof(senza_virtual::Multifunzione)
              << " byte, con virtual: " << sizeof(con_virtual::Multifunzione)
              << " byte (l'ereditarieta' virtuale aggiunge puntatori interni)" << std::endl;

    return 0;
}
