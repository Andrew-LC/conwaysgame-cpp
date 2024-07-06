#ifndef GAME_UI_H
#define GAME_UI_H

#include "Button.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "SDLContext.h"
#include <map>
#include <string>

class GameUI {
public:
  GameUI(SDLContext* context);
  void addButton(int posx, int posy, std::string text);
  void render();
  void conwayGrid(int width, int height, int cellSize);
  void controlUI();
  void handleEvents(SDL_Event& e);
  Button* getButton(std::string text);

private:
  std::map<std::string, Button*> buttons;
  SDLContext* context;
  int cameraX{0};
  int cameraY{0};
  float zoom{1.0f};
};

#endif // GAME_UI
