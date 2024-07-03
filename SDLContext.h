// SDLContext.h
#ifndef SDLCONTEXT_H
#define SDLCONTEXT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class SDLContext {
public:
  SDLContext(SDL_Window *window);
  ~SDLContext();
  SDL_Renderer *getRenderer() { return renderer; }
  TTF_Font *getFont() { return font; }
  bool runSimulation();

private:
  SDL_Renderer *renderer;
  TTF_Font *font;
  bool isRunning{false};
};

#endif // SDLCONTEXT_H
