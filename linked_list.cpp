#include "linked_list.hpp"
#include "utils.hpp"
#include "page.hpp"

LinkedList::LinkedList(SDL_Renderer *&renderer, SDL_Texture *background_texture)
{
    for (int i = 0; i < 10; i++)
    {
        number_arrays.push_back(i);
    }
    cursor = nullptr;
    singly_head = NULL;
    int menu_button_width = 150;
    int menu_button_height = 50;
    int action_button_size = 80;
    new_value = -1;

    // Back button set up
    back_button = Utils::loadTexture("images/back_button.png", renderer);
    back_disable = Utils::loadTexture("images/back_disable.png", renderer);
    back_rect = {(WIDTH * 10) / 2 - menu_button_width * 2 - 40, (HEIGHT * 10) - 185, 50, 50};

    // Singly button set up
    singly_linked_active = Utils::loadTexture("images/singly_linked_active.png", renderer);
    singly_linked_rect = {back_rect.x + back_rect.w + 5, back_rect.y, menu_button_width, menu_button_height};

    // Doubly button set up
    doubly_linked_disable = Utils::loadTexture("images/doubly_linked_disable.png", renderer);
    doubly_linked_rect = {singly_linked_rect.x + singly_linked_rect.w + 5, back_rect.y, menu_button_width, menu_button_height};

    // Circurlar button set up
    circular_linked_disable = Utils::loadTexture("images/circular_linked_disable.png", renderer);
    circular_linked_rect = {doubly_linked_rect.x + doubly_linked_rect.w + 5, back_rect.y, menu_button_width, menu_button_height};

    // Circurlar button set up
    circular_doubly_linked_disable = Utils::loadTexture("images/circular_doubly_linked_disable.png", renderer);
    circular_doubly_linked_rect = {circular_linked_rect.x + circular_linked_rect.w + 5, back_rect.y, menu_button_width, menu_button_height};

    // Cancel button set up
    cancel_button = Utils::loadTexture("images/cancel_button.png", renderer);
    cancel_disable = Utils::loadTexture("images/cancel_disable.png", renderer);
    cancel_rect = {circular_doubly_linked_rect.x + circular_doubly_linked_rect.w + 5, back_rect.y, 50, 50};

    // Add fisrt button set up
    add_first_button = Utils::loadTexture("images/add_first_button.png", renderer);
    add_first_disable = Utils::loadTexture("images/add_first_disable.png", renderer);
    add_first_rect = {10, HEIGHT * 10 - 10 - action_button_size, action_button_size, action_button_size};

    // New value label set up
    font = TTF_OpenFont("fonts/arial.ttf", 25);
    text_surface = TTF_RenderText_Solid(font, "New value: ", {0, 153, 231, 255});
    new_value_text = SDL_CreateTextureFromSurface(renderer, text_surface);
    new_value_rect = {doubly_linked_rect.x + doubly_linked_rect.w - menu_button_width, doubly_linked_rect.y + doubly_linked_rect.h + 5, menu_button_width - 20, menu_button_height - 20};
    square_rect = {10, 10, (WIDTH * 10) - 20, (HEIGHT * 10) - 200};
    number_rect = {new_value_rect.x + new_value_rect.w + 5, new_value_rect.y, 30, 30};

    // Change number button set up
    change_number_button = Utils::loadTexture("images/change_number_button.png", renderer);
    change_number_disable = Utils::loadTexture("images/change_number_disable.png", renderer);
    change_number_rect = {number_rect.x + number_rect.w + 5, number_rect.y, 30, 30}; 

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, background_texture, NULL, NULL);
    renderLayout(renderer);
    SDL_RenderPresent(renderer);
    generateAndDrawNewValue(renderer);
}

LinkedList::~LinkedList()
{

}

void LinkedList::renderLayout(SDL_Renderer*& renderer)
{
    SDL_RenderCopy(renderer, back_button, NULL, &back_rect);
    SDL_RenderCopy(renderer, cancel_disable, NULL, &cancel_rect);
    SDL_RenderCopy(renderer, singly_linked_active, NULL, &singly_linked_rect);
    SDL_RenderCopy(renderer, doubly_linked_disable, NULL, &doubly_linked_rect);
    SDL_RenderCopy(renderer, circular_linked_disable, NULL, &circular_linked_rect);
    SDL_RenderCopy(renderer, circular_doubly_linked_disable, NULL, &circular_doubly_linked_rect);
    SDL_RenderCopy(renderer, new_value_text, NULL, &new_value_rect);
    SDL_RenderCopy(renderer, change_number_button, NULL, &change_number_rect);
    SDL_RenderCopy(renderer, add_first_button, NULL, &add_first_rect);
    SDL_SetRenderDrawColor(renderer, 239, 241, 250, 255);
    SDL_RenderFillRect(renderer, &number_rect);
    SDL_SetRenderDrawColor(renderer, 0, 153, 231, 255);
    SDL_RenderFillRect(renderer, &square_rect);
    SDL_FreeSurface(text_surface);
}

void LinkedList::linkedListAction(SDL_Event& event, bool& quit, SDL_Renderer*& renderer)
{
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            quit = true;
        } else if (event.type == SDL_MOUSEMOTION) {
            back_hovered = Utils::isMouseOverButton(back_rect);
            change_number_hovered = Utils::isMouseOverButton(change_number_rect);
            add_first_hovered = Utils::isMouseOverButton(add_first_rect);

            if (back_hovered || add_first_hovered || change_number_hovered) {
                cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
                SDL_SetCursor(cursor);
            } else {
                SDL_FreeCursor(cursor);
            }
        } else if (event.type == SDL_MOUSEBUTTONDOWN) {
            if (back_hovered) {
                destroy();
                current_page = menu_page;
            } else if (change_number_hovered) {
                generateAndDrawNewValue(renderer);
            }
        }
    }
}

void LinkedList::destroy()
{
    SDL_DestroyTexture(back_button);
    SDL_DestroyTexture(back_disable);
    SDL_DestroyTexture(cancel_button);
    SDL_DestroyTexture(cancel_disable);
    SDL_DestroyTexture(singly_linked_active);
    SDL_DestroyTexture(doubly_linked_disable);
    SDL_DestroyTexture(circular_doubly_linked_disable);
    SDL_DestroyTexture(circular_linked_disable);
    SDL_DestroyTexture(new_value_text);
    SDL_DestroyTexture(new_value_value);
    SDL_DestroyTexture(change_number_button);
    SDL_DestroyTexture(change_number_disable);
    SDL_DestroyTexture(add_first_button);
    SDL_DestroyTexture(add_first_disable);
    SDL_FreeCursor(cursor);
}

void LinkedList::generateAndDrawNewValue(SDL_Renderer*& renderer)
{
    std::uniform_int_distribution<int> random_range(1, 100);
    std::random_device random_number;
    new_value = random_range(random_number);
    std::string numberString;
    if (new_value < 10)
    {
        numberString = "0" + std::to_string(new_value + 1);
    }
    else
    {
        numberString = std::to_string(new_value + 1);
    }
    value_surface = TTF_RenderText_Solid(font, numberString.c_str(), {0, 153, 231, 255});
    new_value_value = SDL_CreateTextureFromSurface(renderer, value_surface);
    SDL_SetRenderDrawColor(renderer, 239, 241, 250, 255);
    SDL_RenderFillRect(renderer, &number_rect);
    SDL_RenderCopy(renderer, new_value_value, NULL, &number_rect);
    SDL_RenderPresent(renderer);
    SDL_FreeSurface(value_surface);
}