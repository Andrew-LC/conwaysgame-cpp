#ifndef CONWAY_H
#define CONWAY_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include "GameUI.h"
#include "SDLContext.h"

#include <iostream>
#include <vector>

using Grid = std::vector<std::vector<bool>>;

#define CHECK(LIST, i, j) ((LIST)[(i)][(j)])

class Conway {
public:
  Conway(SDLContext* context, int width, int height);
  ~Conway();

  void init();
  void run();
  void handleEvents(SDL_Event& e);
  void render();
  void reset();
  bool running() { return isRunning; }

private:
  void initializeGrid();
  void updateGrid(int x, int y);
  void rules();

  int rows;
  int cols;
  int width;
  int height;
  int cellSize{20};
  Grid grid;
  bool isRunning;
  bool runSimulation{false};
  SDLContext* context;
};

#endif // CONWAY_H 
