#include "Button.h"
#include <iostream>

Button::Button(int posx, int posy, std::string text, TTF_Font* font, SDL_Renderer* renderer)
    : posx(posx), posy(posy), text(text), renderer(renderer), font(font), tex(nullptr) {

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
    if (textSurface == nullptr) {
        std::cerr << "TTF_RenderText_Solid Error: " << TTF_GetError() << std::endl;
        return;
    }

    tex = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (tex == nullptr) {
        std::cerr << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(textSurface);
        return;
    }

    width = textSurface->w;
    height = textSurface->h;
    rect = { posx, posy, width, height };

    SDL_FreeSurface(textSurface);
}

Button::~Button() {
    if (tex != nullptr) {
        SDL_DestroyTexture(tex);
    }
}

void Button::render() {
    SDL_RenderCopy(renderer, tex, nullptr, &rect);
}
