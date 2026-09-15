#include "menu.h"

Menu::Menu() : selectedOption(0) {}

Menu::~Menu() {}

void Menu::handleInput(int key) {
    if (key == 1) { // Up
        selectedOption--;
        if (selectedOption < 0) selectedOption = 2;
    } else if (key == 2) { // Down
        selectedOption++;
        if (selectedOption > 2) selectedOption = 2;
    }
}

void Menu::update() {}
