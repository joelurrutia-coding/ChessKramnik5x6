#pragma once
#include "freeglut.h"
#include <string>
#include <vector>

enum MenuScreen {
    MENU_INICIO,
    MENU_FINAL
};

class Menu {
public:
    Menu(MenuScreen screen = MENU_INICIO);

    void setScreen(MenuScreen screen);
    void setWinner(const std::string& winner);
    void dibuja();

    void setScores();
    void guardarScores(int whiteScore, int blackScore);
    void cargarScores(int& whiteScore, int& blackScore);
    bool vsMaquina = false;
    bool modoPetty = false; 
    bool mostrarInstrucciones = false;
private:
    MenuScreen currentScreen;
    std::vector<std::string> items;
    std::string winnerText;
    int whiteScore, blackScore;

    void renderText(float y, const std::string& text, bool titleStyle);
    void menuStart();
    void menuGameOver();
};