#include "utils.hpp"

const int WIDTH = 100;
const int HEIGHT = 60;

SDL_Texture* Utils::loadTexture(const char* file_path, SDL_Renderer*& renderer)
{
    SDL_Surface* loaded_surface = IMG_Load(file_path);
    if (!loaded_surface) {
        std::cerr << "Failed to load image: " << IMG_GetError() << std::endl;
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);
    SDL_FreeSurface(loaded_surface);
    return texture;
}

bool Utils::isMouseOverButton(SDL_Rect buttonRect)
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    return x >= buttonRect.x && x <= buttonRect.x + buttonRect.w && y >= buttonRect.y && y <= buttonRect.y + buttonRect.h;
}