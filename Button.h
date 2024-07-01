#ifndef BUTTON_H 
#define BUTTON_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class Button {
public:
    Button(int posx, int posy, std::string text, TTF_Font* font, SDL_Renderer* renderer);
    ~Button();
    void render();

private:
    int posx;
    int posy;
    int width;
    int height;
    SDL_Renderer* renderer;
    TTF_Font* font;
    std::string text;
    SDL_Texture* tex;
    SDL_Color textColor{255, 255, 255};
    SDL_Rect rect;
};

#endif // BUTTON_H
