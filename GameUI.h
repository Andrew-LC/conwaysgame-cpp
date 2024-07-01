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
  void addButton(std::string text);
  void render();
  void handleEvents(SDL_Event &event);
  // Add methods for UI controls

private:
  SDL_Renderer *renderer;
  TTF_Font *font;
  // Add UI elements (buttons, sliders, etc.)
  vector<Button *> buttons;
};

#endif // GAME_UI
