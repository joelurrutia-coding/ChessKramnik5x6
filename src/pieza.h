#pragma once

#include "vector2D.h"
#include "color.h"
#include "plataforma.h"    
#include <array>
#include <string>
#include <memory>
#include <math.h>

GLUquadric* getSharedQuadric(); //Dbuja primitivas curvas. La función definida getSharedQuadric, permite reutilizar el puntero.

class Pieza {
protected: //Miembros accesibles por las clases derivadas.
    float size;              //Tamaño de la pieza
    Color color;             //Color de la pieza (ej. blanco o negro)
    vector2D posicion;       //Posición (x, y) en el tablero


    std::array<std::array<int, 6>, 5> board;  //Representación del tablero
    vector2D seleccion;                       //Posición seleccionada               
    bool othermode;                           //Tipo de modo                  

public: //Miembros accesibles desde cualquier parte en la que se añade la clase.

    Pieza();                    //Constructor por defecto
    virtual ~Pieza();           //Destructor virtual

    Pieza* crear(int pieceValue) const;     //Crea una nueva pieza
    inline void setColor(const Color& c) { color = c; } //Settea el color
    inline void setPosicion(float ix, float iz) { posicion = { ix, iz }; }  //Settea la posición
    virtual void dibuja() const {}      //Dibuja. Como es virtual, puede ser sobrescrita

    inline std::array<std::array<int, 6>, 5>& getBoard() { return board; }
    inline vector2D getSeleccion() const { return seleccion; }      //Devuelve la posición tipo vector2D

    void seleccionar(int ix, int iz, int turnFlag, Plataforma& platform); //Selecciona una posición en el tablero
    void deseleccionar();

    void setMode(bool omod);        //Cambia el modo de juego, cambiando la matriz que define el tablero
    void guardarTablero(const std::string& filename, bool turnFlag); //Guarda el tablero en un archivo
    void cargarTablero(const std::string& filename, bool& turnFlag); //Carga el tablero desde el archivo
    void dibujarTablero() const;
};