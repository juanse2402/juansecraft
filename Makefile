CXX = i686-w64-mingw32-g++
CXXFLAGS = -march=i686 -mtune=pentium3 -mno-sse -mno-sse2 -O3 -Wall -Wextra -Ithird_party/SDL2/include
LDFLAGS = -Lthird_party/SDL2/lib -static-libgcc -static-libstdc++ -lmingw32 -lSDL2main -lSDL2 -lopengl32 -lglu32 -lm

all: voxel_engine.exe

voxel_engine.exe: src/main.cpp src/chunk.cpp src/chunk.h src/player.cpp src/player.h src/world.cpp src/world.h src/menu.cpp src/menu.h
	$(CXX) src/main.cpp src/chunk.cpp src/player.cpp src/world.cpp src/menu.cpp -o voxel_engine.exe $(CXXFLAGS) $(LDFLAGS)

clean:
	rm -f voxel_engine.exe SDL2.dll
