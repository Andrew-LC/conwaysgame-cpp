#include "Conway.h"
#include <SDL2/SDL_events.h>
#include <vector>

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

 -> To check the diagonal sides we use this update grid[i+1][j+1] and grid[i+1][j-1]
*/

#define CHECK(LIST, i, j) ((LIST)[(i)][(j)])

Conway::Conway()
  : isRunning(false), window(nullptr), renderer(nullptr), rows(0), cols{0} {
}

Conway::~Conway() {
  clean();
}

void Conway::initializeGrid() {
  rows = 100;
  cols = 100;
  grid = Grid(rows, std::vector<bool>(cols, false));
}

void Conway::reset() {
  grid = Grid(rows, std::vector<bool>(cols, false));
  runSimulation = false;
}

bool Conway::init(const char *title, int width, int height) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
      std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError()
                << '\n';
      return false;
    }

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, width,
                              height, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
      std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError()
                << '\n';
      return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
      std::cerr << "Renderer could not be created! SDL_Error: "
                << SDL_GetError() << '\n';
      return false;
    }

    initializeGrid();
    isRunning = true;
    return true;
}

void Conway::run() {
  if (!init("Conway Game", 800, 600)) {
    std::cerr << "Failed to initialize!\n";
    return;
  }
  while (isRunning) {
    handleEvents();
    render();

    if(runSimulation){
      rules();
    }
  }
}

void Conway::handleEvents() {
  SDL_Event e;
  while (SDL_PollEvent(&e) != 0) {
    if (e.type == SDL_QUIT) {
      isRunning = false;
    }
    // Handle other events here (keyboard, mouse, etc.)
    if(e.type == SDL_MOUSEBUTTONDOWN) {
      int x = e.button.x;
      int y = e.button.y;
      updateGrid(x, y);
    }

    if(e.type == SDL_KEYDOWN){
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
}

void Conway::updateGrid(int x, int y) {
  int col = x / cellSize;
  int row = y / cellSize;

  std::cout << grid[row][col];
  grid[row][col] = !grid[row][col];
  std::cout << grid[row][col];
}

void Conway::render() {
  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
  SDL_RenderClear(renderer);

  // Render stuff here
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      if (grid[i][j]) {
	SDL_Rect cellRect = {j * cellSize, i * cellSize, cellSize, cellSize};
	SDL_RenderFillRect(renderer, &cellRect);
      }
    }
  }

  SDL_RenderPresent(renderer);
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

void Conway::clean() {
  if (renderer) {
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;
  }

  if (window) {
    SDL_DestroyWindow(window);
    window = nullptr;
  }

  SDL_Quit();
}
