#ifndef PLAYER_H
#define PLAYER_H

#include "world.h"

class Player {
public:
    Player(float startX, float startY, float startZ);
    ~Player();

    float x, y, z;
    float vx, vy, vz;
    float yaw, pitch;
    float width;
    float height;
    bool isOnGround;

    void handleInput(const uint8_t* state, float dt);
    void update(float dt, const World& world);
    void mouseMove(int relX, int relY);

private:
    bool checkCollision(float nx, float ny, float nz, const World& world) const;
};

#endif
