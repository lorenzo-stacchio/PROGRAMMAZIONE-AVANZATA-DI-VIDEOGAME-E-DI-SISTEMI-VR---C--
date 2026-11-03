// ARGOMENTO: mini-progetto Tris (tic-tac-toe) che mette insieme piu' concetti
//
// - enum class: un insieme di costanti con nome e tipo proprio (Symbol::X, ...)
// - std::array<std::array<T, 3>, 3>: matrice 3x3 a dimensione fissa
// - passaggio per valore (stampa, controllo) vs per referenza (inserimento)
// - input da tastiera con cin, switch, ciclo while
//
// NOTA: per ora non c'e' il controllo del vincitore ne' dei limiti di riga/colonna
// (inserire un valore fuori da 0-2 causa un accesso fuori dall'array).

#include <iostream>
#include <list>
#include <array>
using namespace std;  // permette di scrivere cout invece di std::cout

// Ogni cella puo' essere vuota, X oppure O
enum class Symbol { EMPTY = 0, X = 1, O = 2 };

// Restituisce una griglia con tutte le celle vuote
array<array<Symbol, 3>, 3> generate_empty_board(int rows, int cols){
    array<array<Symbol, 3>, 3> empty_board;
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            empty_board[i][j] = Symbol::EMPTY;
        }
    }
    return empty_board;
};



// Stampa la griglia: static_cast<int> converte il Symbol nel suo numero (0, 1, 2)
void stampa_matrice(array<array<Symbol, 3>, 3> board){
    for (auto row : board){
        for (auto cell : row){
            cout << static_cast<int>(cell) << " ";
        }
        cout << endl;
    }
}

// board e' passata per REFERENZA (&) perche' la funzione deve modificarla
void insert_symbol(array<array<Symbol, 3>, 3>& board, int row, int col, Symbol symbol){
    if (board[row][col] == Symbol::EMPTY){
        board[row][col] = symbol;
    } else {
        cout << "Cell is already occupied!" << endl;
    }
}

// true se non ci sono piu' celle vuote
bool is_board_full(array<array<Symbol, 3>, 3> board){
    for (auto row : board){
        for (auto cell : row){
            if (cell == Symbol::EMPTY){
                return false;
            }
        }
    }
    return true;
}

int main()
    {
       array<array<Symbol, 3>, 3> board = generate_empty_board(3, 3);
       stampa_matrice(board);
       cout << "Board is full!" << endl;  // NOTA: messaggio fuori posto, andrebbe stampato dopo il while
       // Il gioco continua finche' ci sono celle libere
       while(!is_board_full(board)){
           int row, col, int_symbol;
           Symbol symbol;
           cout << "Enter row (0-2): ";
           cin >> row;
           cout << "Enter column (0-2): ";
           cin >> col;
           cout << "Enter symbol (1 for X, 2 for O): ";
           cin >> int_symbol;
           // Converte il numero inserito nel corrispondente Symbol
           switch(int_symbol){
               case 1:
                   symbol = Symbol::X;
                   break;
               case 2:
                   symbol = Symbol::O;
                   break;
               default:
                   cout << "Invalid symbol!" << endl;
                   continue;  // salta al prossimo giro del while
           }
           insert_symbol(board, row, col, symbol);
           stampa_matrice(board);
       }

    }
