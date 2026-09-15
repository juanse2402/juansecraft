#include "renderer.h"
#include <GL/gl.h>
#include <vector>

Renderer::Renderer() {}

Renderer::~Renderer() {}

void Renderer::init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

void Renderer::renderWorld(const World& world, const Player& /*player*/) {
    for (auto& pair : world.chunks) {
        Chunk* chunk = pair.second;
        int chunkX = pair.first.first;
        int chunkZ = pair.first.second;

        int worldStartX = chunkX * CHUNK_SIZE_X;
        int worldStartZ = chunkZ * CHUNK_SIZE_Z;

        for (int x = 0; x < CHUNK_SIZE_X; ++x) {
            for (int y = 0; y < CHUNK_SIZE_Y; ++y) {
                for (int z = 0; z < CHUNK_SIZE_Z; ++z) {
                    uint8_t block = chunk->blocks[x][y][z];
                    if (block == BLOCK_AIR) continue;

                    float wx = worldStartX + x;
                    float wy = y;
                    float wz = worldStartZ + z;

                    glBegin(GL_QUADS);
                    if (block == BLOCK_GRASS) glColor3f(0.3f, 0.8f, 0.3f);
                    else if (block == BLOCK_DIRT) glColor3f(0.55f, 0.27f, 0.07f);
                    else if (block == BLOCK_STONE) glColor3f(0.5f, 0.5f, 0.5f);
                    else glColor3f(0.6f, 0.4f, 0.2f);

                    // Cara Superior
                    glVertex3f(wx, wy + 1.0f, wz);
                    glVertex3f(wx + 1.0f, wy + 1.0f, wz);
                    glVertex3f(wx + 1.0f, wy + 1.0f, wz + 1.0f);
                    glVertex3f(wx, wy + 1.0f, wz + 1.0f);

                    // Cara Inferior
                    glVertex3f(wx, wy, wz + 1.0f);
                    glVertex3f(wx + 1.0f, wy, wz + 1.0f);
                    glVertex3f(wx + 1.0f, wy, wz);
                    glVertex3f(wx, wy, wz);

                    // Cara Frontal
                    glVertex3f(wx, wy, wz + 1.0f);
                    glVertex3f(wx + 1.0f, wy, wz + 1.0f);
                    glVertex3f(wx + 1.0f, wy + 1.0f, wz + 1.0f);
                    glVertex3f(wx, wy + 1.0f, wz + 1.0f);

                    // Cara Trasera
                    glVertex3f(wx + 1.0f, wy, wz);
                    glVertex3f(wx, wy, wz);
                    glVertex3f(wx, wy + 1.0f, wz);
                    glVertex3f(wx + 1.0f, wy + 1.0f, wz);

                    // Cara Izquierda
                    glVertex3f(wx, wy, wz);
                    glVertex3f(wx, wy, wz + 1.0f);
                    glVertex3f(wx, wy + 1.0f, wz + 1.0f);
                    glVertex3f(wx, wy + 1.0f, wz);

                    // Cara Derecha
                    glVertex3f(wx + 1.0f, wy, wz + 1.0f);
                    glVertex3f(wx + 1.0f, wy, wz);
                    glVertex3f(wx + 1.0f, wy + 1.0f, wz);
                    glVertex3f(wx + 1.0f, wy + 1.0f, wz + 1.0f);

                    glEnd();
                }
            }
        }
    }
}
