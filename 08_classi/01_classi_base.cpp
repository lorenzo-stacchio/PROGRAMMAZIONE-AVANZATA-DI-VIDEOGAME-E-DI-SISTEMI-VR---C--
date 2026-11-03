// ARGOMENTO: creare una classe
//
// Una CLASSE e' un tipo definito da noi che raggruppa:
//   - ATTRIBUTI (dati, "variabili membro")
//   - METODI    (funzioni che lavorano su quei dati)
// Un OGGETTO e' una variabile di quel tipo (un'istanza della classe).
//
// Specificatori di accesso:
//   public:    accessibile da chiunque
//   private:   accessibile solo dai metodi della classe (INCAPSULAMENTO)
//   protected: come private, ma visibile anche alle classi derivate (vedi ereditarieta')
//
// struct e class sono quasi identici: l'unica differenza e' che in una struct
// tutto e' public di default, in una class tutto e' private di default.

#include <iostream>
#include <string>

// struct: di solito usata per semplici "contenitori di dati"
struct Punto {
    int x;
    int y;
};

class ContoBancario {
private:
    // Attributi privati: dall'esterno non si possono toccare direttamente,
    // cosi' il saldo non puo' mai diventare negativo "per sbaglio".
    std::string titolare = "sconosciuto";   // valore iniziale di default (C++11)
    double saldo = 0.0;

    // static: UNA sola variabile condivisa da TUTTI gli oggetti della classe
    static int operazioniTotali;

public:
    // Metodo che modifica l'oggetto
    void deposita(double importo) {
        if (importo > 0) {
            saldo += importo;
            operazioniTotali++;
        }
    }

    // Restituisce false se il prelievo non e' possibile
    bool preleva(double importo) {
        if (importo <= 0 || importo > saldo) {
            return false;
        }
        saldo -= importo;
        operazioniTotali++;
        return true;
    }

    // GETTER: leggono un attributo privato.
    // const dopo le parentesi = il metodo promette di NON modificare l'oggetto.
    double getSaldo() const { return saldo; }
    const std::string& getTitolare() const { return titolare; }

    // SETTER: modificano un attributo privato (potendo controllare il valore)
    void setTitolare(const std::string& titolare) {
        // this e' un puntatore all'oggetto corrente: serve a distinguere
        // l'attributo (this->titolare) dal parametro con lo stesso nome
        this->titolare = titolare;
    }

    // Solo dichiarato qui, definito fuori dalla classe (sotto)
    void stampa() const;

    // Metodo static: si chiama sulla classe, non su un oggetto
    static int getOperazioniTotali() { return operazioniTotali; }
};

// Definizione del metodo fuori dalla classe: NomeClasse::nomeMetodo
void ContoBancario::stampa() const {
    std::cout << "Conto di " << titolare << ": " << saldo << " euro" << std::endl;
}

// Gli attributi static vanno definiti (una volta) fuori dalla classe
int ContoBancario::operazioniTotali = 0;

int main()
{
    // --- struct ---
    Punto p{3, 4};           // inizializzazione dei campi in ordine
    p.x = 10;                // campi public: accesso diretto con il punto
    std::cout << "Punto: (" << p.x << ", " << p.y << ")" << std::endl << std::endl;

    // --- oggetti sullo STACK ---
    ContoBancario mario;     // creo un oggetto
    mario.setTitolare("Mario");
    mario.deposita(100);
    mario.preleva(30);
    mario.stampa();

    // mario.saldo = 1000000; // ERRORE di compilazione: saldo e' private

    ContoBancario luigi;     // ogni oggetto ha i SUOI attributi
    luigi.setTitolare("Luigi");
    luigi.deposita(50);
    if (!luigi.preleva(80)) {
        std::cout << "Prelievo di 80 rifiutato a " << luigi.getTitolare() << std::endl;
    }
    luigi.stampa();

    // --- oggetto sull'HEAP con new: si usa un puntatore e la freccia -> ---
    ContoBancario* anna = new ContoBancario;
    anna->setTitolare("Anna");        // anna->metodo() equivale a (*anna).metodo()
    anna->deposita(500);
    anna->stampa();
    delete anna;                      // ogni new va liberato con delete

    // L'attributo static e' condiviso: conta le operazioni di TUTTI i conti
    std::cout << std::endl << "Operazioni totali su tutti i conti: "
              << ContoBancario::getOperazioniTotali() << std::endl;

    // sizeof di un oggetto = somma (circa) dei suoi attributi NON static
    std::cout << "sizeof(ContoBancario) = " << sizeof(ContoBancario) << " byte" << std::endl;

    return 0;
}
