#include "computador.h"
#include "reglas.h" 
#include "menu.h"

#include <iostream>
#include <cstdlib>
#include <string>

Computador::Computador(): 
    movAttackerPos(-1, -1), movAttackerVal(0),
    movEnemyPos(-1, -1), movEnemyVal(7)
{}
Computador::~Computador() {}

void Computador::makeMoveOpening(bool openingFlag, bool turnFlag, bool autopilotFlag, std::array<std::array<int, 6>, 5>& board)
{
    if (!openingFlag || !turnFlag || !autopilotFlag)
        return;
    // RANDOM DE 0 A 6
    std::srand(std::time(nullptr));
    int r = std::rand() % 7;

    if (r >= 0 && r <= 4) {
        imprimirComputerMov(-1, {static_cast<float>(r), 4.0f}, {static_cast<float>(r), 3.0f}, board);
    }
    else if (r == 5) {  
        imprimirComputerMov(-3, { 3.0f, 5.0f }, { 4.0f, 3.0f }, board);
    }
    else if (r == 6) {
        imprimirComputerMov(-3, { 3.0f, 5.0f }, { 2.0f, 3.0f }, board);
    }
}
bool Computador::makeMove(bool turnFlag, bool autopilotFlag, std::array<std::array<int, 6>, 5>& board) {
    if (autopilotFlag != 1 || turnFlag != 1)
        return false;

    vector2D kingPos = Reglas::kingFinder(1, board);
    if (kingPos.x == -1) {
        std::cout << "Rey negro no encontrado\n";
        return false;
    }

    bool foundMove = false;

    for (int x = 0; x < 5; x++) {
        for (int z = 0; z < 6; z++) {
            int attackerVal = board[x][z];
            if (attackerVal >= 0)
                continue; // Solo piezas negras
            vector2D attackerPos(static_cast<float>(x), static_cast<float>(z));

            for (int destX = 0; destX < 5; destX++) {
                for (int destZ = 0; destZ < 6; destZ++) {
                    if (x == destX && z == destZ)
                        continue;
                    vector2D enemyPos(static_cast<float>(destX), static_cast<float>(destZ));
                    if (!Reglas::moveChecker(attackerVal, attackerPos, enemyPos, board))
                        continue;

                    // Simular el movimiento en una copia del tablero
                    std::array<std::array<int, 6>, 5> boardCopy = board;
                    boardCopy[destX][destZ] = attackerVal;
                    boardCopy[x][z] = 0;
                    Tablero platformCopy;

                    // Verificar que el movimiento no deje al rey en jaque
                    if (Reglas::jaque(!turnFlag, boardCopy, platformCopy.getTiles()))
                        continue;
                    int enemyVal = board[destX][destZ];
                    if (!foundMove) {
                        movAttackerPos = attackerPos;
                        movAttackerVal = attackerVal;
                        movEnemyPos = enemyPos;
                        movEnemyVal = enemyVal;
                        foundMove = true;
                    }
                    else {
                        if (enemyVal > movEnemyVal ||
                            (enemyVal == movEnemyVal && attackerVal > movAttackerVal)) {
                            movAttackerPos = attackerPos;
                            movAttackerVal = attackerVal;
                            movEnemyPos = enemyPos;
                            movEnemyVal = enemyVal;
                        }
                    }
                }
            }
        }
    }
    if (foundMove &&
        movAttackerPos.x != -1 && movAttackerPos.z != -1 &&
        movEnemyPos.x != -1 && movEnemyPos.z != -1) {
        imprimirComputerMov(movAttackerVal, movAttackerPos, movEnemyPos, board);
        return true;
    }
    else {
        std::cout << "Computadora no encontró movimiento válido.\n";
        return false;
    }
}
bool Computador::makeMoveKingSafe(bool turnFlag, bool autopilotFlag, std::array<std::array<int, 6>, 5>& board) {
    if (autopilotFlag != 1 || turnFlag != 1)
        return false;

    vector2D kingPos = Reglas::kingFinder(1, board);
    if (kingPos.x == -1) {
        std::cout << "Rey negro no encontrado\n";
        return false;
    }

    bool foundMove = false;
    bool done = false; // Bandera para salir de todos los bucles una vez encontrado un movimiento válido

    for (int x = 0; x < 5 && !done; x++) {
        for (int z = 0; z < 6 && !done; z++) {
            int attackerVal = board[x][z];
            if (attackerVal >= 0)
                continue;  // Solo piezas negras
            vector2D attackerPos(static_cast<float>(x), static_cast<float>(z));

            for (int destX = 0; destX < 5 && !done; destX++) {
                for (int destZ = 0; destZ < 6 && !done; destZ++) {
                    if (x == destX && z == destZ)
                        continue;
                    vector2D enemyPos(static_cast<float>(destX), static_cast<float>(destZ));
                    if (!Reglas::moveChecker(attackerVal, attackerPos, enemyPos, board))
                        continue;

                    std::array<std::array<int, 6>, 5> boardCopy = board;
                    boardCopy[destX][destZ] = attackerVal;
                    boardCopy[x][z] = 0;

                    vector2D newKingPos;
                    if (abs(attackerVal) == 6)
                        newKingPos = enemyPos;  // El rey se mueve a la casilla destino
                    else
                        newKingPos = Reglas::kingFinder(1, boardCopy);
                    if (newKingPos.x == -1)
                        continue;

                    // Verificar que la nueva posición del rey no esté bajo ataque
                    bool kingSafe = true;
                    for (int a = 0; a < 5 && kingSafe; a++) {
                        for (int b = 0; b < 6 && kingSafe; b++) {
                            int whitePiece = boardCopy[a][b];
                            if (whitePiece <= 0)
                                continue;
                            vector2D whitePos(static_cast<float>(a), static_cast<float>(b));
                            if (Reglas::moveChecker(whitePiece, whitePos, newKingPos, boardCopy))
                                kingSafe = false;
                        }
                    }
                    if (kingSafe) { // Movimiento seguro para el rey
                        movAttackerPos = attackerPos;
                        movAttackerVal = attackerVal;
                        movEnemyPos = enemyPos;
                        movEnemyVal = board[destX][destZ];
                        foundMove = true;
                        done = true; // Salir de todos los bucles
                    }
                }
            }
        }
    }
    if (foundMove) {
        imprimirComputerMov(movAttackerVal, movAttackerPos, movEnemyPos, board);
        return true;
    }
    else {
        std::cout << "Computadora no encontró movimiento seguro para el rey.\n";
        return false;
    }
}
void Computador::imprimirComputerMov(int pieceVal, vector2D origen, vector2D destino, std::array<std::array<int, 6>, 5>& board) const {
    if (origen.x != -1 && origen.z != -1 &&
        destino.x != -1 && destino.z != -1) {
        // ACTUALIZAMOS MOVIMIENTO DEL COMPUTADOR
        board[(int)destino.x][(int)destino.z] = board[(int)origen.x][(int)origen.z];
        board[(int)origen.x][(int)origen.z] = 0;

        int piece = abs(pieceVal);
        char abrev = '?';
        switch (piece) {
        case 1: abrev = 'P'; break; // Peón
        case 2: abrev = 'R'; break; // Torre
        case 3: abrev = 'H'; break; // Caballo
        case 4: abrev = 'B'; break; // Alfil
        case 5: abrev = 'Q'; break; // Reina
        case 6: abrev = 'K'; break; // Rey
        default: break;
        }
        char col_orig = 'e' - static_cast<int>(origen.x);
        int row_orig = static_cast<int>(origen.z) + 1;
        char col_dest = 'e' - static_cast<int>(destino.x);
        int row_dest = static_cast<int>(destino.z) + 1;

        std::cout << "b " << abrev << " " << col_orig << row_orig << " " << col_dest << row_dest << std::endl;
    }
}