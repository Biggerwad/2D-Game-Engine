#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

// Global variables
static SDL_Window* window = nullptr;
static SDL_Renderer* renderer = nullptr;

// Initialize SDL
bool initialize() {
    SDL_SetAppMetadata("Snake Game", "1.0", "com.example.snakegame");

    if (SDL_Init(SDL_INIT_VIDEO) != true) {
        std::cerr << "Couldn't initialize SDL: " << SDL_GetError() << std::endl;
        return false;
    }

    if (SDL_CreateWindowAndRenderer("Snake Game", 640, 480, 0, &window, &renderer) != true) {
        std::cerr << "Couldn't create window/renderer: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_ShowWindow(window); // Ensure the window is visible
    return true;
}

// Handle input events
bool handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            return false;
        }
    }
    return true;
}

// Render frame
void renderFrame() {
    double now = static_cast<double>(SDL_GetTicks()) / 1000.0;
    float red = static_cast<float>(0.5 + 0.5 * SDL_sin(now));
    float green = static_cast<float>(0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 2 / 3));
    float blue = static_cast<float>(0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 4 / 3));

    SDL_SetRenderDrawColorFloat(renderer, red, green, blue, SDL_ALPHA_OPAQUE_FLOAT);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

// Cleanup resources
void cleanup() {
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    SDL_Quit();
}

// Main loop
int main(int argc, char* argv[]) {
    if (!initialize()) {
        cleanup();
        return 1;
    }

    bool running = true;
    while (running) {
        running = handleEvents();
        renderFrame();
        SDL_Delay(16); // Limit FPS to ~60
    }

    cleanup();
    return 0;
}