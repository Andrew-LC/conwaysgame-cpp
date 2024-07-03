#include "GameUI.h"
#include "Button.h"
#include "SDLContext.h"
#include <iostream>

GameUI::GameUI(SDLContext* context): context(context) {}

void GameUI::addButton(int posx, int posy, std::string text) {
  Button* button = new Button(context, posx, posy, text);
  buttons[text] = button;
}

void GameUI::controlUI() {
  addButton(200, 540, "Run Simulation");
  addButton(380, 540, "Pause");
  addButton(460, 540, "Reset");

  for (auto button : buttons) {
    button.second->render();
  }
}

void GameUI::handleEvents(SDL_Event &e) {
  auto btn1 = getButton("Run Simulation");
  btn1->handleClick(e, [this](){
   context->runSimulation();
   std::cout << context->runSimulation() << std::endl;
  });
}


void GameUI::conwayGrid(int width, int height, int cellSize) {
  int rows = height / cellSize;
  int cols = width / cellSize;

  // Set the draw color to grey for grid lines
  SDL_SetRenderDrawColor(context->getRenderer(), 0x80, 0x80, 0x80, 0xFF);

  // Draw vertical grid lines
  for (int j = 0; j <= cols; ++j) {
    int x = j * cellSize;
    SDL_RenderDrawLine(context->getRenderer(), x, 0, x, rows * cellSize);
  }

  // Draw horizontal grid lines
  for (int i = 0; i <= rows; ++i) {
    int y = i * cellSize;
    SDL_RenderDrawLine(context->getRenderer(), 0, y, cols * cellSize, y);
  }
}

Button* GameUI::getButton(std::string text) {
  auto it = buttons.find(text);
  if (it != buttons.end()) {
    return it->second;
  }
}

void GameUI::render() {
  conwayGrid(800, 500, 20);
  controlUI();
}
