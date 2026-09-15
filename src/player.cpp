#include "player.h"
#include <SDL2/SDL.h>
#include <cmath>
#include <algorithm>

Player::Player(float startX, float startY, float startZ)
    : x(startX), y(startY), z(startZ),
      vx(0.0f), vy(0.0f), vz(0.0f),
      yaw(-90.0f), pitch(0.0f),
      width(0.6f), height(1.8f),
      isOnGround(false) {}

Player::~Player() {}

void Player::mouseMove(int relX, int relY) {
    float sensitivity = 0.15f;
    yaw += relX * sensitivity;
    pitch -= relY * sensitivity;

    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;
}

void Player::handleInput(const uint8_t* state, float /*dt*/) {
    float speed = 4.3f;
    if (state[SDL_SCANCODE_LSHIFT]) {
        speed = 5.6f;
    }

    float radYaw = yaw * 3.1415926535f / 180.0f;
    float forwardX = std::cos(radYaw);
    float forwardZ = std::sin(radYaw);
    float rightX = -std::sin(radYaw);
    float rightZ = std::cos(radYaw);

    float moveX = 0.0f;
    float moveZ = 0.0f;

    if (state[SDL_SCANCODE_W]) {
        moveX += forwardX;
        moveZ += forwardZ;
    }
    if (state[SDL_SCANCODE_S]) {
        moveX -= forwardX;
        moveZ -= forwardZ;
    }
    if (state[SDL_SCANCODE_A]) {
        moveX += rightX;
        moveZ += rightZ;
    }
    if (state[SDL_SCANCODE_D]) {
        moveX -= rightX;
        moveZ -= rightZ;
    }

    float len = std::sqrt(moveX * moveX + moveZ * moveZ);
    if (len > 0.0f) {
        moveX = (moveX / len) * speed;
        moveZ = (moveZ / len) * speed;
    }

    vx = moveX;
    vz = moveZ;

    if (state[SDL_SCANCODE_SPACE] && isOnGround) {
        vy = 8.5f;
        isOnGround = false;
    }
}

bool Player::checkCollision(float nx, float ny, float nz, const World& world) const {
    float halfW = width / 2.0f;
    
    int minX = static_cast<int>(std::floor(nx - halfW));
    int maxX = static_cast<int>(std::floor(nx + halfW));
    int minY = static_cast<int>(std::floor(ny));
    int maxY = static_cast<int>(std::floor(ny + height));
    int minZ = static_cast<int>(std::floor(nz - halfW));
    int maxZ = static_cast<int>(std::floor(nz + halfW));

    for (int cx = minX; cx <= maxX; ++cx) {
        for (int cy = minY; cy <= maxY; ++cy) {
            for (int cz = minZ; cz <= maxZ; ++cz) {
                if (world.getBlock(cx, cy, cz) != BLOCK_AIR) {
                    return true;
                }
            }
        }
    }
    return false;
}

void Player::update(float dt, const World& world) {
    const float gravity = -25.0f;
    vy += gravity * dt;

    float newX = x + vx * dt;
    if (!checkCollision(newX, y, z, world)) {
        x = newX;
    } else {
        vx = 0.0f;
    }

    float newZ = z + vz * dt;
    if (!checkCollision(x, y, newZ, world)) {
        z = newZ;
    } else {
        vz = 0.0f;
    }

    float newY = y + vy * dt;
    if (!checkCollision(x, newY, z, world)) {
        y = newY;
        isOnGround = false;
    } else {
        if (vy < 0.0f) {
            isOnGround = true;
        }
        vy = 0.0f;
    }
}
