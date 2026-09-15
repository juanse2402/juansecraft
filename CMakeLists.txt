cmake_minimum_required(VERSION 3.10)
project(VoxelEngineRetro CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compilación cruzada MinGW-w64 para i686 (Athlon XP / Pentium 3 - sin SSE2)
set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_C_COMPILER i686-w64-mingw32-gcc)
set(CMAKE_CXX_COMPILER i686-w64-mingw32-g++)

# Banderas de optimización estricta para Athlon XP (i686, sin SSE2)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=i686 -mtune=pentium3 -mno-sse -mno-sse2 -O3 -Wall -Wextra")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -march=i686 -mtune=pentium3 -mno-sse -mno-sse2 -O3")

# Directorios de inclusión para dependencias estáticas o headers (SDL2, OpenGL)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/third_party/SDL2/include)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/third_party/SDL2/lib)

# Archivos fuente del motor voxel
file(GLOB SOURCES "src/*.cpp" "src/*.c")

add_executable(voxel_engine ${SOURCES})

# Enlace estático/dinámico para Windows (MinGW)
target_link_libraries(voxel_engine -lmingw32 -lSDL2main -lSDL2 -lopengl32 -lglu32 -lm)
