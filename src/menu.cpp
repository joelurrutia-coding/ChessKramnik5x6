#include "menu.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

Menu::Menu(MenuScreen screen) : currentScreen(screen) {
    setScreen(screen);
}
void Menu::setScreen(MenuScreen screen) {
    currentScreen = screen;
    items.clear();
    (currentScreen == MENU_INICIO) ? menuStart() : menuGameOver();
}
void Menu::renderText(float y, const std::string& text) {
    glPushMatrix();
    glTranslatef(-0.7f, y, 0.0f);  // Alineamiento a izquierda
    glScalef(0.0005f, 0.001f, 0.001f);  // Escalado de texto
    for (char c : text) {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, c);
    }
    glPopMatrix();
}
void Menu::dibuja() {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glDisable(GL_DEPTH_TEST);
    glColor3f(1.0f, 1.0f, 1.0f);

    float y = 0.45f;
    float dy = -0.15f;
    for (const auto& line : items) {
        renderText(y, line);
        y += dy;
    }
    glEnable(GL_DEPTH_TEST);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}
void Menu::menuStart() {
    items.reserve(8);
    items.push_back("AJEDREZ KRAMNIK");
    items.push_back("Click izq | dcho : seleccionar | posicionar");
    items.push_back("m : vs maquina");
    items.push_back("g : guardar tablero actual");
    items.push_back("c : cargar ultimo tablero");
    items.push_back("v : vista 2D o 3D");
    items.push_back("t : tablero 'Esquinas opuestas' o 'Petty'");
    items.push_back("ENTER para comenzar");
}
void Menu::setWinner(const std::string& winner) {
    winnerText = winner;
}
void Menu::guardarScores(int whiteScore, int blackScore) {
    std::ofstream out("scores.txt");
    if (out.is_open()) {
        out << whiteScore << " " << blackScore;
        out.close();
    }
}
void Menu::cargarScores(int& whiteScore, int& blackScore) {
    std::ifstream in("scores.txt");
    if (in.is_open()) {
        in >> whiteScore >> blackScore;
        in.close();
    }
    else {
        std::cerr << "Error al cargar las puntuaciones.\n";
        whiteScore = 0;
        blackScore = 0;
    }
}
void Menu::setScores() {
    cargarScores(whiteScore, blackScore);
    if (winnerText == "BLANCO")
        whiteScore++;
    else if (winnerText == "NEGRO")
        blackScore++;
    std::cout << "Blanco " << whiteScore << " : " << blackScore << " Negro" << std::endl;
    guardarScores(whiteScore, blackScore);
}
void Menu::menuGameOver() {
    items.clear();
    items.reserve(7);
    items.push_back("FIN DEL JUEGO");
    items.push_back("GANADOR: " + winnerText);
    items.push_back(" ");
    items.push_back("BLANCO " + std::to_string(whiteScore) + " : " + std::to_string(blackScore) + " NEGRO");
    items.push_back(" ");
    items.push_back("r : Reiniciar");
    items.push_back("ESC para salir");
}