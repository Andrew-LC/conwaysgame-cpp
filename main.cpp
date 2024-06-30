#include <SDL2/SDL.h>
#include <Conway.h>

// Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int main(int argc, char* args[]) {
    Conway game;
    game.run();
    return 0;
}
