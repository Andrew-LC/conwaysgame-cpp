#include <SDL2/SDL.h>
#include "Game.h"

// Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int main(int argc, char *args[]) {
  Game game(SCREEN_WIDTH, SCREEN_HEIGHT);
  game.run();
  return 0;
}
