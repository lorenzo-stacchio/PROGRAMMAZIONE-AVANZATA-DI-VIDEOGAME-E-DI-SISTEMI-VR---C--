// ESERCIZIO: Cane, Gatto e Chimera (classi, ereditarieta', overriding, overloading, diamante)
//
// TRACCIA
// 1) Crea la classe ASTRATTA Animale con:
//    - attributi protected: nome, eta
//    - un contatore static degli animali attualmente vivi (+1 nel costruttore, -1 nel distruttore)
//    - costruttore con lista di inizializzazione e distruttore VIRTUALE
//    - metodi virtuali PURI: verso() e specie()
//    - metodo virtuale presentati() che usa verso() e specie()
//    - metodo mangia() in OVERLOADING: mangia(), mangia(cibo), mangia(cibo, grammi)
// 2) Crea Cane e Gatto che ereditano VIRTUALMENTE da Animale:
//    - Cane ha l'attributo razza e il metodo riportaPallina()
//    - Gatto ha l'attributo vite (parte da 7) e il metodo faLeFusa()
//    - entrambi fanno l'OVERRIDE di verso() e specie()
// 3) Crea Chimera, che eredita sia da Cane sia da Gatto (problema del diamante!):
//    - deve costruire direttamente Animale
//    - verso() combina i versi dei genitori
//    - presentati() ridefinito aggiungendo una frase propria
//    - metodo trasformati() che usa i metodi di ENTRAMBI i genitori
// 4) Scrivi operator<< per stampare un Animale con cout.
// 5) Nel main: metti gli animali in un array di Animale*, falli presentare tutti,
//    usa dynamic_cast per capire chi sa riportare la pallina, poi libera la memoria
//    e controlla che il contatore torni a 0.
//
// SOLUZIONE (sotto)
//
//              Animale  (astratta)
//              /      \          <- ereditarieta' virtuale
//           Cane      Gatto
//              \      /
//              Chimera

#include <iostream>
#include <string>

// ============================================================
// 1) Classe base astratta
// ============================================================
class Animale {
protected:
    std::string nome;
    int eta;

private:
    static int animaliVivi;

public:
    Animale(const std::string& nome, int eta) : nome(nome), eta(eta) {
        animaliVivi++;
    }

    // virtual: indispensabile perche' facciamo delete tramite Animale*
    virtual ~Animale() {
        animaliVivi--;
        std::cout << "  (" << nome << " se ne va)" << std::endl;
    }

    // Metodi virtuali puri: Animale e' astratta
    virtual std::string verso() const = 0;
    virtual std::string specie() const = 0;

    virtual void presentati() const {
        std::cout << "Sono " << nome << ", " << specie() << " di " << eta
                  << " anni, e faccio \"" << verso() << "\"" << std::endl;
    }

    // Overloading: stesso nome, parametri diversi
    void mangia() const {
        std::cout << nome << " mangia qualcosa a caso" << std::endl;
    }
    void mangia(const std::string& cibo) const {
        std::cout << nome << " mangia " << cibo << std::endl;
    }
    void mangia(const std::string& cibo, int grammi) const {
        std::cout << nome << " mangia " << grammi << "g di " << cibo << std::endl;
    }

    const std::string& getNome() const { return nome; }
    static int getAnimaliVivi() { return animaliVivi; }
};

int Animale::animaliVivi = 0;

// 4) operator<< : grazie a specie() virtuale stampa il tipo giusto
std::ostream& operator<<(std::ostream& os, const Animale& a) {
    os << "[" << a.specie() << " " << a.getNome() << "]";
    return os;
}

// ============================================================
// 2) Cane e Gatto: ereditarieta' VIRTUALE da Animale
// ============================================================
class Cane : virtual public Animale {
protected:
    std::string razza;

public:
    Cane(const std::string& nome, int eta, const std::string& razza)
        : Animale(nome, eta), razza(razza) {}

    std::string verso() const override { return "Bau"; }
    std::string specie() const override { return "cane (" + razza + ")"; }

    void riportaPallina() const {
        std::cout << nome << " corre e riporta la pallina!" << std::endl;
    }
};

class Gatto : virtual public Animale {
protected:
    int vite = 7;

public:
    Gatto(const std::string& nome, int eta) : Animale(nome, eta) {}

    std::string verso() const override { return "Miao"; }
    std::string specie() const override { return "gatto"; }

    void faLeFusa() const {
        std::cout << nome << " fa le fusa... (vite rimaste: " << vite << ")" << std::endl;
    }
};

// ============================================================
// 3) Chimera: il diamante
// ============================================================
class Chimera : public Cane, public Gatto {
public:
    // Con l'ereditarieta' virtuale e' la classe PIU' DERIVATA a costruire Animale.
    // Le chiamate Animale(...) dentro i costruttori di Cane e Gatto vengono ignorate,
    // quindi esiste UN solo nome e UNA sola eta (e il contatore sale di 1, non di 2).
    Chimera(const std::string& nome, int eta)
        : Animale(nome, eta), Cane(nome, eta, "misto"), Gatto(nome, eta) {}

    // Cane e Gatto ridefiniscono entrambi verso() e specie(): per evitare
    // l'ambiguita' Chimera DEVE ridefinirli. Posso pero' riusare i genitori.
    std::string verso() const override {
        return Cane::verso() + "-" + Gatto::verso() + "!";
    }
    std::string specie() const override { return "chimera"; }

    void presentati() const override {
        Animale::presentati();   // comportamento di base...
        std::cout << "  ...e sono meta' cane e meta' gatto!" << std::endl;   // ...piu' qualcosa di mio
    }

    // Usa i metodi di entrambi i genitori sullo STESSO oggetto
    void trasformati() const {
        std::cout << nome << " si trasforma:" << std::endl << "  ";
        riportaPallina();   // da Cane
        std::cout << "  ";
        faLeFusa();         // da Gatto
    }
};

// ============================================================
// 5) main
// ============================================================
int main()
{
    // Animale a("x", 1);   // ERRORE: Animale e' astratta

    Animale* animali[] = {
        new Cane("Fido", 5, "labrador"),
        new Gatto("Luna", 3),
        new Chimera("Kimy", 1000)
    };
    const int quanti = 3;

    std::cout << "Animali vivi: " << Animale::getAnimaliVivi() << " (la chimera conta 1, non 2)" << std::endl;

    std::cout << std::endl << "=== Presentazioni (polimorfismo) ===" << std::endl;
    for (int i = 0; i < quanti; i++) {
        animali[i]->presentati();   // viene chiamata la versione della classe vera
    }

    std::cout << std::endl << "=== Overloading di mangia ===" << std::endl;
    animali[0]->mangia();
    animali[1]->mangia("tonno");
    animali[2]->mangia("croccantini", 300);

    std::cout << std::endl << "=== operator<< ===" << std::endl;
    for (int i = 0; i < quanti; i++) {
        std::cout << *animali[i] << std::endl;
    }

    std::cout << std::endl << "=== Chi sa riportare la pallina? (dynamic_cast) ===" << std::endl;
    // dynamic_cast restituisce nullptr se l'oggetto NON e' davvero di quel tipo.
    // La Chimera E' un Cane, quindi anche lei sa riportare la pallina.
    for (int i = 0; i < quanti; i++) {
        Cane* c = dynamic_cast<Cane*>(animali[i]);
        if (c != nullptr) {
            c->riportaPallina();
        } else {
            std::cout << animali[i]->getNome() << " ti guarda e non si muove." << std::endl;
        }
    }

    std::cout << std::endl << "=== Metodi specifici della Chimera ===" << std::endl;
    Chimera* k = dynamic_cast<Chimera*>(animali[2]);
    if (k != nullptr) {
        k->trasformati();
    }

    std::cout << std::endl << "=== Liberazione della memoria ===" << std::endl;
    for (int i = 0; i < quanti; i++) {
        delete animali[i];   // distruttore virtuale: vengono chiamati tutti i distruttori giusti
    }
    std::cout << "Animali vivi: " << Animale::getAnimaliVivi() << std::endl;

    return 0;
}
