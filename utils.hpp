// utils.hpp
#ifndef UTILS_HPP
#define UTILS_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

class Utils {
public:
    static SDL_Texture* loadTexture(const char* file_path, SDL_Renderer*& renderer);
    static bool isMouseOverButton(SDL_Rect buttonRect);
};

extern const int WIDTH;
extern const int HEIGHT;

#endif // UTILS_HPP
