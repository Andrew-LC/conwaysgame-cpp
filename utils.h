#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <stdlib.h> // Needed for exit()
#include <SDL2/SDL.h>
#include <string>

void catchError(int code, std::string err);
template<typename T>
T* catchErrorNULL(T* ptr, std::string err);

#endif // UTILS_H

template<typename T>
T* catchErrorNULL(T* ptr, std::string err) { 
  if (ptr == NULL) {
    std::cout << err << "%s. SDL ERROR: "
	      << SDL_GetError() << std::endl;
    exit(1);
  }

  return ptr;
}
