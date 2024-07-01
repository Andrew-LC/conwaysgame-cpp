#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include "Button.h"

#include <iostream>
#include <vector>

using Grid = std::vector<std::vector<bool>>;

#define CHECK(LIST, i, j) ((LIST)[(i)][(j)])

class Conway {
public:
  Conway();
  ~Conway();

  bool init(const char *title, int width, int height);
  void handleEvents();
  void update();
  void render();
  void clean();
  void run();
  void initializeGrid();
  void updateGrid(int x, int y);
  void rules();
  void reset();
  bool running() { return isRunning; }

private:
  int rows;
  int cols;
  int cellSize{20};
  Grid grid;
  bool isRunning;
  bool runSimulation{false};
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Texture* playerTex;
  int fontSize{18};
  TTF_Font* Font;
  Button* text;
};

#endif
