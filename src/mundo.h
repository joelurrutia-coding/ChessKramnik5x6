#include "plataforma.h"
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
    Plataforma platform;   
    Pieza piezas;       
    Menu menu;          
    Computador computer;

    float x_ojo, y_ojo, z_ojo, angle, targetAngle;
    bool clickFlag, rotationFlag, fullscrnFlag, modelviewFlag, autopilotFlag,
         modeFlag, turnFlag, openingFlag, endFlag, jaqueFlag, blackCastlingF, whiteCastlingF;

    Mundo();

    void inicializa();
    void rotarOjo();
    void cambiarOjo();
    void modoVSmaquina();
    void dibuja();
    void tecla(unsigned char key);

    void leftClick(int mouseX, int mouseY);
    void rightClick(int mouseX, int mouseY);
};