#include "SDLContext.h"
#include "utils.h"
#include <vector>
#include <iostream>

SDLContext::SDLContext(SDL_Window *window) {
    renderer = catchErrorNULL(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED),
                 "Renderer could not be created! SDL_Error: ");
    
    // Initialize SDL_ttf
    catchError(TTF_Init() == -1, "SDL_ttf could not initialize! SDL_ttf Error: ");
    
    font = TTF_OpenFont("./assets/CascadiaCode-Regular.ttf", 18);
    if (font == nullptr) {
        std::cerr << "Font could not be loaded! SDL_ttf Error: " << TTF_GetError() << '\n';
    }

    gridTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                                    SDL_TEXTUREACCESS_TARGET, 800, 800);
}

SDLContext::~SDLContext() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(gridTexture);
    TTF_CloseFont(font);
    TTF_Quit();
}

bool SDLContext::runSimulation(bool val) {
    isRunning = val;
    return isRunning;
}

bool SDLContext::checkRunning() {
    return isRunning;
}

Grid& SDLContext::getGrid() {
    return grid;
}

void SDLContext::createGrid(int rows, int cols) {
    grid = Grid(rows, std::vector<bool>(cols, false));
}

void SDLContext::updateCamera(int x, int y, float zoom) {
    cameraRect.x = x;
    cameraRect.y = y;
    cameraRect.w = 800 / zoom;
    cameraRect.h = 500 / zoom;
}


int SDLContext::getCellSize(){
  return cellSize;
}

void SDLContext::updateCellSize(int zoom) {
  cellSize *= zoom;
}

void SDLContext::drawGrid() {
  int height = 500;
  int width = 800;
  int rows = height / cellSize;
  int cols = width / cellSize;

  SDL_SetRenderTarget(getRenderer(), getGridTexture());
  SDL_SetRenderDrawColor(getRenderer(), 0x80, 0x80, 0x80, 0xFF);

  for (int j = 0; j <= cols; ++j) {
    int x = j * cellSize;
    SDL_RenderDrawLine(getRenderer(), x, 0, x, rows * cellSize);
  }

  for (int i = 0; i <= rows; ++i) {
    int y = i * cellSize;
    SDL_RenderDrawLine(getRenderer(), 0, y, cols * cellSize, y);
  }

  SDL_SetRenderTarget(getRenderer(), nullptr);
  SDL_RenderCopy(getRenderer(),getGridTexture(), 
                 &getCameraRect(), &getDestRect());
}
