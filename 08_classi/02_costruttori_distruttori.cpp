// ARGOMENTO: costruttori e distruttori
//
// - COSTRUTTORE: metodo speciale con lo stesso nome della classe e senza tipo di ritorno.
//   Viene chiamato AUTOMATICAMENTE quando l'oggetto nasce. Serve a inizializzarlo.
//   Una classe puo' avere piu' costruttori (overloading).
// - DISTRUTTORE: ~NomeClasse(), senza parametri. Viene chiamato AUTOMATICAMENTE
//   quando l'oggetto muore (fine dello scope, oppure delete). Serve a liberare risorse.
// - Lista di inizializzazione ( : attributo(valore) ): inizializza gli attributi PRIMA
//   del corpo del costruttore. E' il modo corretto (e l'unico per const e referenze).
// - RAII: "la risorsa si acquisisce nel costruttore e si rilascia nel distruttore",
//   cosi' non ci si puo' dimenticare di liberarla.

#include <iostream>
#include <string>

class Risorsa {
private:
    std::string nome;
    int* dati;          // memoria allocata dinamicamente: va liberata nel distruttore
    int dimensione;

public:
    // Costruttore con parametri + lista di inizializzazione
    Risorsa(const std::string& nome, int dimensione)
        : nome(nome), dati(new int[dimensione]), dimensione(dimensione)
    {
        for (int i = 0; i < dimensione; i++) {
            dati[i] = i * 10;
        }
        std::cout << "  [costruttore]        " << this->nome << " (alloca " << dimensione << " int)" << std::endl;
    }

    // Costruttore di default (senza parametri) che DELEGA a quello sopra (C++11)
    Risorsa() : Risorsa("anonima", 1) {
        std::cout << "  [costruttore default] completato" << std::endl;
    }

    // Costruttore di COPIA: crea un nuovo oggetto copiandone un altro.
    // Va scritto a mano quando la classe gestisce memoria: quello automatico
    // copierebbe solo il puntatore e due oggetti libererebbero la stessa memoria!
    Risorsa(const Risorsa& altra)
        : nome(altra.nome + "_copia"), dati(new int[altra.dimensione]), dimensione(altra.dimensione)
    {
        for (int i = 0; i < dimensione; i++) {
            dati[i] = altra.dati[i];   // copia PROFONDA: copio i valori, non il puntatore
        }
        std::cout << "  [costruttore copia]  " << nome << std::endl;
    }

    // Assegnamento disabilitato per semplicita' (= delete).
    // Regola del tre: se scrivi distruttore, costruttore di copia O operator=,
    // probabilmente ti servono tutti e tre.
    Risorsa& operator=(const Risorsa&) = delete;

    // Distruttore
    ~Risorsa() {
        delete[] dati;
        std::cout << "  [distruttore]        " << nome << std::endl;
    }

    void stampa() const {
        std::cout << "  " << nome << ": ";
        for (int i = 0; i < dimensione; i++) {
            std::cout << dati[i] << " ";
        }
        std::cout << std::endl;
    }
};

// Composizione: una classe che contiene altri oggetti come attributi
class Componente {
    std::string nome;
public:
    Componente(const std::string& nome) : nome(nome) {
        std::cout << "  costruito " << nome << std::endl;
    }
    ~Componente() {
        std::cout << "  distrutto " << nome << std::endl;
    }
};

class Automobile {
    // Gli attributi vengono costruiti nell'ordine in cui sono DICHIARATI qui
    Componente motore;
    Componente ruote;
    const int anno;     // un attributo const si puo' inizializzare SOLO nella lista
public:
    Automobile(int anno) : motore("motore"), ruote("ruote"), anno(anno) {
        std::cout << "  costruita automobile del " << this->anno << std::endl;
    }
    ~Automobile() {
        std::cout << "  distrutta automobile" << std::endl;
    }
};

class Temperatura {
    double gradi;
public:
    // explicit: impedisce conversioni implicite tipo Temperatura t = 25.0;
    explicit Temperatura(double gradi) : gradi(gradi) {}
    double get() const { return gradi; }
};

int main()
{
    std::cout << "1) Oggetto in uno scope { }" << std::endl;
    {
        Risorsa r("A", 3);
        r.stampa();
        std::cout << "  ...fine dello scope..." << std::endl;
    }   // qui r muore: il distruttore viene chiamato da solo

    std::cout << std::endl << "2) Costruttore di default (delegante)" << std::endl;
    {
        Risorsa r;
        r.stampa();
    }

    std::cout << std::endl << "3) Costruttore di copia" << std::endl;
    {
        Risorsa originale("B", 4);
        Risorsa copia = originale;   // NON e' un assegnamento: chiama il costruttore di copia
        copia.stampa();
        // copia = originale;        // ERRORE: operator= e' stato cancellato
    }   // distrutti in ordine INVERSO rispetto alla costruzione: prima copia, poi originale

    std::cout << std::endl << "4) new e delete" << std::endl;
    Risorsa* p = new Risorsa("C", 2);   // il costruttore parte con new
    p->stampa();
    delete p;                           // il distruttore parte con delete
    // senza delete la memoria non verrebbe mai liberata (memory leak)

    std::cout << std::endl << "5) Ordine con la composizione" << std::endl;
    {
        Automobile a(2024);
        // costruzione:  prima gli attributi (in ordine), poi il corpo del costruttore
        // distruzione:  prima il corpo del distruttore, poi gli attributi (in ordine inverso)
    }

    std::cout << std::endl << "6) explicit" << std::endl;
    Temperatura t(25.0);          // ok
    // Temperatura t2 = 25.0;     // ERRORE grazie a explicit
    std::cout << "  temperatura = " << t.get() << std::endl;

    std::cout << std::endl << "Fine del main" << std::endl;
    return 0;
}
