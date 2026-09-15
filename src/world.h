#ifndef WORLD_H
#define WORLD_H

#include "chunk.h"
#include <unordered_map>
#include <utility>

struct HashPair {
    template <class T1, class T2>
    size_t operator()(const std::pair<T1, T2>& p) const {
        auto hash1 = std::hash<T1>{}(p.first);
        auto hash2 = std::hash<T2>{}(p.second);
        return hash1 ^ (hash2 << 1);
    }
};

class World {
public:
    World();
    ~World();

    std::unordered_map<std::pair<int, int>, Chunk*, HashPair> chunks;

    void loadChunk(int chunkX, int chunkZ);
    uint8_t getBlock(int x, int y, int z) const;
    void setBlock(int x, int y, int z, uint8_t type);
};

#endif
