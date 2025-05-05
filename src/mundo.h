#include "tablero.h"
#include "pieza.h"  
#include "menu.h"
#include "computador.h" 

enum Pantalla {
    START,
    PLAYING,
    GAME_OVER
};

class Mundo
{
public:
    Tablero platform;   
    Pieza piezas;       
    Menu menu;          
    Computador computer;

    float x_ojo, y_ojo, z_ojo, angle, targetAngle;
    bool modeFlag, turnFlag, clickFlag, rotationFlag, endFlag, modelviewFlag, fullscrnFlag, autopilotFlag, jaqueFlag, openingFlag;

    Mundo();

    void inicializa();
    void rotarOjo();
    void cambiarOjo();
    void modoVSmaquina();
    void dibuja();
    void tecla(unsigned char key);
    void leftClick(int mouseX, int mouseY);
    void rightClick(int mouseX, int mouseY);
    void imprimirMov(int piece, vector2D origen, vector2D destino) const;
};