#include "Conway.h"
#include "SDLContext.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>
#include <vector>

#define CHECK(LIST, i, j) ((LIST)[(i)][(j)])

Conway::Conway(SDLContext *context, int width, int height)
    : context(context), isRunning(false), runSimulation(false),
      width(width), height(height), rows(height / context->getCellSize()),
      cols(width / context->getCellSize()) {}

void Conway::initializeGrid() { 
    context->createGrid(rows, cols);
}

void Conway::reset() {
    context->createGrid(rows, cols);
    runSimulation = false;
}

void Conway::init() {
    initializeGrid();
    isRunning = true;
}

void Conway::handleEvents(SDL_Event &e) {
    if (e.type == SDL_MOUSEBUTTONDOWN) {
        int x = e.button.x;
        int y = e.button.y;
        if (y < height) {
            updateGrid(x, y);
        }
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
    int cellSize = context->getCellSize();
    int col = x / cellSize;
    int row = y / cellSize;
    
    // Apply camera offset
    SDL_Rect cameraRect = context->getCameraRect();
    col += cameraRect.x / cellSize;
    row += cameraRect.y / cellSize;
    
    if (row < rows && col < cols) {
        auto &grid = context->getGrid();
        grid[row][col] = !grid[row][col];
        std::cout << "Cell (" << col << ", " << row << ") toggled to "
                  << (grid[row][col] ? "alive" : "dead") << std::endl;
    } else {
        std::cout << "Click outside grid bounds: (" << col << ", " << row << ")" << std::endl;
    }
}

void Conway::render() {
    const auto &grid = context->getGrid();
    int cellSize = context->getCellSize();
    SDL_SetRenderTarget(context->getRenderer(), context->getGridTexture());
    SDL_SetRenderDrawColor(context->getRenderer(), 0, 0, 0, 255);
    SDL_RenderClear(context->getRenderer());
    SDL_SetRenderDrawColor(context->getRenderer(), 255, 255, 255, 255);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (grid[i][j]) {
                SDL_Rect cellRect = {j * cellSize, i * cellSize, cellSize, cellSize};
                SDL_RenderFillRect(context->getRenderer(), &cellRect);
            }
        }
    }
    SDL_SetRenderTarget(context->getRenderer(), nullptr);
    SDL_RenderCopy(context->getRenderer(), context->getGridTexture(), 
                   &context->getCameraRect(), &context->getDestRect());
    context->drawGrid();
}

void Conway::run() {
    if (runSimulation || context->checkRunning()) {
        rules();
    }
}

void Conway::rules() {
    auto &grid = context->getGrid();
    std::vector<std::vector<bool>> nextGrid = grid;
    
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
