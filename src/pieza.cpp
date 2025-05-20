#include "pieza.h"
#include "freeglut.h"
#include <fstream>
#include <iostream>

#include "peon.h"
#include "torre.h"
#include "caballo.h"
#include "alfil.h"
#include "reina.h"
#include "rey.h"

#include "reglas.h"

GLUquadric* getSharedQuadric() {
    static GLUquadric* sharedQuad = gluNewQuadric();
    return sharedQuad;
}
Pieza::Pieza() :
    size(1.0f),
    color(none),
    posicion(0.0f, 0.0f),
    seleccion(-1, -1), board({}),
    othermode(false)
{}
Pieza::~Pieza() {}

Pieza* Pieza::crear(int pieceValue) const {
    if (pieceValue == 0)
        return nullptr;
    int type = abs(pieceValue);
    Pieza* piece = nullptr;
    switch (type) {
    case 1:
        piece = new Peon;
        break;
    case 2:
        piece = new Torre;
        break;
    case 3:
        piece = new Caballo;
        break;
    case 4:
        piece = new Alfil;
        break;
    case 5:
        piece = new Reina;
        break;
    case 6:
        piece = new Rey;
        break;
    default:
        break;
    }
    if (piece) {
        if (pieceValue < 0)
            piece->setColor(black);
        else
            piece->setColor(white);
    }
    return piece;
}

void Pieza::seleccionar(int ix, int iz, int turnFlag, Plataforma& platform) {
    int pc = board[ix][iz];
    if (pc == 0)
        return;
    if ((turnFlag == 0 && pc < 0) || (turnFlag == 1 && pc > 0))
        return;
    seleccion = vector2D(static_cast<float>(ix), static_cast<float>(iz));
    platform.resetTileColors();
    Reglas::displayValidMoves(pc, seleccion, board, platform.getTiles());
}
void Pieza::deseleccionar() {
    seleccion = vector2D(-1, -1);
}

void Pieza::setMode(bool omod) {
    othermode = omod;
    if (!othermode) {
        // ESQUINAS OPUESTAS
        std::array<std::array<int, 6>, 5> initBoard = { {
            { 2,  1,  0,  0, -1, -6 },
            { 3,  1,  0,  0, -1, -5 },
            { 4,  1,  0,  0, -1, -4 },
            { 5,  1,  0,  0, -1, -3 },
            { 6,  1,  0,  0, -1, -2 }
        } };
        board = initBoard;
    }
    else {
        // PETTY
        std::array<std::array<int, 6>, 5> initBoard = { {
            { 5,  1,  0,  0, -1, -5 },
            { 6,  1,  0,  0, -1, -6 },
            { 4,  1,  0,  0, -1, -4 },
            { 3,  1,  0,  0, -1, -3 },
            { 2,  1,  0,  0, -1, -2 }
        } };
        board = initBoard;
    }
    deseleccionar();
}
void Pieza::guardarTablero(const std::string& filename, bool turnFlag) {
    deseleccionar();
    std::ofstream file(filename);
    if (!file) {
        //std::cerr << "Error. No se pudo guardar el tablero.\n";
        return;
    }
    for (int z = 0; z < 6; ++z) {
        for (int x = 0; x < 5; ++x) {
            file << board[x][z] << ' ';
        }
        file << '\n';
    }
    file << turnFlag << '\n';
    //std::cout << "Ultimo tablero guardado exitosamente.\n";
}
void Pieza::cargarTablero(const std::string& filename, bool& turnFlag) {
    std::ifstream file(filename);
    if (!file) {
        //std::cerr << "Error. No se pudo cargar el ultimo tablero guardado.\n";
        return;
    }
    for (int z = 0; z < 6; ++z) {
        for (int x = 0; x < 5; ++x) {
            file >> board[x][z];
        }
    }
    file >> turnFlag;
   // std::cout << "Ultimo tablero guardado cargado exitosamente\n";
}
void Pieza::dibujarTablero() const {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 6; ++j) {
            int value = board[i][j];
            if (value == 0)
                continue;
            // Coronazion del peon
            if (value == 1 && j == 5) {
				value = 5; // Reina
                const_cast<std::array<std::array<int, 6>, 5>&>(board)[i][j] = value;
			}
			else if (value == -1 && j == 0) {
				value = -5; // Reina
                const_cast<std::array<std::array<int, 6>, 5>&>(board)[i][j] = value;
            }
            Pieza* piece = crear(value);
            if (!piece)
                continue;
            piece->setPosicion(static_cast<float>(i + 1), static_cast<float>(j + 1));
            if (i == static_cast<int>(seleccion.x) && j == static_cast<int>(seleccion.z)) {
                Color c = piece->color;
                c.a = 150;
                piece->setColor(c);
            }
            piece->dibuja();
            delete piece;
        }
    }
}