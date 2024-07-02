#ifndef GAME_UI_H
#define GAME_UI_H

#include "Button.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>

using std::vector;

class GameUI {
public:
  GameUI(SDL_Renderer *renderer, TTF_Font *font);
  void addButton(int posx, int posy, std::string text);
  void render();
  void conwayGrid(int width, int height, int cellSize);
  void controlUI();
  void handleEvents(SDL_Event& e);

private:
  SDL_Renderer *renderer;
  TTF_Font *font;
  vector<Button *> buttons;
};

#endif // GAME_UI
