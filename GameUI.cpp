#include "GameUI.h"
#include "Button.h"
#include <vector>

GameUI::GameUI(SDL_Renderer* renderer, TTF_Font* font):
  renderer(renderer), font(font) {}

void GameUI::addButton(int posx, int posy, std::string text) {
  Button* button = new Button(posx, posy, text, font, renderer);
  buttons.push_back(button);
}

void GameUI::controlUI() {
  addButton(200, 540, "Run Simulation");
  addButton(380, 540, "Pause");
  addButton(460, 540, "Reset");

  for (auto button : buttons) {
    button->render();
  }
}

void GameUI::conwayGrid(int width, int height, int cellSize) {
  int rows = height / cellSize;
  int cols = width / cellSize;

  // Set the draw color to grey for grid lines
  SDL_SetRenderDrawColor(renderer, 0x80, 0x80, 0x80, 0xFF);

  // Draw vertical grid lines
  for (int j = 0; j <= cols; ++j) {
    int x = j * cellSize;
    SDL_RenderDrawLine(renderer, x, 0, x, rows * cellSize);
  }

  // Draw horizontal grid lines
  for (int i = 0; i <= rows; ++i) {
    int y = i * cellSize;
    SDL_RenderDrawLine(renderer, 0, y, cols * cellSize, y);
  }
}

void GameUI::render() {
  conwayGrid(800, 500, 20);
  controlUI();
}
