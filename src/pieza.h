#pragma once

#include "vector2D.h"
#include "color.h"
#include "tablero.h"    
#include <array>
#include <string>
#include <memory>
#include <cmath>

GLUquadric* getSharedQuadric();

class Pieza {
protected: // Miembros accesibles por las clases derivadas.
    float size;         
    Color color;        
    vector2D posicion;  

    std::array<std::array<int, 6>, 5> board;  // 5 COLUMNAS × 6 FILAS
    vector2D seleccion;                       
    bool othermode;                           

public: // Miembros accesibles desde cualquier parte en la que se añade la clase.
    Pieza();
    virtual ~Pieza();

    inline void setColor(const Color& c) { color = c; }
    inline void setPosicion(float ix, float iz) {
        posicion.x = ix;
        posicion.z = iz;
    }
    virtual void dibujaIndividual() const {}

    std::array<std::array<int, 6>, 5>& getBoard();
    vector2D getSeleccion() const;
    void deseleccionar();
    void seleccionar(int ix, int iz, int turnFlag, Tablero& platform);

    void guardarTablero(const std::string& filename, bool turnFlag);
    void cargarTablero(const std::string& filename, bool& turnFlag);
    void setMode(bool omod);

    Pieza* createPiece(int pieceValue) const;
    void dibuja() const;
};