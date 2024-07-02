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

    // Set outlineRect slightly larger than text rect
    outlineRect = { posx - 10, posy - 10, width + 20, height + 20 };

    SDL_FreeSurface(textSurface);
}

Button::~Button() {
    if (tex != nullptr) {
        SDL_DestroyTexture(tex);
    }
}

void Button::render() {
    // Draw the outline rectangle
    SDL_SetRenderDrawColor(renderer, outlineColor.r, outlineColor.g, outlineColor.b, 255);
    SDL_RenderDrawRect(renderer, &outlineRect);

    // Render the text
    SDL_RenderCopy(renderer, tex, nullptr, &rect);
}
