#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "GameUI.h"
#include "Conway.h"

class Game {
public:
  Game(int width, int height);
  void run();

private:
  void init();
  void handleEvents();
  void update();
  void render();
  void close();

  bool isRunning;
  int width{0};
  int height{0};
  SDL_Window *window;
  SDL_Renderer *renderer;
  TTF_Font *font;
  Conway* conway;
  GameUI* ui;
};

#endif // GAME_H
