#include "GameUI.h"
#include "Button.h"
#include "SDLContext.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <iostream>

#define CAMERA_WIDTH 800
#define CAMERA_HEIGHT 500

GameUI::GameUI(SDLContext *context) : context(context) {}

void GameUI::addButton(int posx, int posy, std::string text) {
  Button* button = new Button(context, posx, posy, text);
  buttons[text] = button;
}

void GameUI::handleEvents(SDL_Event &e) {
  if (e.type == SDL_KEYDOWN) {
    switch (e.key.keysym.sym) {
    case SDLK_UP:
      cameraY -= 10;
      break;
    case SDLK_DOWN:
      cameraY += 10;
      break;
    case SDLK_LEFT:
      cameraX -= 10;
      break;
    case SDLK_RIGHT:
      cameraX += 10;
      break;
    case SDLK_EQUALS: 
      zoom *= 1.1f;
      break;
    case SDLK_MINUS:
      zoom /= 1.1f;
      break;
    }
  }

  auto btn1 = getButton("Run Simulation");
  btn1->handleClick(e, [this]() { context->runSimulation(true); });
  auto btn2 = getButton("Pause");
  btn2->handleClick(e, [this]() { context->runSimulation(false); });

  context->updateCamera(cameraX, cameraY, zoom);
  context->updateCellSize(zoom);
}

void GameUI::controlUI() {
  addButton(200, 540, "Run Simulation");
  addButton(380, 540, "Pause");
  addButton(460, 540, "Reset");

  for (auto button : buttons) {
    button.second->render();
  }
}

void GameUI::conwayGrid(int width, int height, int cellSize) {
  context->drawGrid();
}

Button* GameUI::getButton(std::string text) {
  auto it = buttons.find(text);
  if (it != buttons.end()) {
    return it->second;
  }
  return nullptr;
}

void GameUI::render() {
  conwayGrid(800, 500, 20);
  controlUI();
}
