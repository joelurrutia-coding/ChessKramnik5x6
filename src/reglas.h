#include <array>
#include "vector2D.h"
#include "plataforma.h"

class Reglas {
public:
    Reglas();

    static vector2D pieceFinder(int value, std::array<std::array<int, 6>, 5>& board);
    static bool moveChecker(int piece, vector2D origen, vector2D destino, std::array<std::array<int, 6>, 5>& board);
    static bool enroqueChecker(bool turn, vector2D origen, vector2D destino, std::array<std::array<int, 6>, 5>& board);
    static void enroqueMove(bool turn, vector2D origen, vector2D destino, std::array<std::array<int, 6>, 5>& board);

    static void displayValidMoves(int piece, vector2D origen, std::array<std::array<int, 6>, 5>& board, std::array<std::array<Losa, 6>, 5>& tiles);
    static void displayCastling(int piece, vector2D origen, std::array<std::array<int, 6>, 5>& board, std::array<std::array<Losa, 6>, 5>& tiles);
    static void displayDanger(vector2D posicion, std::array<std::array<Losa, 6>, 5>& tiles);
    static void displayDangerous(vector2D posicion, std::array<std::array<Losa, 6>, 5>& tiles);
    
    static bool jaque(bool turnFlag, std::array<std::array<int, 6>, 5>& board, std::array<std::array<Losa, 6>, 5>& tiles);
    static bool jaqueMate(bool turnFlag, std::array<std::array<int, 6>, 5>& board, std::array<std::array<Losa, 6>, 5>& tiles);

    static void updateMov(int value, vector2D origen, vector2D destino, std::array<std::array<int, 6>, 5>& board);
};