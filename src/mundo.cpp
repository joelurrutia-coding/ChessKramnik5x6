#include "mundo.h"
#include "reglas.h"

#include <math.h>
#include <vector>
#include <iostream>
#include "freeglut.h"
#include <GL/glu.h>

Pantalla currentScreen = START;

Mundo::Mundo() :
    // CAMARA
    x_ojo(3.0f), y_ojo(4.9f), z_ojo(-1.0f),
    // ROTACION
    angle(-1.5707963268f), targetAngle(angle),
    // FLAGS DE INTERFAZ GRAFICA
    clickFlag(true), rotationFlag(false), modelviewFlag(true), fullscrnFlag(false),  
    // FLAGS DE INTERFAZ DE JUEGO
    turnFlag(false), jaqueFlag(false), modeFlag(false), autopilotFlag(false),
    // ONE-TIME-USE FLAGS (POR PARTIDA) 
    openingFlag(true), endFlag(false), blackCastlingF(true), whiteCastlingF(true)
{}
void Mundo::rotarOjo() {
    if (!rotationFlag)
        return;
    clickFlag = false;
    angle += 0.05f;
    if (angle >= targetAngle) {
        angle = targetAngle;
        rotationFlag = false;
        clickFlag = true;
    }
    if (modelviewFlag) {
        x_ojo = 3.0f + 4.5f * cos(angle);
        z_ojo = 3.5f + 4.5f * sin(angle);
    }
    else {
        x_ojo = 3.0f + 0.1f * cos(angle);
        z_ojo = 3.499f + 0.1f * sin(angle);
    }
}
void Mundo::cambiarOjo() {
    if (modelviewFlag) {
        if (!turnFlag) {
            x_ojo = 3.0f;
            y_ojo = 4.9f;
            z_ojo = -1.0f;
        }
        else {
            x_ojo = 3.0f;
            y_ojo = 4.9f;
            z_ojo = 8.0f;
        }
    }
    else {
        if (!turnFlag) {
            x_ojo = 3.0f;
            y_ojo = 6.45f;
            z_ojo = 3.499f;
        }
        else {
            x_ojo = 3.0f;
            y_ojo = 6.45f;
            z_ojo = 3.501f;
        }
    }
}
void Mundo::modoVSmaquina() {
    autopilotFlag = !autopilotFlag;
    //std::cout << (autopilotFlag ? "Humano VS Maquina (Seleccionado)\n" : "Humano VS Humano (Seleccionado)\n");
}
void Mundo::inicializa() {
    std::system("cls");
    x_ojo = 3.0f;
    y_ojo = 4.9f;
    z_ojo = -1.0f;
    angle = -1.5707963268f;
    turnFlag = rotationFlag = endFlag = false;
    clickFlag = openingFlag = blackCastlingF = whiteCastlingF = true;
    piezas.deseleccionar();
    platform.resetTileColors();
    piezas.setMode(modeFlag);
    cambiarOjo();
}
void Mundo::dibuja() {
    switch (currentScreen) {
    case START:
        menu.setScreen(MENU_INICIO);
        menu.dibuja();
        break;
    case PLAYING:
        gluLookAt(x_ojo, y_ojo, z_ojo,  // POSICION DEL OJO
                  3.0f, -1.0f, 3.5f,    // DONDE MIRA EL OJO
                  0.0f, 1.0f, 0.0f);    // VECTOR HACIA ARRIBA (+Y)
        glPushMatrix();
        glTranslatef(3.0f, 0.2f, 3.5f);
        glColor4ub(255, 255, 255, 255);
        glRotatef(90, 0, -1, 0);
        glutWireSphere(10, 20, 17);
        glPopMatrix();

        platform.dibuja();
        piezas.dibujarTablero();
        break;
    case GAME_OVER:
        menu.setScreen(MENU_FINAL);
        menu.dibuja();
        break;
    default:
        break;
    }
}
void Mundo::tecla(unsigned char key) {
    switch (currentScreen) {
    case START:
        if (key == 13) {  // ENTER
            currentScreen = PLAYING;
            glutPostRedisplay();
            return;
        }
        else if (key == 'f' || key == 'F') {
            if (fullscrnFlag == 0) {
                glutFullScreen();
            }
            else {
                glutReshapeWindow(1408, 792);
                glutPositionWindow(52, 0);
            }
            fullscrnFlag = !fullscrnFlag;
            return;
        }
        break;
    case PLAYING:
        if (!rotationFlag) {
            switch (key) {
            case 'f': case 'F':
                if (fullscrnFlag==0){
                    glutFullScreen();
                }
                else {
                    glutReshapeWindow(1408, 792);
                    glutPositionWindow(52, 0);
                }
                fullscrnFlag = !fullscrnFlag;
                break;
            case 't': case 'T':
                modeFlag = !modeFlag;
                inicializa();
                break;
            case 'g': case 'G':
                piezas.guardarTablero("lastboard.txt", turnFlag);
                break;
            case 'c': case 'C':
                inicializa();
                piezas.cargarTablero("lastboard.txt", turnFlag);
                openingFlag = false;
                if (turnFlag) {
                    rotationFlag = true;
                    targetAngle = angle + 3.14159265f;
                }
                break;
            case 'v': case 'V':
                modelviewFlag = !modelviewFlag;
                cambiarOjo();
                break;
            case 'm': case 'M':
                modoVSmaquina();
                break;
            case 27:
                exit(0);
                break;
            default:
                break;
            }
        }
        break;
    case GAME_OVER:
        if (key == 13) { // ENTER
            currentScreen = START;
            inicializa();
            glutPostRedisplay();
            return;
        }
        if (key == 27) { // ESC
            exit(0);
        }
        break;
    default:
        break;
    }
    glutPostRedisplay();
}
void Mundo::leftClick(int mouse_x, int mouse_y) {
    GLint viewport[4];                  // X, Y, ANCHO, ALTURA DE LA PANTALLA
    GLdouble modelview[16];             // 4x4 CAMARA + MODELO DE VISTA
    GLdouble projection[16];            // 4x4 MATRIZ DE PROYECCION
    GLfloat depth_z = 0;                // PROFUNDIDAD DEL CLICK EN 3D
    GLdouble world_x, world_y, world_z; // COORDENADAS 3D DEL MUNDO EN PANTALLA

    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    glGetDoublev(GL_PROJECTION_MATRIX, projection);
    glGetIntegerv(GL_VIEWPORT, viewport);

    // CONVERSION COORDENADAS DE PANTALLA (X,Y,Z) A TABLERO (X,Z) 
    mouse_y = viewport[3] - mouse_y;
    glReadPixels(mouse_x, mouse_y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth_z);
    gluUnProject(mouse_x, mouse_y, depth_z,
        modelview, projection, viewport,
        &world_x, &world_y, &world_z);

    int board_x = static_cast<int>(world_x - 0.5f);
    int board_z = static_cast<int>(world_z - 0.5f);

    if (board_x >= 0 && board_x < 5 && board_z >= 0 && board_z < 6 && clickFlag) {
        piezas.seleccionar(board_x, board_z, turnFlag, platform);
        bool castling = (turnFlag ? blackCastlingF : whiteCastlingF);
        int pc = piezas.getBoard()[board_x][board_z];
        if (castling && abs(pc) == 6) Reglas::displayCastling(pc, { static_cast<float>(board_x), static_cast<float>(board_z) }, piezas.getBoard(), platform.getTiles());
    }
}
void Mundo::rightClick(int mouse_x, int mouse_y) {
    GLint viewport[4];
    GLdouble modelview[16], projection[16];
    GLfloat depth_z = 0.0f;
    GLdouble world_x, world_y, world_z;

    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    glGetDoublev(GL_PROJECTION_MATRIX, projection);
    glGetIntegerv(GL_VIEWPORT, viewport);

    mouse_y = viewport[3] - mouse_y;
    glReadPixels(mouse_x, mouse_y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth_z);
    gluUnProject(mouse_x, mouse_y, depth_z,
        modelview, projection, viewport,
        &world_x, &world_y, &world_z);

    int board_x = static_cast<int>(world_x - 0.5f);
    int board_z = static_cast<int>(world_z - 0.5f);

    vector2D destino = { static_cast<float>(board_x), static_cast<float>(board_z) };
    if (destino.x >= 0 && destino.x < 5 && destino.z >= 0 && destino.z < 6) {
        vector2D seleccion = piezas.getSeleccion();
        if (seleccion.x != -1 && seleccion.z != -1) {
            int value = piezas.getBoard()[static_cast<int>(seleccion.x)][static_cast<int>(seleccion.z)];
            if ((turnFlag == 0 && value > 0) || (turnFlag == 1 && value < 0)) {

                if (seleccion.z == destino.z && seleccion.x == destino.x)
                    return;
                else if (((turnFlag && blackCastlingF) || (!turnFlag && whiteCastlingF)) && Reglas::enroqueChecker(turnFlag, seleccion, destino, piezas.getBoard())) {
                    Reglas::enroqueMove(turnFlag, seleccion, destino, piezas.getBoard());
                    if (turnFlag)
                        blackCastlingF = false;
                    else
                        whiteCastlingF = false;
                }
                else if (!Reglas::moveChecker(value, seleccion, destino, piezas.getBoard()))
                    return;
                
                // ACTUALIZAMOS E IMPRIMIMOS EL MOVIMIENTO
                Reglas::updateMov(value, seleccion, destino, piezas.getBoard());

                piezas.deseleccionar();
                platform.resetTileColors();
                if (!autopilotFlag && turnFlag) {
                    openingFlag = false;
                }
                turnFlag = !turnFlag;
                rotationFlag = true;
                targetAngle = angle + 3.14159265f;

                if (Reglas::jaque(turnFlag, piezas.getBoard(), platform.getTiles())) {
                    endFlag = true;
                    targetAngle = angle;
                    rotationFlag = false;
                    //std::cout << "JaqueMate!\n";
				}
				else if (Reglas::jaqueMate(!turnFlag, piezas.getBoard(), platform.getTiles())) {
					endFlag = true;
					turnFlag = !turnFlag;
                    //std::cout << "JaqueMate!\n";
				}
                else if (Reglas::jaque(!turnFlag, piezas.getBoard(), platform.getTiles())) {
                    jaqueFlag = true;
                    //std::cout << "Jaque!\n";
                }
                else {
                    jaqueFlag = false;
                }
                if (endFlag == 0 && autopilotFlag && turnFlag) {
                    if (openingFlag) {
                        computer.makeMoveOpening(openingFlag, turnFlag, autopilotFlag, piezas.getBoard());
                        openingFlag = false;
                        platform.resetTileColors();
                        //std::cout << "makeMoveOpening\n";
                    }
                    else if (jaqueFlag) {
                        endFlag = !computer.makeMoveKingSafe(turnFlag, autopilotFlag, piezas.getBoard());
                        platform.resetTileColors();
                        //std::cout << "makeMoveSafeKing\n";
                    }
                    else if (!jaqueFlag) {
                        endFlag = !computer.makeMove(turnFlag, autopilotFlag, piezas.getBoard());
                        platform.resetTileColors();
                        //std::cout << "makeMove\n";
                    }
                    turnFlag = !turnFlag;
                    targetAngle = angle;
                    rotationFlag = false;
                    if (Reglas::jaque(turnFlag, piezas.getBoard(), platform.getTiles())) {
                        endFlag = true;
                        //std::cout << "JaqueMate!\n";
                    }
                    else if (Reglas::jaqueMate(!turnFlag, piezas.getBoard(), platform.getTiles())) {
                        endFlag = true;
                        turnFlag = !turnFlag;
                        //std::cout << "JaqueMate!\n";
                    }
                    else if (Reglas::jaque(!turnFlag, piezas.getBoard(), platform.getTiles())) {
                        //std::cout << "Jaque!\n";
                    }
                }
            }
        }
    }
    glutPostRedisplay();
    // COMPROBACION FIN DEL JUEGO.
    if (endFlag) {
        std::string winner = (turnFlag == 0) ? "BLANCO" : "NEGRO";
        //std::cout << "Jaque Mate!\n";
        //std::cout << "Ganador: " << winner << std::endl;
        menu.setWinner(winner);
		menu.setScores();
        currentScreen = GAME_OVER;
        return;
    }
}