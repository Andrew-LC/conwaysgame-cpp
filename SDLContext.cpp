#include "SDLContext.h"
#include <iostream>

SDLContext::SDLContext(SDL_Window* window) {
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << '\n';
    }

    // Initialize SDL_ttf
    if (TTF_Init() == -1) {
        std::cerr << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
    }

    font = TTF_OpenFont("./assets/CascadiaCode-Regular.ttf", 18);
    if (font == nullptr) {
        std::cerr << "Font could not be loaded! SDL_ttf Error: " << TTF_GetError() << '\n';
    }
}

SDLContext::~SDLContext() {
    SDL_DestroyRenderer(renderer);
    TTF_CloseFont(font);
    TTF_Quit();  // Add this to quit SDL_ttf
}

bool SDLContext::runSimulation() {
  isRunning = !isRunning;
  return isRunning;
}
