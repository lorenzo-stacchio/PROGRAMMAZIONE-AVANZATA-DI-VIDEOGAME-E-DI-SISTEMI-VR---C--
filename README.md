# Esercizi e appunti di C++

## Programmazione Avanzata di Videogame e di Sistemi di Realtà Virtuale

| Offerta formativa | UNIVPM – A.A. 2026/2027 |
| --- | --- |
| **Università** | Università Politecnica delle Marche (UNIVPM) |
| **Area** | Ingegneria |
| **Corso di Laurea** | Ingegneria dell'Informazione per Videogame e Realtà Virtuale |
| **Insegnamento** | Programmazione Avanzata di Videogame e di Sistemi di Realtà Virtuale |
| **Anno Accademico** | 2026/2027 |

Materiale didattico dell'insegnamento: una raccolta di programmi C++ commentati in italiano, divisi per argomento. Si parte dai tipi primitivi e si arriva alle classi e all'ereditarietà multipla.

**Perché il C++ in questo corso:** è il linguaggio di riferimento per i motori di gioco (Unreal Engine, la maggior parte dei motori proprietari) e per i sistemi di realtà virtuale. In questi ambiti ogni millisecondo per frame conta, e bisogna controllare direttamente memoria e prestazioni. I concetti qui raccolti sono la base per tutto quello che viene dopo: puntatori, gestione della memoria, classi, polimorfismo.

Ogni file è un programma completo con un proprio `main`: si apre, si compila e si esegue da solo. I commenti spiegano il concetto, mentre l'output mostra cosa succede davvero. Leggere il codice e poi guardarne l'output è il modo più veloce per capirlo.

## Percorso di studio consigliato

Le cartelle sono numerate, ma l'ordine di studio consigliato è leggermente diverso: i progetti usano le classi, quindi conviene farli per ultimi.

1. [01_tipi_e_numeri](01_tipi_e_numeri/): come il C++ rappresenta i dati
2. [02_array_liste_matrici](02_array_liste_matrici/): come raggrupparli
3. [03_puntatori_e_referenze](03_puntatori_e_referenze/): come la memoria viene condivisa tra variabili e funzioni
4. [04_funzioni](04_funzioni/): dichiarazioni, overloading, lambda, funzioni di ordine superiore
5. [05_ricorsione](05_ricorsione/): funzioni che chiamano se stesse
6. [07_macro](07_macro/): cosa fa il preprocessore prima della compilazione
7. [08_classi](08_classi/): programmazione a oggetti
8. [06_progetti](06_progetti/): esercizi più grandi che mettono insieme tutto

---

## 01 – Tipi e numeri

📁 [01_tipi_e_numeri](01_tipi_e_numeri/)

**Perché:** ogni variabile in C++ ha un tipo che decide quanta memoria occupa, quali valori può contenere e come si comportano le operazioni. Molti bug nascono proprio da qui: una divisione intera inattesa, un overflow, il confronto tra due `double`.

| File | Cosa contiene |
|------|---------------|
| [tipi_primitivi.cpp](01_tipi_e_numeri/tipi_primitivi.cpp) | Panoramica completa in 11 sezioni: inizializzazione (`=`, `()`, `{}`), interi e loro limiti, `<cstdint>`, letterali (hex, binario, `1'000'000`, suffissi), aritmetica e divisione intera, overflow, `float`/`double`, `char` come numero, `bool`, conversioni e `static_cast`, `const`/`constexpr`/`auto`. |
| [confronto_float_nan.cpp](01_tipi_e_numeri/confronto_float_nan.cpp) | Perché `NaN != NaN` e perché i numeri in virgola mobile vanno confrontati con una tolleranza invece che con `==` (funzione `nearlyEqual`). |

## 02 – Array, liste e matrici

📁 [02_array_liste_matrici](02_array_liste_matrici/)

**Perché:** quasi ogni programma lavora su collezioni di dati. Qui si vede la differenza tra un array a dimensione fissa e una `std::list`, che invece cresce e si riduce.

| File | Cosa contiene |
|------|---------------|
| [array_liste.cpp](02_array_liste_matrici/array_liste.cpp) | Array statici, ciclo *for each*, `std::list` con `push_back`, `pop_back`, `pop_front`. |
| [matrici.cpp](02_array_liste_matrici/matrici.cpp) | Matrici come array 2D, calcolo di righe e colonne con `sizeof`, *structured binding* (`auto [a, b, c]`), matrice come lista di liste. |

## 03 – Puntatori e referenze

📁 [03_puntatori_e_referenze](03_puntatori_e_referenze/)

**Perché:** è l'argomento che distingue il C++ da molti altri linguaggi. Bisogna sapere se una funzione lavora su una copia o sull'originale, e cosa contiene davvero un puntatore.

| File | Cosa contiene |
|------|---------------|
| [puntatori_referenze_passaggi.cpp](03_puntatori_e_referenze/puntatori_referenze_passaggi.cpp) | Referenze (`int &`), puntatori (`int *`, `&`, `*`), passaggio per valore, per referenza, per referenza costante e per puntatore. Include una domanda-test ("cosa stampa?") con la risposta nei commenti. |

## 04 – Funzioni

📁 [04_funzioni](04_funzioni/)

**Perché:** le funzioni sono il modo base per organizzare il codice. In C++ una funzione si può anche passare come parametro a un'altra, ed è la base di molti algoritmi della libreria standard.

| File | Cosa contiene |
|------|---------------|
| [funzioni_dichiarazione_overloading.cpp](04_funzioni/funzioni_dichiarazione_overloading.cpp) | Differenza tra dichiarazione e definizione, dichiarazioni ripetute, overloading, perché una funzione va dichiarata prima di essere usata. |
| [lambda.cpp](04_funzioni/lambda.cpp) | Funzioni lambda usate come criterio di ordinamento in `std::sort`. |
| [funzioni_ordine_superiore.cpp](04_funzioni/funzioni_ordine_superiore.cpp) | Puntatori a funzione, funzioni che ricevono o restituiscono funzioni, *map*/*filter*/*reduce* scritti a mano, array di puntatori a funzione, lambda convertite in puntatori. |

## 05 – Ricorsione

📁 [05_ricorsione](05_ricorsione/)

**Perché:** alcuni problemi si descrivono in modo naturale in termini di se stessi. È importante capire la differenza tra ricorsione normale e ricorsione *di coda*: nel primo caso ogni chiamata resta in memoria e lo stack può finire, nel secondo il compilatore può trasformare la ricorsione in un ciclo.

| File | Cosa contiene |
|------|---------------|
| [funzioni_ricorsioni.cpp](05_ricorsione/funzioni_ricorsioni.cpp) | Fattoriale con ricorsione normale e con ricorsione di coda (accumulatore), con la traccia passo-passo delle chiamate. |
| [fattoriale_coda_numeri_grandi.cpp](05_ricorsione/fattoriale_coda_numeri_grandi.cpp) | Un miliardo di chiamate ricorsive senza *stack overflow* grazie all'ottimizzazione `/O2`. Il risultato stampato è `0` per overflow: il commento spiega perché. |
| [esplora_lista_ricorsiva.cpp](05_ricorsione/esplora_lista_ricorsiva.cpp) | Esercizio: stampare una lista ricorsivamente. Versione semplice che copia la lista a ogni chiamata. |
| [list_subparts.cpp](05_ricorsione/list_subparts.cpp) | Stesso esercizio con gli iteratori: stampa solo una sotto-parte della lista e non copia nulla. |

## 06 – Progetti

📁 [06_progetti](06_progetti/)

**Perché:** qui i concetti delle altre cartelle si usano insieme, come in un programma reale.

| File | Cosa contiene |
|------|---------------|
| [cane_gatto_chimera.cpp](06_progetti/cane_gatto_chimera.cpp) | **Esercizio con traccia e soluzione.** Classe astratta `Animale`, `Cane` e `Gatto` con ereditarietà virtuale, `Chimera` che eredita da entrambi (problema del diamante), overriding, overloading di `mangia()`, `operator<<`, `dynamic_cast`, contatore `static` degli animali vivi. Da fare dopo [08_classi](08_classi/). |
| [visualizzazione_tris.cpp](06_progetti/visualizzazione_tris.cpp) | Mini gioco del tris da terminale: `enum class`, `std::array` 3x3, input con `cin`, `switch`. Manca ancora il controllo del vincitore e dei limiti di riga e colonna (segnalato con `NOTA:` nel codice): è un buon spunto per esercitarsi. |

## 07 – Macro e preprocessore

📁 [07_macro](07_macro/)

**Perché:** prima della compilazione il preprocessore riscrive il codice. Le macro sono semplici sostituzioni di testo: potenti, ma piene di trappole. Servono soprattutto per gli include guard, la compilazione condizionale (debug/release, Windows/Linux) e i messaggi con file e riga.

| File | Cosa contiene |
|------|---------------|
| [macro_spiegazione.cpp](07_macro/macro_spiegazione.cpp) | Macro costanti e con parametri, il problema delle parentesi (`QUADRATO(2 + 3)`), la doppia valutazione (`MAX(i++, 0)`), operatori `#` e `##`, macro su più righe con `do { } while (0)`, macro variadiche, `#ifdef`/`#if`, macro di sistema (`_WIN32`, `__FILE__`, `__LINE__`, …), `#undef` e l'alternativa `constexpr`. |
| [matematica.h](07_macro/matematica.h) | Esempio di *include guard* (`#ifndef` / `#define` / `#endif`). Il file precedente lo include due volte apposta per mostrare che funziona. |
| [esercizio_macro.cpp](07_macro/esercizio_macro.cpp) | **Esercizio con traccia e soluzione:** `ARRAY_SIZE`, `MIN`, `CLAMP`, `RIPETI`, `CONTROLLA` (stile *assert* con file e riga), `LOG` attivabile con `#define`, getter generati con `##`. Accanto a ogni risultato è stampato anche quello atteso. |

## 08 – Classi

📁 [08_classi](08_classi/)

**Perché:** le classi permettono di creare tipi propri che uniscono dati e comportamento, e di proteggere i dati dall'uso sbagliato (incapsulamento). Con l'ereditarietà e il polimorfismo si scrive codice che funziona con tipi diversi senza conoscerli in anticipo. I file sono numerati nell'ordine in cui vanno letti.

| File | Cosa contiene |
|------|---------------|
| [01_classi_base.cpp](08_classi/01_classi_base.cpp) | `struct` e `class`, `public`/`private`, attributi e metodi, getter e setter, `this`, metodi `const`, membri `static`, oggetti sullo stack e sull'heap (`new`/`delete`, `->`). |
| [02_costruttori_distruttori.cpp](08_classi/02_costruttori_distruttori.cpp) | Costruttore con parametri, di default e delegante, lista di inizializzazione, costruttore di copia profonda, regola del tre, distruttore e RAII, ordine di costruzione e distruzione (anche con la composizione), `explicit`. |
| [03_overloading.cpp](08_classi/03_overloading.cpp) | Overloading di metodi e costruttori, overloading degli operatori su un `Vettore2D` (`+`, `-`, `*`, `+=`, `==`, `<<`), funzioni `friend`. |
| [04_ereditarieta_overriding.cpp](08_classi/04_ereditarieta_overriding.cpp) | Ereditarietà, `protected`, `virtual`, `override`, `final`, classi astratte (`= 0`), polimorfismo con puntatori e referenze, differenza tra *overriding* e *hiding*, perché il distruttore della base deve essere `virtual`. |
| [05_problema_diamante.cpp](08_classi/05_problema_diamante.cpp) | Ereditarietà multipla e problema del diamante: la versione senza `virtual` (due copie della base, accessi ambigui) e quella con ereditarietà virtuale (una sola copia, costruita dalla classe più derivata). |

> **Overloading o overriding?**
> *Overloading* significa stesso nome con parametri diversi; il compilatore sceglie quale versione chiamare durante la compilazione.
> *Overriding* significa che una classe derivata ridefinisce un metodo `virtual` della base con la stessa firma; la versione da chiamare si sceglie durante l'esecuzione, in base al tipo vero dell'oggetto.

---

## Come compilare ed eseguire

Il progetto usa il compilatore Microsoft **MSVC** (`cl.exe`) tramite VS Code.

**Da VS Code:** apri il file `.cpp` e premi **Ctrl+Shift+B**. La task in [.vscode/tasks.json](.vscode/tasks.json) compila il file aperto e crea l'eseguibile nella sua stessa cartella, quindi funziona in tutte le sottocartelle. Poi esegui il file dal terminale, ad esempio:

```
.\08_classi\01_classi_base.exe
```

**Dal terminale:** apri il *Developer Command Prompt for VS 2022* (oppure lancia `vcvars64.bat`), così `cl` è disponibile, e poi:

```
cl /EHsc /O2 nome_file.cpp
```

Note:
- [matrici.cpp](02_array_liste_matrici/matrici.cpp) usa una funzionalità di C++17: se il compilatore si lamenta, aggiungi `/std:c++17`.
- [tipi_primitivi.cpp](01_tipi_e_numeri/tipi_primitivi.cpp) produce 3 warning **voluti**, che mostrano conversioni con perdita di dati.
- I file `.exe`, `.obj`, `.pdb` e `.ilk` sono generati dalla compilazione: si possono cancellare in qualsiasi momento.

## Convenzioni usate nei file

- `// ARGOMENTO:` in cima al file riassume i concetti trattati.
- `// ESERCIZIO:` indica un esercizio: prima viene la `TRACCIA`, poi la `SOLUZIONE`. Per esercitarti, leggi solo la traccia e prova a scriverla da solo.
- `// NOTA:` segnala un limite noto o un comportamento sorprendente.
- `// ERRORE` accanto a una riga commentata indica codice che **non** compila: è lasciato lì per mostrare cosa il compilatore vieta. Prova a togliere il commento e leggi il messaggio di errore.
- Nei programmi con molte parti, l'output è diviso in sezioni `=== titolo ===` che corrispondono alle sezioni del codice.

---

*Materiale per l'insegnamento **Programmazione Avanzata di Videogame e di Sistemi di Realtà Virtuale**, Corso di Laurea in Ingegneria dell'Informazione per Videogame e Realtà Virtuale, Università Politecnica delle Marche, A.A. 2026/2027.*
