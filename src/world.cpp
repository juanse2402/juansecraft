#include "world.h"
#include <cmath>

World::World() {}

World::~World() {
    for (auto& pair : chunks) {
        delete pair.second;
    }
    chunks.clear();
}

void World::loadChunk(int chunkX, int chunkZ) {
    std::pair<int, int> coords = {chunkX, chunkZ};
    if (chunks.find(coords) == chunks.end()) {
        Chunk* newChunk = new Chunk();
        newChunk->generateTestTerrain();
        chunks[coords] = newChunk;
    }
}

uint8_t World::getBlock(int x, int y, int z) const {
    int chunkX = std::floor(x / (float)CHUNK_SIZE_X);
    int chunkZ = std::floor(z / (float)CHUNK_SIZE_Z);

    auto it = chunks.find({chunkX, chunkZ});
    if (it != chunks.end()) {
        int localX = x - (chunkX * CHUNK_SIZE_X);
        int localZ = z - (chunkZ * CHUNK_SIZE_Z);
        return it->second->getBlock(localX, y, localZ);
    }
    return BLOCK_AIR;
}

void World::setBlock(int x, int y, int z, uint8_t type) {
    int chunkX = std::floor(x / (float)CHUNK_SIZE_X);
    int chunkZ = std::floor(z / (float)CHUNK_SIZE_Z);

    auto it = chunks.find({chunkX, chunkZ});
    if (it != chunks.end()) {
        int localX = x - (chunkX * CHUNK_SIZE_X);
        int localZ = z - (chunkZ * CHUNK_SIZE_Z);
        it->second->setBlock(localX, y, localZ, type);
    }
}
