// Game.h
#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include "SDLContext.h"
#include "GameUI.h"
#include "Conway.h"

class Game {
public:
    Game(int width, int height);
    void run();

private:
    void init();
    void handleEvents();
    void update();
    void render();
    void close();

    bool isRunning;
    int width;
    int height;
    SDL_Window* window;
    SDLContext* context;
    GameUI* ui;
    Conway* conway;
};

#endif // GAME_H

// Game.cpp
#include "Game.h"
#include <iostream>

Game::Game(int width, int height) : width(width), height(height), window(nullptr), context(nullptr), ui(nullptr), conway(nullptr) {}

void Game::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << '\n';
        return;
    }

    window = SDL_CreateWindow("Conway Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << '\n';
        return;
    }

    context = new SDLContext(window);
    ui = new GameUI(context);
    conway = new Conway(800, 500, context);

    isRunning = true;
}

void Game::run() {
    init();
    while (isRunning) {
        handleEvents();
        update();
        render();
    }
    close();
}

void Game::render() {
    SDL_Renderer* renderer = context->getRenderer();
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(renderer);

    ui->render();
    conway->render();

    SDL_RenderPresent(renderer);
}

// ... other Game methods ...

// GameUI.h
#ifndef GAMEUI_H
#define GAMEUI_H

#include "SDLContext.h"
#include "Button.h"
#include <vector>

class GameUI {
public:
    GameUI(SDLContext* context);
    void render();
    // ... other methods ...

private:
    SDLContext* context;
    std::vector<Button*> buttons;
};

#endif // GAMEUI_H

// GameUI.cpp
#include "GameUI.h"

GameUI::GameUI(SDLContext* context) : context(context) {
    // Initialize buttons using context
    buttons.push_back(new Button(context, 200, 540, "Run Simulation"));
    buttons.push_back(new Button(context, 380, 540, "Pause"));
    buttons.push_back(new Button(context, 460, 540, "Reset"));
}

void GameUI::render() {
    for (auto button : buttons) {
        button->render();
    }
    // ... other rendering ...
}

// Conway.h
#ifndef CONWAY_H
#define CONWAY_H

#include "SDLContext.h"
#include <vector>

class Conway {
public:
    Conway(int width, int height, SDLContext* context);
    void render();
    // ... other methods ...

private:
    SDLContext* context;
    std::vector<std::vector<bool>> grid;
    // ... other members ...
};

#endif // CONWAY_H

// Conway.cpp
#include "Conway.h"

Conway::Conway(int width, int height, SDLContext* context) : context(context) {
    // Initialize grid
}

void Conway::render() {
    SDL_Renderer* renderer = context->getRenderer();
    // Render the Conway grid using the renderer
}

// Button.h
#ifndef BUTTON_H
#define BUTTON_H

#include "SDLContext.h"
#include <string>

class Button {
public:
    Button(SDLContext* context, int x, int y, const std::string& text);
    void render();

private:
    SDLContext* context;
    SDL_Texture* texture;
    SDL_Rect rect;
    // ... other members ...
};

#endif // BUTTON_H

// Button.cpp
#include "Button.h"

Button::Button(SDLContext* context, int x, int y, const std::string& text) : context(context) {
    SDL_Surface* surface = TTF_RenderText_Solid(context->getFont(), text.c_str(), {255, 255, 255, 255});
    texture = SDL_CreateTextureFromSurface(context->getRenderer(), surface);
    SDL_FreeSurface(surface);
    
    rect = {x, y, /* width */, /* height */};
}

void Button::render() {
    SDL_RenderCopy(context->getRenderer(), texture, nullptr, &rect);
}
