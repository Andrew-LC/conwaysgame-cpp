#ifndef BUTTON_H
#define BUTTON_H

#include "SDLContext.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class Button {
public:
  Button(SDLContext *context, int posx, int posy, std::string text);
  ~Button();
  void render();
  bool isClicked(int x, int y);

  template <typename Func> void handleClick(SDL_Event &e, Func lambda);

private:
  int posx;
  int posy;
  int width;
  int height;
  SDLContext *context;
  std::string text;
  SDL_Texture *tex;
  SDL_Color textColor{255, 255, 255};
  SDL_Color outlineColor{255, 255, 255};
  SDL_Rect rect;
  SDL_Rect outlineRect;
};

template <typename Func> void Button::handleClick(SDL_Event &e, Func lambda) {
  if (e.type == SDL_MOUSEBUTTONDOWN) {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    if (isClicked(mouseX, mouseY)) {
      lambda();
    }
  }
}

#endif // BUTTON_H
