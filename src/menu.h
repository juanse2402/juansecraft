#ifndef MENU_H
#define MENU_H

enum GameState {
    STATE_MENU,
    STATE_PLAYING,
    STATE_EXIT
};

class Menu {
public:
    Menu();
    ~Menu();

    int selectedOption; // 0: Singleplayer, 1: Options, 2: Quit
    void handleInput(int key);
    void update();
};

#endif
