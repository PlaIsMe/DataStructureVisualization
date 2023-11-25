#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "utils.hpp"
#include "menu.hpp"
#include "page.hpp"
#include "sort.hpp"
#include "linked_list.hpp"

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
SDL_Texture* background_texture = nullptr;
Menu* menu = nullptr;
Sort* sort = nullptr;
LinkedList* linked_list = nullptr;

bool initializeSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        return false;
    }

    window = SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH * 10, HEIGHT * 10, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer creation failed: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cerr << "SDL_image initialization failed: " << IMG_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }

    if (TTF_Init() != 0) {
        std::cerr << "SDL_ttf initialization failed: " << TTF_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }

    return true;
}

bool loadBackground() {
    background_texture = Utils::loadTexture("images/background.png", renderer);
    if (!background_texture) {
        return false;
    }

    return true;
}

void closeSDL() {
    SDL_DestroyTexture(background_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* argv[]) {
    if (!initializeSDL()) {
        return -1;
    }

    if (!loadBackground()) {
        closeSDL();
        return -1;
    }

    bool quit = false;
    SDL_Event event;
    current_page = menu_page;

    while (!quit) {
        if (current_page == menu_page)
        {
            if (menu == nullptr)
            {
                menu = new Menu(renderer, background_texture);
            }
            if (sort != nullptr)
            {
                delete sort;
                sort = nullptr;
            }
            if (linked_list != nullptr)
            {
                delete linked_list;
                linked_list = nullptr;
            }
            menu->menuAction(event, quit, renderer);
        }
        else if (current_page == sort_page)
        {
            if (sort == nullptr)
            {
                sort = new Sort(renderer, background_texture);
            }
            if (menu != nullptr)
            {
                delete menu;
                menu = nullptr;
            }
            if (linked_list != nullptr)
            {
                delete linked_list;
                linked_list = nullptr;
            }
            sort->sortAction(event, quit, renderer);
        }
        else if (current_page = linked_list_page)
        {
            if (linked_list == nullptr)
            {
                linked_list = new LinkedList(renderer, background_texture);
            }
            if (sort != nullptr)
            {
                delete sort;
                sort = nullptr;
            }
            if (menu != nullptr)
            {
                delete menu;
                menu = nullptr;
            }
            linked_list->linkedListAction(event, quit, renderer);
        }

        // SDL_Delay(16);
    }

    closeSDL();

    return 0;
}
