#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#include <cmath>
#include "chunk.h"
#include "player.h"

int main(int, char*[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Error SDL_Init: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "Voxel Engine Retro - Minecraft 1.0 Style (Athlon XP / GL 2.1)",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        800, 600,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
    );

    if (!window) {
        std::cerr << "Error SDL_CreateWindow: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    if (!glContext) {
        std::cerr << "Error SDL_GL_CreateContext: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetSwapInterval(1);

    // Capturar cursor para la vista en primera persona
    SDL_SetRelativeMouseMode(SDL_TRUE);

    glEnable(GL_DEPTH_TEST);

    Chunk sampleChunk;
    sampleChunk.generateTestTerrain();

    // Spawn del jugador en el centro del chunk, sobre la superficie (Y=65)
    Player player(8.0f, 65.0f, 8.0f);

    Uint32 lastTime = SDL_GetTicks();
    bool running = true;
    SDL_Event event;

    while (running) {
        Uint32 currentTime = SDL_GetTicks();
        float dt = (currentTime - lastTime) / 1000.0f;
        if (dt > 0.05f) dt = 0.05f; // Limitar delta time para estabilidad física
        lastTime = currentTime;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) {
                running = false;
            }
            if (event.type == SDL_MOUSEMOTION) {
                player.mouseMove(event.motion.xrel, event.motion.yrel);
            }
        }

        const Uint8* keystate = SDL_GetKeyboardState(NULL);
        player.handleInput(keystate, dt);
        player.update(dt, sampleChunk);

        // Renderizado OpenGL 2.1
        glClearColor(0.5f, 0.7f, 1.0f, 1.0f); // Color cielo clásico de Minecraft
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(70.0, 800.0 / 600.0, 0.1, 1000.0);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        // Calcular vista en primera persona
        float radYaw = player.yaw * 3.1415926535f / 180.0f;
        float radPitch = player.pitch * 3.1415926535f / 180.0f;

        float lookX = player.x + std::cos(radYaw) * std::cos(radPitch);
        float lookY = player.y + 1.62f + std::sin(radPitch); // 1.62 altura de ojos clásica
        float lookZ = player.z + std::sin(radYaw) * std::cos(radPitch);

        gluLookAt(
            player.x, player.y + 1.62f, player.z,
            lookX, lookY, lookZ,
            0.0f, 1.0f, 0.0f
        );

        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
