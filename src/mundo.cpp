#include "mundo.h"
#include "reglas.h"

#include <math.h>
#include <vector>
#include <iostream>
#include "freeglut.h"
#include <GL/glu.h>

Pantalla currentScreen = START;

Mundo::Mundo() :
    x_ojo(3.0f), y_ojo(4.9f), z_ojo(-1.0f),
    angle(-1.5707963268f), targetAngle(angle),
    modeFlag(false), turnFlag(false), clickFlag(true), rotationFlag(false), 
    modelviewFlag(true), fullscrnFlag(false), 
    endFlag(false), jaqueFlag(false), autopilotFlag(false), openingFlag(true)
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
    std::cout << (autopilotFlag ? "Humano VS Maquina (Seleccionado)\n" : "Humano VS Humano (Seleccionado)\n");
}
void Mundo::inicializa() {
    x_ojo = 3.0f;
    y_ojo = 4.9f;
    z_ojo = -1.0f;
    angle = -1.5707963268f;
    turnFlag = false;
    clickFlag = true;
    rotationFlag = false;
    piezas.deseleccionar();
    platform.resetTileColors();
    piezas.setMode(modeFlag);
    endFlag = false;
    openingFlag = true;
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
        piezas.dibuja();
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
        if (key == 'r' || key == 'R') {
            currentScreen = START;
            inicializa();
            glutPostRedisplay();
            return;
        }
        if (key == 27) {
            exit(0);
        }
        break;
    default:
        break;
    }
    glutPostRedisplay();
}
void Mundo::leftClick(int mouseX, int mouseY) {
    GLint viewport[4];               // X, Y, ANCHO, ALTURA DE LA PANTALLA
    GLdouble modelview[16];          // 4x4 CAMARA + MODELO DE VISTA
    GLdouble projection[16];         // 4x4 MATRIZ DE PROYECCION
    GLfloat depthZ;                  // PROFUNDIDAD DEL CLICK EN 3D
    GLdouble worldX, worldY, worldZ; // COORDENADAS 3D DEL MUNDO EN PANTALLA

    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    glGetDoublev(GL_PROJECTION_MATRIX, projection);
    glGetIntegerv(GL_VIEWPORT, viewport);

    // CONVERSION COORDENADAS DE PANTALLA (X,Y,Z) A TABLERO (X,Z) 
    mouseY = viewport[3] - mouseY;
    glReadPixels(mouseX, mouseY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depthZ);
    gluUnProject(mouseX, mouseY, depthZ,
        modelview, projection, viewport,
        &worldX, &worldY, &worldZ);

    int boardX = static_cast<int>(worldX - 0.5f);
    int boardZ = static_cast<int>(worldZ - 0.5f);

    if (boardX >= 0 && boardX < 5 && boardZ >= 0 && boardZ < 6 && clickFlag) {
        piezas.seleccionar(boardX, boardZ, turnFlag, platform);
    }
}
void Mundo::rightClick(int mouseX, int mouseY) {
    GLint viewport[4];
    GLdouble modelview[16], projection[16];
    GLfloat depthZ = 0.0f;
    GLdouble worldX, worldY, worldZ;

    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    glGetDoublev(GL_PROJECTION_MATRIX, projection);
    glGetIntegerv(GL_VIEWPORT, viewport);

    mouseY = viewport[3] - mouseY;
    glReadPixels(mouseX, mouseY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depthZ);
    gluUnProject(mouseX, mouseY, depthZ,
        modelview, projection, viewport,
        &worldX, &worldY, &worldZ);

    int boardX = static_cast<int>(worldX - 0.5f);
    int boardZ = static_cast<int>(worldZ - 0.5f);

    vector2D destino = { static_cast<float>(boardX), static_cast<float>(boardZ) };
    if (destino.x >= 0 && destino.x < 5 && destino.z >= 0 && destino.z < 6) {
        vector2D seleccion = piezas.getSeleccion();
        if (seleccion.x != -1 && seleccion.z != -1) {
            int piece = piezas.getBoard()[static_cast<int>(seleccion.x)][static_cast<int>(seleccion.z)];
            if ((turnFlag == 0 && piece > 0) || (turnFlag == 1 && piece < 0)) {
                if ((seleccion.z == destino.z && seleccion.x == destino.x) ||
                    !Reglas::moveChecker(piece, seleccion, destino, piezas.getBoard()))
                    return;
                piezas.getBoard()[static_cast<int>(destino.x)][static_cast<int>(destino.z)] = piece;
                piezas.getBoard()[static_cast<int>(seleccion.x)][static_cast<int>(seleccion.z)] = 0;
                imprimirMov(piece, seleccion, destino);

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
                    std::cout << "Jaque!\n";
                }
                else {
                    jaqueFlag = false;
                }
                if (endFlag == 0 && autopilotFlag && turnFlag) {
                    if (openingFlag) {
                        computer.makeMoveOpening(openingFlag, turnFlag, autopilotFlag, piezas.getBoard());
                        openingFlag = false;
                    }
                    else if (jaqueFlag) {
                        endFlag = !computer.makeMoveKingSafe(turnFlag, autopilotFlag, piezas.getBoard());
                        //std::cout << "makeMoveSafeKing\n";
                    }
                    else if (!jaqueFlag) {
                        endFlag = !computer.makeMove(turnFlag, autopilotFlag, piezas.getBoard());
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
                        std::cout << "Jaque!\n";
                    }
                }
            }
        }
    }
    glutPostRedisplay();
    // COMPROBACION FIN DEL JUEGO.
    if (endFlag) {
        std::string winner = (turnFlag == 0) ? "BLANCO" : "NEGRO";
        std::cout << "Jaque Mate!\n";
        std::cout << "Ganador: " << winner << std::endl;
        menu.setWinner(winner);
		menu.setScores();
        currentScreen = GAME_OVER;
        return;
    }
}
void Mundo::imprimirMov(int piece, vector2D origen, vector2D destino) const {
    char turno = (turnFlag == 0) ? 'w' : 'b';
    char abrev = '?';
    switch (abs(piece)) {
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
    std::cout << turno << " " << abrev << " " << col_orig << row_orig << " " << col_dest << row_dest << std::endl;
}