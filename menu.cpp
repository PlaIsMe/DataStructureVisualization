#include "menu.hpp"
#include "page.hpp"
#include "utils.hpp"

Menu::Menu(SDL_Renderer*& renderer, SDL_Texture* background_texture)
{
    sort_button = Utils::loadTexture("images/sort_button.png", renderer);
    cursor = nullptr;
    sort_rect = {100, 350, 200, 50};
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, background_texture, NULL, NULL);
    SDL_RenderCopy(renderer, sort_button, NULL, &sort_rect);

    SDL_RenderPresent(renderer);
}

Menu::~Menu()
{
    // SDL_DestroyTexture(sort_button);
    // SDL_DestroyTexture(sort_hover);
}

void Menu::menuAction(SDL_Event& event, bool& quit, SDL_Renderer*& renderer)
{
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            quit = true;
        } else if (event.type == SDL_MOUSEMOTION) {
            sort_hovered = Utils::isMouseOverButton(sort_rect);
            if (sort_hovered) {
                cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
                SDL_SetCursor(cursor);
            } else {
                SDL_FreeCursor(cursor);
            }
        } else if (event.type == SDL_MOUSEBUTTONDOWN) {
            if (sort_hovered) {
                SDL_DestroyTexture(sort_button);
                SDL_FreeCursor(cursor);
                sort_hovered = false;
                current_page = sort_page;
            }
        }
    }
}
