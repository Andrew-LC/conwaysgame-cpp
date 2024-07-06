#include "utils.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL.h>
#include <string>

void catchError(int code, std::string err) { 
  if (code < 0) {
    std::cout << err << "%s. SDL ERROR: "
	      << SDL_GetError() << std::endl;
    exit(1);
  }
}
