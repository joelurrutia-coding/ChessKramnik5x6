#include <array>
#include "vector2D.h"
#include "tablero.h"

class Reglas {
public:
    Reglas();

    static bool moveChecker(int piece, vector2D origen, vector2D destino, std::array<std::array<int, 6>, 5>& board);
    static void displayValidMoves(int piece, vector2D origen, std::array<std::array<int, 6>, 5>& board, std::array<std::array<Losa, 6>, 5>& tiles);
    static void displayDanger(vector2D posicion, std::array<std::array<Losa, 6>, 5>& tiles);
    static void displayDangerous(vector2D posicion, std::array<std::array<Losa, 6>, 5>& tiles);

    static vector2D kingFinder(bool turnFlag, std::array<std::array<int, 6>, 5>& board);
    static bool jaque(bool turnFlag, std::array<std::array<int, 6>, 5>& board, std::array<std::array<Losa, 6>, 5>& tiles);
    static bool jaqueMate(bool turnFlag, std::array<std::array<int, 6>, 5>& board, std::array<std::array<Losa, 6>, 5>& tiles);
};