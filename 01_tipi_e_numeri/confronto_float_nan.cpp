// ARGOMENTO: numeri in virgola mobile, NaN e confronto "quasi uguale"
//
// - NaN (Not a Number) e' l'unico valore diverso da se' stesso: NaN != NaN e' sempre true.
// - I float/double hanno precisione limitata, quindi confrontarli con == e' rischioso:
//   meglio usare una tolleranza relativa e assoluta (vedi nearlyEqual).

#include <iostream>
#include <string>
#include <limits>    // std::numeric_limits
#include <cmath>     // std::isfinite, std::abs
#include <algorithm> // std::max

// ESERCIZIO
// Drenate la vita di due priest finchè una nuova variabile vita del
// diavolo non raggiunge la somma di 70;
// potete drenare 10 punti vita alla volta.
// (traccia dell'esercizio, non ancora svolta in questo file)

// Confronta due double con tolleranza:
//   relTol = tolleranza relativa (proporzionale alla grandezza dei numeri)
//   absTol = tolleranza assoluta (utile per numeri vicini a zero)
bool nearlyEqual(double a, double b, double relTol = 1e-9, double absTol = 1e-12)
{
    if (a == b)
        return true; // zeri e infiniti uguali
    if (!std::isfinite(a) || !std::isfinite(b))
        return false; // NaN o infinito: non sono mai "quasi uguali"
    if (std::abs(a - b) <= absTol)
        return true;
    double scale = std::max(std::abs(a), std::abs(b));
    // scale > 0: gli zeri uguali sono gia stati gestiti
    // divido per scale per confrontare la differenza in termini relativi
    return std::abs(a / scale - b / scale) <= relTol;
}

    int main()
    {
        // quiet_NaN() restituisce un NaN "silenzioso" (non genera eccezioni)
        float a = std::numeric_limits<float>::quiet_NaN();
        float b = std::numeric_limits<float>::quiet_NaN();

        // boolalpha stampa true/false invece di 1/0
        std::cout << std::boolalpha << (a != b) << std::endl; // true: NaN != NaN

        // Posted by Joseph Mansfield, modified by community. See post 'Timeline' for change history
        // Retrieved 2026-10-29, License - CC BY-SA 3.0

        // Il modo corretto per sapere se un valore e' NaN:
        // if (std::isnan(a))
        // {
        // }
        std::cout << std::boolalpha << nearlyEqual(a,b) << std::endl; // false


        // Vicino al massimo rappresentabile, sottrarre 10 o 15 non cambia nulla:
        // la differenza e' molto piu' piccola della precisione del float.
        float c = std::numeric_limits<float>::max() - 10;
        float d = std::numeric_limits<float>::max() - 15;
        std::cout << std::boolalpha << nearlyEqual(c,d) << std::endl; // true

    }
