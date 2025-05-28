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

#include "ETSIDI.h"

GLUquadric* getSharedQuadric() {
    static GLUquadric* sharedQuad = gluNewQuadric();
    return sharedQuad; //Devuelve el puntero
}
Pieza::Pieza() : //Constructor por defecto
    size(1.0f),
    color(none),
    posicion(0.0f, 0.0f), 
    seleccion(-1, -1), //No hay selección
	board({}),      //Inicializa el tablero vacío
	othermode(false)  //Inicializa el modo de juego a false (modo ESQUINAS OPUESTAS)
{}
Pieza::~Pieza() {} 

Pieza* Pieza::crear(int pieceValue) const { //Crea una nueva pieza según el valor de la pieza
    if (pieceValue == 0)
		return nullptr;     //Si el valor es 0, no hay pieza

	int type = abs(pieceValue); //Usamos abs para obtener el valor absoluto, ya que el tipo de pieza no depende del color.
    Pieza* piece = nullptr;     //Este puntero apuntará a la pieza creada

	switch (type) {         //Según el valor absoluto de pieceValue, crea dinámicamente un objeto del tipo adecuado. 
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
	if (piece) {            //Este if, define el color de la pieza según el valor de pieceValue.
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
    ETSIDI::play("sonidos/seleccion.mp3");
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
    ETSIDI::play("sonidos/guardar.mp3");
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
    ETSIDI::play("sonidos/carga.mp3");
   // std::cout << "Ultimo tablero guardado cargado exitosamente\n";
}
void Pieza::dibujarTablero() const {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 6; ++j) {
            int value = board[i][j];
            if (value == 0)
                continue;

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