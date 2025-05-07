#include "vector2D.h"
#include <array>

class Computador {
private:
    vector2D movOrigPos;
    int movOrigVal;
    vector2D movDestPos;
    int movDestVal;

public:
    Computador();
    ~Computador();

    void makeMoveOpening(bool openingFlag, bool turnFlag, bool autopilotFlag, std::array<std::array<int, 6>, 5>& board);
    bool makeMove(bool turnFlag, bool autopilotFlag, std::array<std::array<int, 6>, 5>& board);
    bool makeMoveKingSafe(bool turnFlag, bool autopilotFlag, std::array<std::array<int, 6>, 5>& board);
    void imprimirComputerMov(int piece, vector2D origen, vector2D destino, std::array<std::array<int, 6>, 5>& board) const;
};