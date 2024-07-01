#include "GameUI.h"

GameUI::GameUI(SDL_Renderer* renderer, TTF_Font* font):
  renderer(renderer), font(font) {}

GameUI::addButton(std::string text) {
  Button* button = new Button(0, 0, text);
  buttons.push_back(button);
}
