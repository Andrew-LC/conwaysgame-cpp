#include "Game.h"
#include "Conway.h"
#include "SDLContext.h"
#include "GameUI.h"
#include "utils.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <iostream>


Game::Game(int width, int height) : width(width), height(height) {}

void Game::init() {
  catchError(SDL_Init(SDL_INIT_VIDEO), "Error: Could not initialize sdl init");

  window = catchErrorNULL(SDL_CreateWindow(
      "Conway Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width,
      height, SDL_WINDOW_SHOWN), "Error: could not initialize window");

  context = new SDLContext(window);
  ui = new GameUI(context);
  conway = new Conway(context, 800, 800);
  conway->init();
  isRunning = true;
}

void Game::close() {
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
    ui->handleEvents(e);
  }
}

void Game::render() {
  SDL_Renderer* renderer = context->getRenderer();
  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
  SDL_RenderClear(renderer);

  ui->render();
  conway->render();

  SDL_RenderPresent(renderer);
}
