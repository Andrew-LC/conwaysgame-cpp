#include "Game.h"
#include "Conway.h"
#include "GameUI.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <iostream>

Game::Game(int width, int height) : width(width), height(height) {}

void Game::init() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError()
              << '\n';
  }

  window = SDL_CreateWindow("Conway Game", SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, width, height,
                            SDL_WINDOW_SHOWN);
  if (window == nullptr) {
    std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError()
              << '\n';
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == nullptr) {
    std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError()
              << '\n';
  }

  // Initialize SDL_ttf
  if (TTF_Init() == -1) {
    std::cerr << "SDL_ttf could not initialize! SDL_ttf Error: "
              << TTF_GetError() << std::endl;
  }

  font = TTF_OpenFont("./assets/CascadiaCode-Regular.ttf", 18);
  if (font == nullptr) {
    std::cerr << "Font could not be loaded! SDL_Error: " << SDL_GetError()
              << '\n';
  }

  // Initialize the ui
  ui = new GameUI(renderer, font);
  conway = new Conway(800, 800, renderer);
  conway->init();
  isRunning = true;
}

void Game::close() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void Game::run() {
  init();
  while (isRunning) {
    handleEvents();
    render();
    conway->run();
  }
  close();
}

void Game::handleEvents() {
  SDL_Event e;
  while (SDL_PollEvent(&e) != 0) {
    if (e.type == SDL_QUIT) {
      isRunning = false;
    }
    conway->handleEvents(e);
  }
}

void Game::render() {
  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
  SDL_RenderClear(renderer);

  ui->render();
  conway->render();

  SDL_RenderPresent(renderer);
}
