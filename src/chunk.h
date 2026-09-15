#ifndef CHUNK_H
#define CHUNK_H

#include <vector>
#include <cstdint>

const int CHUNK_SIZE_X = 16;
const int CHUNK_SIZE_Y = 256;
const int CHUNK_SIZE_Z = 16;

enum BlockType : uint8_t {
    BLOCK_AIR = 0,
    BLOCK_GRASS = 1,
    BLOCK_DIRT = 2,
    BLOCK_STONE = 3,
    BLOCK_WOOD = 4,
    BLOCK_LEAVES = 5
};

class Chunk {
public:
    Chunk();
    ~Chunk();

    uint8_t blocks[CHUNK_SIZE_X][CHUNK_SIZE_Y][CHUNK_SIZE_Z];

    void generateTestTerrain();
    uint8_t getBlock(int x, int y, int z) const;
    void setBlock(int x, int y, int z, uint8_t type);
};

#endif
