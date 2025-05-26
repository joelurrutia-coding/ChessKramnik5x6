#include "computador.h"
#include "reglas.h" 
#include "menu.h"

#include <iostream>
#include <math.h>
#include <string>

Computador::Computador(): 
    movOrigPos(-1, -1), movOrigVal(0),
    movDestPos(-1, -1), movDestVal(-10)
{}
Computador::~Computador() {}

void Computador::makeMoveOpening(bool openingFlag, bool turnFlag, bool autopilotFlag, std::array<std::array<int, 6>, 5>& board) {
    if (!openingFlag || !turnFlag || !autopilotFlag)
        return;
    // RANDOM DE 0 A 6
    std::srand(std::time(nullptr));
    int r = std::rand() % 7;

    if (r >= 0 && r <= 4) {
        Reglas::updateMov(-1, {static_cast<float>(r), 4.0f}, {static_cast<float>(r), 3.0f}, board);
    }
    else if (r == 5) {  
        Reglas::updateMov(-3, { 3.0f, 5.0f }, { 4.0f, 3.0f }, board);
    }
    else if (r == 6) {
        Reglas::updateMov(-3, { 3.0f, 5.0f }, { 2.0f, 3.0f }, board);
    }
}
bool Computador::makeMove(bool turnFlag, bool autopilotFlag, std::array<std::array<int, 6>, 5>& board) {
    if (autopilotFlag != 1 || turnFlag != 1)
        return false;

    vector2D kingPos = Reglas::pieceFinder(-6, board);
    if (kingPos.x == -1) {
        //std::cout << "Rey negro no encontrado\n";
        return false;
    }
    bool foundMove = false;

    for (int x = 0; x < 5; x++) {
        for (int z = 0; z < 6; z++) {
            int origVal = board[x][z];
            if (origVal >= 0)
                continue; // Solo piezas negras
            vector2D origPos(static_cast<float>(x), static_cast<float>(z));

            for (int destX = 0; destX < 5; destX++) {
                for (int destZ = 0; destZ < 6; destZ++) {
                    if (x == destX && z == destZ)
                        continue;
                    vector2D destPos(static_cast<float>(destX), static_cast<float>(destZ));
                    if (!Reglas::moveChecker(origVal, origPos, destPos, board))
                        continue;

                    // Simular el movimiento en una copia del tablero
                    std::array<std::array<int, 6>, 5> boardCopy = board;
                    boardCopy[destX][destZ] = origVal;
                    boardCopy[x][z] = 0;
                    Plataforma platformCopy;

                    // Verificar que el movimiento no deje al rey en jaque
                    if (Reglas::jaque(!turnFlag, boardCopy, platformCopy.getTiles()))
                        continue;

                    int destVal = board[destX][destZ];
                    if (!foundMove) {
                        movOrigPos = origPos;
                        movOrigVal = origVal;
                        movDestPos = destPos;
                        movDestVal = destVal;
                        foundMove = true;
                    }
                    else {
                        if (destVal > movDestVal ||
                            (destVal == movDestVal && origVal > movOrigVal)) {
                            movOrigPos = origPos;
                            movOrigVal = origVal;
                            movDestPos = destPos;
                            movDestVal = destVal;
                        }
                    }
                }
            }
        }
    }
    if (foundMove &&
        movOrigPos.x != -1 && movOrigPos.z != -1 &&
        movDestPos.x != -1 && movDestPos.z != -1) {
        Reglas::updateMov(movOrigVal, movOrigPos, movDestPos, board);
        return true;
    }
    else {
        //std::cout << "Computadora no encontró movimiento válido.\n";
        return false;
    }
}
bool Computador::makeMoveKingSafe(bool turnFlag, bool autopilotFlag, std::array<std::array<int, 6>, 5>& board) {
    if (autopilotFlag != 1 || turnFlag != 1)
        return false;

    // Ubicar al rey negro en el tablero original.
    vector2D kingPos = Reglas::pieceFinder(-6, board);
    if (kingPos.x == -1) {
        //std::cout << "Rey negro no encontrado\n";
        return false;
    }
    // Variables de candidato para cada opción (sin usar struct extra).
    bool foundCapture = false, foundKing = false, foundBlock = false;
    
    vector2D bestCaptureOrigPos, bestCaptureDestPos;
    int bestCaptureOrigVal = 0;        // En caso de empate, movemos el menos costoso para negros (mejor orig -1 que -6).
    int bestCaptureDestVal = -10;      // Mayor valor capturado mejor, de -5 a +6.

    vector2D bestKingOrigPos, bestKingDestPos;   
    //int bestKingOrigVal = -6;        // Movemos el rey negro (-6).
    int bestKingDestVal = -10;         // Peor caso comer a la reina negra (-5), mejor caso comer al rey negro (+6).

    vector2D bestBlockOrigPos, bestBlockDestPos;
    int bestBlockOrigVal = -10;        // Para bloquear, se prefiere sacrificar la pieza de mayor valor (es decir, que cueste menos, ej. -1 es mejor que -5).
    int bestBlockDestVal = -10;

    // Recorrer todas las piezas negras y sus movimientos posibles.
    for (int x = 0; x < 5; x++) {
        for (int z = 0; z < 6; z++) {
            int origVal = board[x][z];
            if (origVal >= 0)
                continue;  // Sólo piezas negras.
            vector2D origPos(static_cast<float>(x), static_cast<float>(z));

            // Examinar cada casilla destino.
            for (int destX = 0; destX < 5; destX++) {
                for (int destZ = 0; destZ < 6; destZ++) {
                    if (x == destX && z == destZ)
                        continue;
                    vector2D destPos(static_cast<float>(destX), static_cast<float>(destZ));
                    if (!Reglas::moveChecker(origVal, origPos, destPos, board))
                        continue;

                    // Simular el movimiento en una copia del tablero y crear un objeto temporal.
                    std::array<std::array<int, 6>, 5> boardCopy = board;
                    boardCopy[destX][destZ] = origVal;
                    boardCopy[x][z] = 0;
                    Plataforma platformCopy;

                    // Verificar que el movimiento no deje al rey en jaque.
                    if (Reglas::jaque(!turnFlag, boardCopy, platformCopy.getTiles()))
                        continue;

                    // Valor de la casilla destino en el tablero original
                    int destVal = board[destX][destZ];

                    // Opción A: Capturar al atacante (destVal > 0).
                    if (destVal > 0) {
                        if (!foundCapture || (destVal > bestCaptureDestVal) || (destVal == bestCaptureDestVal && origVal > bestCaptureOrigVal)) {
                            bestCaptureOrigPos = origPos;
                            bestCaptureOrigVal = origVal;
                            bestCaptureDestVal = destVal;
                            bestCaptureDestPos = destPos;
                            foundCapture = true;
                            //std::cout << "Capturar\n";
                        }
                    }
                    // Opción B: Bloquear la línea de ataque (si no es rey ni caballo)
                    if (origVal != -6 && origVal != -3 && destVal > bestBlockDestVal) { // destVal == 0
                        if (destX == static_cast<int>(kingPos.x) || destZ == static_cast<int>(kingPos.z) ||
                            (abs(destX - static_cast<int>(kingPos.x)) == abs(destZ - static_cast<int>(kingPos.z)))) {
                            if (!foundBlock || (origVal > bestBlockOrigVal)) {
                                bestBlockOrigPos = origPos;
                                bestBlockDestPos = destPos;
                                bestBlockOrigVal = origVal;
                                bestBlockDestVal = destVal;
                                foundBlock = true;
                                //std::cout << "Bloqueo\n";
                            }
                        }
                    }
                    // Opción C: Mover el rey para esquivar el jaque.
                    if (origVal == -6 && destVal > bestKingDestVal) {
                        if (!foundKing || (destVal > bestKingDestVal) || (destVal == bestKingDestVal)) {
                            bestKingOrigPos = origPos;
                            //bestKingOrigVal = -6;
                            bestKingDestPos = destPos;
                            bestKingDestVal = destVal;  
                            foundKing = true;
                            //std::cout << "Esquivar\n";
                        }
                    }
                }
            }
        }
    }
    if (foundCapture) {
        movOrigPos = bestCaptureOrigPos;
        movOrigVal = bestCaptureOrigVal;
        movDestPos = bestCaptureDestPos;
        movDestVal = bestCaptureDestVal;
        Reglas::updateMov(movOrigVal, movOrigPos, movDestPos, board);
        return true;
    }
    else if (foundBlock) {
        movOrigPos = bestBlockOrigPos;
        movOrigVal = bestBlockOrigVal;
        movDestPos = bestBlockDestPos;
        movDestVal = bestBlockDestVal;
        Reglas::updateMov(movOrigVal, movOrigPos, movDestPos, board);
        return true;
    }
    else if (foundKing) {
        movOrigPos = bestKingOrigPos;
        movOrigVal = -6;
        movDestPos = bestKingDestPos;
        movDestVal = bestKingDestVal;
        Reglas::updateMov(movOrigVal, movOrigPos, movDestPos, board);
        return true;
    }
    else {
        //std::cout << "Computadora no encontro movimiento seguro para el rey.\n";
        return false;
    }
}