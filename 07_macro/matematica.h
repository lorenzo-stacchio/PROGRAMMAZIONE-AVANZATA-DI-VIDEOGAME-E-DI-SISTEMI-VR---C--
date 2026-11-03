// ARGOMENTO: include guard (protezione contro la doppia inclusione)
//
// #include copia letteralmente il contenuto del file nel punto in cui viene scritto.
// Se un header venisse incluso due volte, le sue definizioni comparirebbero due volte
// e il compilatore darebbe errore ("ridefinizione").
//
// Soluzione: la prima volta MATEMATICA_H non esiste -> la definisco e includo il contenuto.
// La seconda volta MATEMATICA_H esiste gia' -> il preprocessore salta tutto fino a #endif.
//
// Alternativa piu' corta (non standard ma supportata da tutti i compilatori): #pragma once

#ifndef MATEMATICA_H
#define MATEMATICA_H

// Versione macro: semplice sostituzione di testo
#define CUBO(x) ((x) * (x) * (x))

// Versione funzione: controllo dei tipi, nessuna sorpresa (preferibile in C++)
inline int cubo(int x) { return x * x * x; }

#endif // MATEMATICA_H
