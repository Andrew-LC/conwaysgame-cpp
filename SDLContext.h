// SDLContext.h
#ifndef SDLCONTEXT_H
#define SDLCONTEXT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>

using Grid = std::vector<std::vector<bool>>;

class SDLContext {
public:
  SDLContext(SDL_Window *window);
  ~SDLContext();
  SDL_Renderer *getRenderer() { return renderer; }
  TTF_Font *getFont() { return font; }
  bool runSimulation(bool val);
  bool checkRunning();
  Grid& getGrid(); 
  void createGrid(int rows, int cols);
  SDL_Texture* getGridTexture() { return gridTexture; }
  SDL_Rect& getCameraRect() { return cameraRect; }
  SDL_Rect& getDestRect() { return destRect; }
  void updateCamera(int x, int y, float zoom);
  int getCellSize();
  void updateCellSize(int zoom);
  void drawGrid();

private:
  SDL_Renderer *renderer;
  TTF_Font *font;
  Grid grid;
  bool isRunning{false};
  SDL_Texture* gridTexture;
  SDL_Rect cameraRect{0, 0, 800, 500};
  SDL_Rect destRect{0, 0, 800, 500};
  int cellSize{20};
};

#endif // SDLCONTEXT_H
