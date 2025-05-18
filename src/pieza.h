#pragma once

#include "vector2D.h"
#include "color.h"
#include "plataforma.h"    
#include <array>
#include <string>
#include <memory>
#include <math.h>

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

    Pieza* crear(int pieceValue) const;
    inline void setColor(const Color& c) { color = c; }
    inline void setPosicion(float ix, float iz) { posicion = { ix, iz }; }
    virtual void dibuja() const {}

    inline std::array<std::array<int, 6>, 5>& getBoard() { return board; }
    inline vector2D getSeleccion() const { return seleccion; }

    void seleccionar(int ix, int iz, int turnFlag, Plataforma& platform);
    void deseleccionar();

    void setMode(bool omod);
    void guardarTablero(const std::string& filename, bool turnFlag);
    void cargarTablero(const std::string& filename, bool& turnFlag);
    void dibujarTablero() const;
};