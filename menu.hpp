// menu.hpp
#ifndef MENU_HPP
#define MENU_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "utils.hpp"
#include <SDL2/SDL_ttf.h>

class Menu {
    public:
        Menu(SDL_Renderer*& renderer, SDL_Texture* background_texture);
        ~Menu();
        void menuAction(SDL_Event& event, bool& quit, SDL_Renderer*& renderer);

    private:
        SDL_Texture* sort_button;
        SDL_Cursor* cursor;
        SDL_Rect sort_rect;
        bool sort_hovered = false;
};


#endif // MENU_HPP
