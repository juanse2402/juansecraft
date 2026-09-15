#ifndef PLAYER_H
#define PLAYER_H

#include "chunk.h"

class Player {
public:
    Player(float startX, float startY, float startZ);
    ~Player();

    // Posición del jugador (coordenadas del mundo)
    float x, y, z;
    // Velocidad de movimiento
    float vx, vy, vz;
    // Orientación de la cámara (ángulos de Euler)
    float yaw, pitch;

    // Dimensiones de la caja de colisión AABB (Ancho, Alto)
    float width;
    float height;

    bool isOnGround;

    void handleInput(const uint8_t* state, float dt);
    void update(float dt, const Chunk& chunk);
    void mouseMove(int relX, int relY);

private:
    bool checkCollision(float nx, float ny, float nz, const Chunk& chunk) const;
};

#endif
