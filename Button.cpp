#include "Button.h"
#include "SDLContext.h"
#include <iostream>


Button::Button(SDLContext* context, int posx, int posy, std::string text)
  : context(context), posx(posx), posy(posy), text(text), tex(nullptr) {

  SDL_Surface* textSurface = TTF_RenderText_Solid(context->getFont(), text.c_str(), textColor);
    if (textSurface == nullptr) {
        std::cerr << "TTF_RenderText_Solid Error: " << TTF_GetError() << std::endl;
        return;
    }

    tex = SDL_CreateTextureFromSurface(context->getRenderer(), textSurface);
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

bool Button::isClicked(int x, int y) {
  SDL_Point mousePoint = {x, y};

  if(SDL_PointInRect(&mousePoint, &outlineRect)){
    return true;
  }

  return false;
} 

void Button::render() {
    // Draw the outline rectangle
    SDL_SetRenderDrawColor(context->getRenderer(), outlineColor.r, outlineColor.g, outlineColor.b, 255);
    SDL_RenderDrawRect(context->getRenderer(), &outlineRect);

    // Render the text
    SDL_RenderCopy(context->getRenderer(), tex, nullptr, &rect);
}


