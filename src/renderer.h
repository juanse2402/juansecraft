#ifndef RENDERER_H
#define RENDERER_H

#include "world.h"
#include "player.h"

class Renderer {
public:
    Renderer();
    ~Renderer();

    void init();
    void renderWorld(const World& world, const Player& player);
    void renderMenu();
};

#endif
