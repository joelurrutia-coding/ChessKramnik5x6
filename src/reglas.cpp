#include "reglas.h"
#include <math.h>
#include <iostream>
#include <fstream>
#include "freeglut.h"
#include "vector2D.h"
#include <vector>
#include "plataforma.h"
#include "ETSIDI.h"

Reglas::Reglas() {};

bool Reglas::moveChecker(int value, vector2D origen, vector2D destino, std::array<std::array<int, 6>, 5>& board) {
    bool turn = (value > 0) ? 0 : 1;
    int kingValue = (turn ? -6 : 6);
    vector2D kingPos = pieceFinder(kingValue, board);

    if (static_cast<int>(destino.x) < 0 || static_cast<int>(destino.x) > 4 || static_cast<int>(destino.z) < 0 || static_cast<int>(destino.z) > 5 || destino == kingPos) {
        return false;
    }
    int dx = static_cast<int>(destino.x - origen.x);
    int dz = static_cast<int>(destino.z - origen.z);
    int abs_dx = abs(dx);
    int abs_dz = abs(dz);
    int pc = abs(value);

    switch (pc) {
    case 1: // PEON
        return (((value > 0) && ((dx == 0 && dz == 1 && board[static_cast<int>(destino.x)][static_cast<int>(destino.z)] == 0) || (abs_dx == 1 && dz == 1 && board[static_cast<int>(destino.x)][static_cast<int>(destino.z)] != 0))) || ((value < 0) && ((dx == 0 && dz == -1 && board[static_cast<int>(destino.x)][static_cast<int>(destino.z)] == 0) || (abs_dx == 1 && dz == -1 && board[static_cast<int>(destino.x)][static_cast<int>(destino.z)] != 0))));
    case 3: // CABALLO
        return (abs_dx == 2 && abs_dz == 1) || (abs_dx == 1 && abs_dz == 2);
    case 6: // REY
        return ((abs_dx <= 1 && abs_dz <= 1) && !(dx == 0 && dz == 0));
    }
    if (pc == 2 || pc == 4 || pc == 5) { // TORRE, ALFIL, REINA
        bool valid = (pc == 2 && (dx == 0 || dz == 0)) ||
            (pc == 4 && (abs_dx == abs_dz)) ||
            (pc == 5 && (dx == 0 || dz == 0 || abs_dx == abs_dz));
        if (!valid || !(dx || dz)) return false;
        int step_x = (dx > 0) - (dx < 0);
        int step_z = (dz > 0) - (dz < 0);
        for (int ox = static_cast<int>(origen.x + step_x), oz = static_cast<int>(origen.z + step_z);
            ox != destino.x || oz != destino.z;
            ox += step_x, oz += step_z)
            if (board[ox][oz] != 0)
                return false;
        return true;
    }
    return false;
}
void Reglas::displayValidMoves(int value, vector2D origen, std::array<std::array<int, 6>, 5>& board, std::array<std::array<Losa, 6>, 5>& tiles) {
    for (int j = 0; j < 6; ++j) {
        for (int i = 0; i < 5; ++i) {
            if (moveChecker(value, origen, { static_cast<float>(i), static_cast<float>(j) }, board)) {
                if ((board[i][j] < 0 && value > 0) || (board[i][j] > 0 && value < 0)) {
                    tiles[static_cast<int>(origen.x)][static_cast<int>(origen.z)].setColor({ dangerous });
                    tiles[i][j].setColor({ danger });
                }
                else {
					tiles[i][j].setColor({ valid });
				}
            }
        }
    }
}
void Reglas::displayCastling(int value, vector2D origen, std::array<std::array<int, 6>, 5>& board, std::array<std::array<Losa, 6>, 5>& tiles) {
    int oz = (value < 0 ? 5 : 0);
    for (int i = 0; i<5; ++i){
        if (abs(value) == 6 && enroqueChecker(value < 0, origen, { static_cast<float>(i), static_cast<float>(oz) }, board)) {
            tiles[i][oz].setColor({ enroque });
        }
    }
}
void Reglas::displayDanger(vector2D posicion, std::array<std::array<Losa, 6>, 5>& tiles) {
    tiles[static_cast<int>(posicion.x)][static_cast<int>(posicion.z)].setColor({ danger });
}
void Reglas::displayDangerous(vector2D posicion, std::array<std::array<Losa, 6>, 5>& tiles) {
    tiles[static_cast<int>(posicion.x)][static_cast<int>(posicion.z)].setColor({ dangerous });
}
vector2D Reglas::pieceFinder(int value, std::array<std::array<int, 6>, 5>& board) {
    for (int j = 0; j < 6; ++j) {
        for (int i = 0; i < 5; ++i) {
            if (board[i][j] == value) {
                return { static_cast<float>(i), static_cast<float>(j) };                
            }
        }
    }
    return { -1, -1 };
}
bool Reglas::jaque(bool turnFlag, std::array<std::array<int, 6>, 5>& board, std::array<std::array<Losa, 6>, 5>& tiles) {
    int kingValue = (turnFlag ? 6 : -6);
    vector2D kingPos = pieceFinder(kingValue, board);
    if (kingPos.x == -1) return true; // REY NO ENCONTRADO
    
    for (int j = 0; j < 6; ++j) {
        for (int i = 0; i < 5; ++i) {
            int pc = board[i][j];
            if (pc == 0) continue;
            if ((turnFlag == 0 && pc <= 0) || (turnFlag == 1 && pc >= 0))
                continue; 

            vector2D piecePos = { static_cast<float>(i), static_cast<float>(j) };
            if (moveChecker(pc, piecePos, kingPos, board)) {
                displayDanger(kingPos, tiles); // REY EN PELIGRO
                displayDangerous(piecePos, tiles); // ATACANTE PELIGROSO
                return true; // JAQUE
            }
        }
    }
    return false;
}
bool Reglas::jaqueMate(bool turnFlag, std::array<std::array<int, 6>, 5>& board, std::array<std::array<Losa, 6>, 5>& tiles){ // (REQUIERE MÁS TESTING)
    int kingValue = (turnFlag ? 6 : -6);
    vector2D kingPos = pieceFinder(kingValue, board);
    if (kingPos.x == -1)
        return true;  // REY NO ENCONTRADO

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 6; j++) {

            int destVal = board[i][j];
            if (turnFlag == 0) {
                if (destVal >= 0)
                    continue;
            }
            else {
                if (destVal <= 0)
                    continue;
            }
            vector2D piecePos(static_cast<float>(i), static_cast<float>(j));

            // PRUEBA CADA POSIBLE DESTINO DE LA PIEZA ENEMIGA.
            for (int k = 0; k < 5; k++) {
                for (int l = 0; l < 6; l++) {
                    if (i == k && j == l)
                        continue;  
                    vector2D dest(static_cast<float>(k), static_cast<float>(l));

                    if (!moveChecker(destVal, piecePos, dest, board))
                        continue;  // MOV ILEGAL

                    // SIMULAR EL MOV.
                    std::array<std::array<int, 6>, 5> boardCopy = board;
                    boardCopy[k][l] = destVal;
                    boardCopy[i][j] = 0;

                    vector2D newKingPos;
                    if ((turnFlag == 0 && destVal == 6) || (turnFlag == 1 && abs(destVal) == 6))
                        newKingPos = dest;
                    else
                        newKingPos = pieceFinder(kingValue, boardCopy);
                    if (newKingPos.x == -1)
                        continue;  

                    // COMPRUEBA QUE ALGUNA DE LAS PIEZAS AMIGAS PUEDE ATACAR AL REY ENEMIGO
                    bool kingAttacked = false;
                    for (int x = 0; x < 5 && !kingAttacked; x++) {
                        for (int z = 0; z < 6 && !kingAttacked; z++) {
                            int origVal = boardCopy[x][z];
                            if (origVal == 0)
                                continue;
                            if (turnFlag == 0 && origVal <= 0)
                                continue;
                            if (turnFlag == 1 && origVal >= 0)
                                continue;
                            vector2D origPos(static_cast<float>(x), static_cast<float>(z));
                            if (moveChecker(origVal, origPos, newKingPos, boardCopy))
                                kingAttacked = true;
                        }
                    }
                    if (!kingAttacked)
                        return false;
                }
            }
        }
    }
    return true; // JAQUE MATE!
}
bool Reglas::enroqueChecker(bool turn, vector2D origenKing, vector2D destinoKing, std::array<std::array<int, 6>, 5>& board) {
    int rookVal = (turn ? -2 : 2);
    int oz = (turn ? 5 : 0);

    vector2D rookPos = { -1, -1 };
    for (int i = 0; i < 5; i++){
        if (board[i][oz] == rookVal)
            rookPos = { static_cast<float>(i), static_cast<float>(oz) };
    }
    int dir = static_cast<int>(rookPos.x - origenKing.x);
    if (rookPos.x == -1 || dir == 0) return false;
    dir = (dir > 0 ? 1 : -1);
    for (int i = static_cast<int>(origenKing.x) + dir; i != static_cast<int>(rookPos.x); i += dir)
        if (board[i][oz] != 0)
            return false;
    return (rookPos.x != -1 && (static_cast<float>(oz) == origenKing.z) && (origenKing.z == destinoKing.z) && (destinoKing.z == rookPos.z) && origenKing.x + (2 * dir) < 5 && destinoKing.x == (origenKing.x + (2 * dir)));
}
void Reglas::enroqueMove(bool turn, vector2D origenKing, vector2D destinoKing, std::array<std::array<int, 6>, 5>& board) {
    int rookVal = (turn ? -2 : 2);

    vector2D origenRook = { -1, -1 };
    for (int i = 0; i < 5; i++) {
        if (board[i][static_cast<int>(origenKing.z)] == rookVal)
            origenRook = { static_cast<float>(i), origenKing.z };
    }
    int dir = static_cast<int>(origenRook.x - origenKing.x);
    if (origenRook.x == -1 || dir == 0) return;
    dir = (dir > 0 ? 1 : -1);
    updateMov(rookVal, origenRook, {origenKing.x + static_cast<float>(dir), origenRook.z}, board);
    ETSIDI::play("sonidos/enroque.mp3");
    return;
}
void Reglas::updateMov(int value, vector2D origen, vector2D destino, std::array<std::array<int, 6>, 5>& board){
    if (origen.x != -1 && origen.z != -1 && destino.x != -1 && destino.z != -1) {         
        
        // CORONACION DEL PEON
        if (value == 1 && destino.z == 5) {
            ETSIDI::play("sonidos/coronacion.mp3");
            board[static_cast<int>(origen.x)][static_cast<int>(origen.z)] = 5; // Peon a Reina
        }
        else if (value == -1 && destino.z == 0) {
            ETSIDI::play("sonidos/coronacion.mp3");
            board[static_cast<int>(origen.x)][static_cast<int>(origen.z)] = -5; // Peon a Reina
        }

        int destVal = board[static_cast<int>(destino.x)][static_cast<int>(destino.z)];
        if (destVal == 0) {
            ETSIDI::play("sonidos/desplazamiento.mp3");
        }
        else {
            ETSIDI::play("sonidos/ataque.mp3");
        }
        // ACTUALIZAMOS MOVIMIENTO DEL COMPUTADOR
        board[static_cast<int>(destino.x)][static_cast<int>(destino.z)] = board[static_cast<int>(origen.x)][static_cast<int>(origen.z)];
        board[static_cast<int>(origen.x)][static_cast<int>(origen.z)] = 0;

        int pc = abs(value);
        char abrev = '?';
        switch (pc) {
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

        std::cout << (value < 0 ? "b" : "w") << " " << abrev << " " << col_orig << row_orig << " " << col_dest << row_dest << std::endl;
    }
}