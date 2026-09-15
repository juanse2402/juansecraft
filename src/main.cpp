#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#include <cmath>
#include "chunk.h"
#include "player.h"
#include "world.h"
#include "menu.h"
#include "renderer.h"

int main(int, char*[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Error SDL_Init: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "Voxel Engine Retro - Minecraft 1.0 Style (Playable Version)",
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

    Renderer renderer;
    renderer.init();

    GameState gameState = STATE_MENU;
    Menu menu;
    World world;
    Player player(8.0f, 65.0f, 8.0f);

    world.loadChunk(0, 0);

    Uint32 lastTime = SDL_GetTicks();
    bool running = true;
    SDL_Event event;

    while (running) {
        Uint32 currentTime = SDL_GetTicks();
        float dt = (currentTime - lastTime) / 1000.0f;
        if (dt > 0.05f) dt = 0.05f;
        lastTime = currentTime;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            if (gameState == STATE_MENU) {
                if (event.type == SDL_KEYDOWN) {
                    if (event.key.keysym.sym == SDLK_UP) {
                        menu.handleInput(1);
                    } else if (event.key.keysym.sym == SDLK_DOWN) {
                        menu.handleInput(2);
                    } else if (event.key.keysym.sym == SDLK_RETURN) {
                        if (menu.selectedOption == 0) {
                            gameState = STATE_PLAYING;
                            SDL_SetRelativeMouseMode(SDL_TRUE);
                        } else if (menu.selectedOption == 2) {
                            running = false;
                        }
                    }
                }
            } else if (gameState == STATE_PLAYING) {
                if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
                    gameState = STATE_MENU;
                    SDL_SetRelativeMouseMode(SDL_FALSE);
                }
                if (event.type == SDL_MOUSEMOTION) {
                    player.mouseMove(event.motion.xrel, event.motion.yrel);
                }
            }
        }

        if (gameState == STATE_PLAYING) {
            const Uint8* keystate = SDL_GetKeyboardState(NULL);
            player.handleInput(keystate, dt);
            player.update(dt, world);
        }

        if (gameState == STATE_MENU) {
            glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        } else {
            glClearColor(0.5f, 0.7f, 1.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluPerspective(70.0, 800.0 / 600.0, 0.1, 1000.0);

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();

            float radYaw = player.yaw * 3.1415926535f / 180.0f;
            float radPitch = player.pitch * 3.1415926535f / 180.0f;

            float lookX = player.x + std::cos(radYaw) * std::cos(radPitch);
            float lookY = player.y + 1.62f + std::sin(radPitch);
            float lookZ = player.z + std::sin(radYaw) * std::cos(radPitch);

            gluLookAt(
                player.x, player.y + 1.62f, player.z,
                lookX, lookY, lookZ,
                0.0f, 1.0f, 0.0f
            );

            renderer.renderWorld(world, player);
        }

        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
