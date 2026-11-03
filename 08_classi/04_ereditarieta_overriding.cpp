// ARGOMENTO: ereditarieta', overriding e polimorfismo
//
// - EREDITARIETA': class Derivata : public Base { ... }
//   La derivata "e' un" tipo di base: eredita attributi e metodi e puo' aggiungerne.
// - virtual: il metodo puo' essere RIDEFINITO dalle derivate.
// - OVERRIDING: la derivata ridefinisce un metodo virtual della base con la STESSA firma.
//   La parola chiave override (C++11) chiede al compilatore di controllare che sia davvero
//   un override (se sbagli la firma, da' errore invece di creare un metodo nuovo).
// - POLIMORFISMO: tramite un puntatore/referenza alla BASE si chiama il metodo della
//   classe VERA dell'oggetto, scelto a TEMPO DI ESECUZIONE.
// - Metodo virtuale PURO (= 0): la base non lo implementa -> classe ASTRATTA,
//   non si possono creare oggetti di quella classe.
// - final: impedisce ulteriori derivazioni o override.
// - Distruttore virtual: OBBLIGATORIO nella base se si fa delete tramite puntatore alla base.

#include <iostream>
#include <string>

class Forma {
protected:
    // protected: invisibile da fuori, ma accessibile alle classi derivate
    std::string nome;

public:
    Forma(const std::string& nome) : nome(nome) {
        std::cout << "  [costruttore Forma] " << nome << std::endl;
    }

    virtual ~Forma() {
        std::cout << "  [distruttore Forma] " << nome << std::endl;
    }

    // Virtuale puro: ogni forma DEVE dire come si calcola la sua area
    virtual double area() const = 0;

    // Virtuale con implementazione di default: le derivate POSSONO ridefinirlo
    virtual void descrivi() const {
        std::cout << "  Sono un " << nome << " con area " << area() << std::endl;
    }

    // NON virtuale: se una derivata lo ridefinisce lo NASCONDE, non lo sovrascrive
    void saluta() const {
        std::cout << "  Ciao da Forma" << std::endl;
    }
};

class Rettangolo : public Forma {
protected:
    double base, altezza;

public:
    // Il costruttore della derivata deve chiamare quello della base nella lista
    Rettangolo(double base, double altezza, const std::string& nome = "Rettangolo")
        : Forma(nome), base(base), altezza(altezza)
    {
        std::cout << "  [costruttore Rettangolo]" << std::endl;
    }

    ~Rettangolo() override {
        std::cout << "  [distruttore Rettangolo]" << std::endl;
    }

    double area() const override {
        return base * altezza;
    }

    void descrivi() const override {
        Forma::descrivi();   // richiamo la versione della base...
        std::cout << "    ...e i miei lati sono " << base << " x " << altezza << std::endl;   // ...e aggiungo
    }

    // Stesso nome di Forma::saluta, ma Forma::saluta NON e' virtual -> e' "hiding"
    void saluta() const {
        std::cout << "  Ciao da Rettangolo" << std::endl;
    }
};

// final: nessuno puo' derivare da Quadrato
class Quadrato final : public Rettangolo {
public:
    Quadrato(double lato) : Rettangolo(lato, lato, "Quadrato") {
        std::cout << "  [costruttore Quadrato]" << std::endl;
    }
    ~Quadrato() override {
        std::cout << "  [distruttore Quadrato]" << std::endl;
    }
    // area() e descrivi() vengono ereditati da Rettangolo
};

class Cerchio : public Forma {
    double raggio;
public:
    Cerchio(double raggio) : Forma("Cerchio"), raggio(raggio) {}

    double area() const override {
        return 3.14159 * raggio * raggio;
    }
    // double area() override { ... }  // ERRORE: manca const, la firma e' diversa e override se ne accorge
};

// Funzione che accetta QUALSIASI Forma: grazie al polimorfismo funziona con tutte
void stampaInfo(const Forma& f) {
    f.descrivi();
}

int main()
{
    // Forma f("x");   // ERRORE: Forma e' astratta (ha un metodo virtuale puro)

    std::cout << "=== Costruzione (prima la base, poi la derivata) ===" << std::endl;
    Rettangolo r(3, 4);
    Quadrato q(5);
    Cerchio c(1);

    std::cout << std::endl << "=== Overriding e polimorfismo con referenze ===" << std::endl;
    stampaInfo(r);
    stampaInfo(q);
    stampaInfo(c);

    std::cout << std::endl << "=== Polimorfismo con un array di puntatori alla base ===" << std::endl;
    Forma* forme[] = {&r, &q, &c};
    double areaTotale = 0;
    for (Forma* f : forme) {
        areaTotale += f->area();   // chiama l'area() giusta per ogni oggetto
    }
    std::cout << "  Area totale: " << areaTotale << std::endl;

    std::cout << std::endl << "=== Overriding (virtual) vs hiding (non virtual) ===" << std::endl;
    Forma& rifBase = r;
    r.saluta();         // "Ciao da Rettangolo": chiamato sull'oggetto Rettangolo
    rifBase.saluta();   // "Ciao da Forma": saluta NON e' virtual, conta il tipo della referenza
    rifBase.descrivi(); // versione di Rettangolo: descrivi E' virtual, conta il tipo vero

    std::cout << std::endl << "=== delete tramite puntatore alla base ===" << std::endl;
    Forma* dinamica = new Quadrato(2);
    std::cout << "  ...delete..." << std::endl;
    delete dinamica;    // grazie al distruttore virtual vengono chiamati TUTTI i distruttori
                        // (senza virtual verrebbe chiamato solo ~Forma: errore!)

    std::cout << std::endl << "=== Fine main: distruzione degli oggetti sullo stack ===" << std::endl;
    return 0;
}
