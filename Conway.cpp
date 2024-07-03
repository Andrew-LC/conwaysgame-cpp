#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>
#include "Conway.h"
#include "SDLContext.h"

/*
[[0, 0, 0, 0, 0]
 [0, 0, 1, 0, 0]
 [0, 1, 1, 0, 0]
 [0, 0, 1, 1, 0]
 [0, 0, 0, 0, 0]]

 first alive cell: i = 1, j =  2

 -> First we can just update the i value with +1 and -1

    to go up and down the row i.e grid[i+1][j] and grid[i-1][j]
 -> Then do the same with j to go back and forth within col by one step

 -> To check the diagonal sides we use this update grid[i+1][j+1] and
grid[i+1][j-1]
*/


#define CHECK(LIST, i, j) ((LIST)[(i)][(j)])

Conway::Conway(SDLContext *context, int width, int height)
  : context(context), isRunning(false), width(width), height(height) {
  rows = height;
  cols = width;
}

void Conway::initializeGrid() {
  try {
    grid = Grid(rows, std::vector<bool>(cols, false));
  } catch (const std::bad_alloc &e) {
    std::cerr << "Error: Failed to allocate memory for grid" << std::endl;
    throw;
  }
}

void Conway::reset() {
  grid = Grid(rows, std::vector<bool>(cols, false));
  runSimulation = false;
}

void Conway::init() {
  initializeGrid();
  std::cout << "Grid: " << cols << " " << rows << std::endl;
  isRunning = true;
}


void Conway::handleEvents(SDL_Event& e) {
    // Handle other events here (keyboard, mouse, etc.)
    if (e.type == SDL_MOUSEBUTTONDOWN) {
      int x = e.button.x;
      int y = e.button.y;
      if(y < 500)
	updateGrid(x, y);
    }

    if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
      case SDLK_RETURN:
        std::cout << "Running simulation\n";
        runSimulation = true;
        break;
      case SDLK_ESCAPE:
        reset();
        break;
      }
    }
}

void Conway::updateGrid(int x, int y) {
  int col = x / cellSize;
  int row = y / cellSize;

  std::cout << col << " " << row << std::endl;

  std::cout << grid[row][col];
  grid[row][col] = !grid[row][col];
  std::cout << grid[row][col];
}

void Conway::render() {
  // // Render stuff here
  SDL_SetRenderDrawColor(context->getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      if (grid[i][j]) {
        SDL_Rect cellRect = {j * cellSize, i * cellSize, cellSize, cellSize};
        SDL_RenderFillRect(context->getRenderer(), &cellRect);
      }
    }
  }
}

void Conway::run() {
  if(runSimulation){
    rules();
  }
}

void Conway::rules() {
  /*
    Rule 1: Any live cell with fewer than two live neighbours dies, as if by
    underpopulation.
    Rule 2: Any live cell with two or three live neighbours
    lives on to the next generation.
    Rule 3: Any live cell with more than three
    live neighbours dies, as if by overpopulation.
    Rule 4: Any dead cell with
    exactly three live neighbours becomes a live cell, as if by reproduction.
  */
  Grid nextGrid = grid;

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols;
         ++j) { // Assuming you have a 'cols' member variable
      int aliveCount = 0;

      // Check all 8 neighbors
      for (int x = -1; x <= 1; ++x) {
        for (int y = -1; y <= 1; ++y) {
          if (x == 0 && y == 0)
            continue; // Skip the current cell

          int ni = i + x;
          int nj = j + y;

          if (ni >= 0 && ni < rows && nj >= 0 && nj < cols &&
              CHECK(grid, ni, nj)) {
            aliveCount++;
          }
        }
      }

      // Apply Conway's rules
      if (CHECK(grid, i, j)) {
        // Live cell
        if (aliveCount < 2 || aliveCount > 3) {
          nextGrid[i][j] = false; // Cell dies
        }
      } else {
        // Dead cell
        if (aliveCount == 3) {
          nextGrid[i][j] = true; // Cell becomes alive
        }
      }
    }
  }

  // Update the grid with the next generation
  grid = nextGrid;
}
