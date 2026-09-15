#include "chunk.h"
#include <cstring>

Chunk::Chunk() {
    std::memset(blocks, 0, sizeof(blocks));
}

Chunk::~Chunk() {}

void Chunk::generateTestTerrain() {
    for (int x = 0; x < CHUNK_SIZE_X; ++x) {
        for (int z = 0; z < CHUNK_SIZE_Z; ++z) {
            // Suelo de piedra hasta la altura 60
            for (int y = 0; y < 60; ++y) {
                blocks[x][y][z] = BLOCK_STONE;
            }
            // Capa de tierra de 60 a 63
            for (int y = 60; y < 63; ++y) {
                blocks[x][y][z] = BLOCK_DIRT;
            }
            // Bloque de pasto en la superficie (63)
            blocks[x][63][z] = BLOCK_GRASS;
        }
    }
}

uint8_t Chunk::getBlock(int x, int y, int z) const {
    if (x < 0 || x >= CHUNK_SIZE_X || y < 0 || y >= CHUNK_SIZE_Y || z < 0 || z >= CHUNK_SIZE_Z) {
        return BLOCK_AIR;
    }
    return blocks[x][y][z];
}

void Chunk::setBlock(int x, int y, int z, uint8_t type) {
    if (x < 0 || x >= CHUNK_SIZE_X || y < 0 || y >= CHUNK_SIZE_Y || z < 0 || z >= CHUNK_SIZE_Z) {
        return;
    }
    blocks[x][y][z] = type;
}
