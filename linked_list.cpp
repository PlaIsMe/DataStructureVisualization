#include "linked_list.hpp"
#include "utils.hpp"
#include "page.hpp"

const int delay_time = 1000;

LinkedList::LinkedList(SDL_Renderer *&renderer, SDL_Texture *background_texture)
{
    thread_manager = std::thread(&LinkedList::threadManager, this, std::ref(renderer));

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
    number_rect = {new_value_rect.x + new_value_rect.w + 5, new_value_rect.y, 15, 30};

    // Up button set up
    up_button = Utils::loadTexture("images/up_button.png", renderer);
    up_disable = Utils::loadTexture("images/up_disable.png", renderer);
    up_rect = {number_rect.x + number_rect.w + 5, number_rect.y, 30, 15};

    // Down button set up
    down_button = Utils::loadTexture("images/down_button.png", renderer);
    down_disable = Utils::loadTexture("images/down_disable.png", renderer);
    down_rect = {number_rect.x + number_rect.w + 5, number_rect.y + 15, 30, 15};

    // Change number button set up
    change_number_button = Utils::loadTexture("images/change_number_button.png", renderer);
    change_number_disable = Utils::loadTexture("images/change_number_disable.png", renderer);
    change_number_rect = {up_rect.x + up_rect.w + 5, number_rect.y, 30, 30}; 

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, background_texture, NULL, NULL);
    renderLayout(renderer);
    SDL_RenderPresent(renderer);
    generateAndDrawNewValue(renderer);
    renderSinglyLinkedList(renderer);
}

void LinkedList::threadManager(SDL_Renderer *&renderer)
{
    while (!exit_thread_manager)
    {
        if (!is_processing && processing_thread.joinable())
        {
            processing_thread.join();
        }
    }
}

LinkedList::~LinkedList()
{
    do
    {
        exit_thread_manager = true;
    } while (!thread_manager.joinable());
    thread_manager.join();
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
    SDL_RenderCopy(renderer, up_button, NULL, &up_rect);
    SDL_RenderCopy(renderer, down_button, NULL, &down_rect);
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
            up_hovered = Utils::isMouseOverButton(up_rect);
            down_hovered = Utils::isMouseOverButton(down_rect);

            if (back_hovered || add_first_hovered || change_number_hovered
            || up_hovered || down_hovered) {
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
            } else if (add_first_hovered) {
                processing_thread = std::thread(&LinkedList::singlyLinkedAddFirst, this, std::ref(renderer));
            } else if (up_hovered) {
                increaseAndDrawNewValue(renderer);
            } else if (down_hovered) {
                decreaseAndDrawNewValue(renderer);
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
    SDL_DestroyTexture(up_button);
    SDL_DestroyTexture(up_disable);
    SDL_DestroyTexture(down_button);
    SDL_DestroyTexture(down_disable);
    SDL_FreeCursor(cursor);
}

void LinkedList::generateAndDrawNewValue(SDL_Renderer*& renderer)
{
    std::uniform_int_distribution<int> random_range(0, 9);
    std::random_device random_number;
    new_value = random_range(random_number);
    std::string numberString = std::to_string(new_value);
    value_surface = TTF_RenderText_Solid(font, numberString.c_str(), {0, 153, 231, 255});
    new_value_value = SDL_CreateTextureFromSurface(renderer, value_surface);
    SDL_SetRenderDrawColor(renderer, 239, 241, 250, 255);
    SDL_RenderFillRect(renderer, &number_rect);
    SDL_RenderCopy(renderer, new_value_value, NULL, &number_rect);
    SDL_RenderPresent(renderer);
    SDL_FreeSurface(value_surface);
}

void LinkedList::increaseAndDrawNewValue(SDL_Renderer*& renderer)
{
    if (new_value == 9) {
        new_value = 0;
    } else {
        new_value = new_value + 1;
    }
    std::string numberString = std::to_string(new_value);
    value_surface = TTF_RenderText_Solid(font, numberString.c_str(), {0, 153, 231, 255});
    new_value_value = SDL_CreateTextureFromSurface(renderer, value_surface);
    SDL_SetRenderDrawColor(renderer, 239, 241, 250, 255);
    SDL_RenderFillRect(renderer, &number_rect);
    SDL_RenderCopy(renderer, new_value_value, NULL, &number_rect);
    SDL_RenderPresent(renderer);
    SDL_FreeSurface(value_surface);
}

void LinkedList::decreaseAndDrawNewValue(SDL_Renderer*& renderer)
{
    if (new_value == 0) {
        new_value = 9;
    } else {
        new_value = new_value - 1;
    }
    std::string numberString = std::to_string(new_value);
    value_surface = TTF_RenderText_Solid(font, numberString.c_str(), {0, 153, 231, 255});
    new_value_value = SDL_CreateTextureFromSurface(renderer, value_surface);
    SDL_SetRenderDrawColor(renderer, 239, 241, 250, 255);
    SDL_RenderFillRect(renderer, &number_rect);
    SDL_RenderCopy(renderer, new_value_value, NULL, &number_rect);
    SDL_RenderPresent(renderer);
    SDL_FreeSurface(value_surface);
}

void LinkedList::renderArrow(SDL_Renderer*& renderer, SDL_Rect from_rect,
 SDL_Rect to_rect, std::string direction, bool is_start_bordered, bool is_end_bordered)
{
    SDL_RenderSetScale(renderer, 5, 5);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    int start_padding_size;
    if (is_start_bordered) {
        start_padding_size = 15;
    } else {
        start_padding_size = 10;
    }
    int end_padding_size;
    if (is_end_bordered) {
        end_padding_size = 15;
    } else {
        end_padding_size = 10;
    }
    if (direction == "right") {
        SDL_RenderDrawLine(renderer, (from_rect.x + from_rect.w + start_padding_size) / 5, (from_rect.y + (from_rect.h / 2))/5, (to_rect.x - end_padding_size) / 5, (to_rect.y + (to_rect.h / 2)) /5);
        SDL_RenderDrawLine(renderer, (to_rect.x - end_padding_size - 5) / 5, (to_rect.y + (to_rect.h / 2) - 5)/5, (to_rect.x - end_padding_size - 10) / 5, (to_rect.y + (to_rect.h / 2) - 10)/5);
        SDL_RenderDrawLine(renderer, (to_rect.x - end_padding_size - 5) / 5, (to_rect.y + (to_rect.h / 2) + 5)/5, (to_rect.x - end_padding_size - 10) / 5, (to_rect.y + (to_rect.h / 2) + 10)/5);
    } else if (direction == "top") {
        SDL_RenderDrawLine(renderer, (from_rect.x + from_rect.w/2) / 5, (from_rect.y - start_padding_size)/5, (to_rect.x + to_rect.w/2) / 5, (to_rect.y + to_rect.h + end_padding_size)/5);
        SDL_RenderDrawLine(renderer, (to_rect.x + to_rect.w/2 - 5)/5, (to_rect.y + to_rect.h + 20)/5, (to_rect.x + to_rect.w/2 - 10)/5, (to_rect.y + to_rect.h + 25)/5);
        SDL_RenderDrawLine(renderer, (to_rect.x + to_rect.w/2 + 5)/5, (to_rect.y + to_rect.h + 20)/5, (to_rect.x + to_rect.w/2 + 10)/5, (to_rect.y + to_rect.h + 25)/5);
    } else if (direction == "bottom") {
        SDL_RenderDrawLine(renderer,  (from_rect.x + from_rect.w/2) / 5, (from_rect.y + from_rect.h + start_padding_size)/5, (to_rect.x + to_rect.w/2) / 5, (to_rect.y - start_padding_size - 5)/5);
        SDL_RenderDrawLine(renderer, (to_rect.x + to_rect.w/2 - 5)/5, (to_rect.y - end_padding_size - 10)/5, (to_rect.x + to_rect.w/2 - 10)/5, (to_rect.y - end_padding_size - 15)/5);
        SDL_RenderDrawLine(renderer, (to_rect.x + to_rect.w/2 + 5)/5, (to_rect.y - end_padding_size - 10)/5, (to_rect.x + to_rect.w/2 + 10)/5, (to_rect.y - end_padding_size - 15)/5);
    }
    
    SDL_RenderSetScale(renderer, 1, 1);
    SDL_RenderPresent(renderer);
}

void LinkedList::renderDestroyArrow(SDL_Renderer*& renderer, SDL_Rect from_rect, SDL_Rect to_rect,
 std::string direction, bool is_start_bordered, bool is_end_bordered)
{
    SDL_RenderSetScale(renderer, 5, 5);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    int start_padding_size;
    if (is_start_bordered) {
        start_padding_size = 15;
    } else {
        start_padding_size = 10;
    }
    int end_padding_size;
    if (is_end_bordered) {
        end_padding_size = 15;
    } else {
        end_padding_size = 10;
    }
    if (direction == "right") {
        int from_x = (from_rect.x + from_rect.w + start_padding_size)/5;
        int from_y = (from_rect.y + (from_rect.h / 2))/5;
        int to_x = (to_rect.x - end_padding_size)/5;
        int to_y = (to_rect.y + (to_rect.h / 2)) /5;
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderDrawLine(renderer, from_x + (to_x - from_x)/2 - 2, from_y - 2, from_x + (to_x - from_x)/2 + 2, from_y + 2);
        SDL_RenderDrawLine(renderer, from_x + (to_x - from_x)/2 - 2, from_y + 2, from_x + (to_x - from_x)/2 + 2, from_y - 2);
    } else if (direction == "top") {
        int from_x = (from_rect.x + from_rect.w/2) / 5;
        int from_y = (from_rect.y - start_padding_size)/5;
        int to_x = (to_rect.x + to_rect.w/2) / 5;
        int to_y = (to_rect.y + to_rect.h + end_padding_size)/5;
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderDrawLine(renderer, from_x - 2, to_y - (to_y - from_y)/2 - 1, from_x + 2, to_y - (to_y - from_y)/2 + 3);
        SDL_RenderDrawLine(renderer, from_x + 2, to_y - (to_y - from_y)/2 - 1, from_x - 2, to_y - (to_y - from_y)/2 + 3);
    }
    
    SDL_RenderSetScale(renderer, 1, 1);
    SDL_RenderPresent(renderer);
}

void LinkedList::renderElement(SDL_Renderer*& renderer, std::string text, SDL_Rect render_rect, bool is_bordered)
{
    // draw border
    if (is_bordered)
    {
        SDL_Rect outer_rect = {render_rect.x - 10, render_rect.y - 10, render_rect.w + 20, render_rect.h + 20};
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &outer_rect);
        SDL_Rect inner_rect = {render_rect.x - 5, render_rect.y - 5, render_rect.w + 10, render_rect.h + 10};
        SDL_SetRenderDrawColor(renderer, 0, 153, 231, 255);
        SDL_RenderFillRect(renderer, &inner_rect);
    }

    SDL_Surface *render_surface;
    SDL_Texture *render_texture;
    render_surface = TTF_RenderText_Solid(font, text.c_str(), {255, 255, 255, 255});
    render_texture = SDL_CreateTextureFromSurface(renderer, render_surface);
    SDL_RenderCopy(renderer, render_texture, NULL, &render_rect);

    SDL_RenderPresent(renderer);
    SDL_FreeSurface(render_surface);
}

void LinkedList::renderSinglyLinkedList(SDL_Renderer*& renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 153, 231, 255);
    SDL_RenderFillRect(renderer, &square_rect);
    if (singly_head == NULL) {
        head_rect = {50, (square_rect.y + square_rect.h / 2), 80, 30};
        renderElement(renderer, "HEAD", head_rect, false);
        null_rect = {head_rect.x + head_rect.w + 65, head_rect.y, 80, 30};
        renderArrow(renderer, head_rect, null_rect, "right", false, false);
        renderElement(renderer, "NULL", null_rect, false);
    } else {
        int position = 85;
        SinglyNode* output_node = singly_head;
        SDL_Rect element_rect;
        while (output_node != NULL)
        {
            SDL_Rect old_element_rect = element_rect;
            std::string numberString = std::to_string(output_node->value);
            element_rect = {position, (square_rect.y + square_rect.h / 2), 15, 30};
            renderElement(renderer, numberString, element_rect, true);
            if (output_node == singly_head)
            {
                head_rect = {50, (square_rect.y + square_rect.h / 2) + 100, 80, 30};
                renderElement(renderer, "HEAD", head_rect, false);
                renderArrow(renderer, head_rect, element_rect, "top", false, true);
            } else {
                renderArrow(renderer, old_element_rect, element_rect, "right", true, true);
            }
            position += 75;
            output_node = output_node->next;
        }
        null_rect = {position, (square_rect.y + square_rect.h / 2), 80, 30};
        renderArrow(renderer, element_rect, null_rect, "right", true, false);
        renderElement(renderer, "NULL", null_rect, false);
    }
}

void LinkedList::singlyLinkedAddFirst(SDL_Renderer*& renderer)
{
    is_processing = true;
    // logic
    SinglyNode* new_element = new SinglyNode(new_value);

    // view
    SDL_Rect first_element_rect = {85, (square_rect.y + square_rect.h / 2), 15, 30};
    SDL_Rect new_element_rect = {head_rect.x + 35, first_element_rect.y - 100, 15, 30};
    std::string numberString = std::to_string(new_value);
    renderElement(renderer, numberString, new_element_rect, true);
    SDL_Rect next_rect = {new_element_rect.x + new_element_rect.w + 75, new_element_rect.y, 80, 30};
    renderElement(renderer, "NULL", next_rect, false);
    renderArrow(renderer, new_element_rect, next_rect, "right", true, false);
    std::this_thread::sleep_for(std::chrono::milliseconds(delay_time));

    if (singly_head == NULL) {
        // view
        renderDestroyArrow(renderer, head_rect, null_rect, "right", false, false);
        std::this_thread::sleep_for(std::chrono::milliseconds(delay_time));
        SDL_Rect clear_rect = {head_rect.x + head_rect.w, head_rect.y, 200, 30};
        SDL_SetRenderDrawColor(renderer, 0, 153, 231, 255);
        SDL_RenderFillRect(renderer, &clear_rect);
        SDL_RenderPresent(renderer);
        std::this_thread::sleep_for(std::chrono::milliseconds(delay_time));
        renderArrow(renderer, head_rect, new_element_rect, "top", false, true);
        std::this_thread::sleep_for(std::chrono::milliseconds(delay_time));
    } else {        
        renderDestroyArrow(renderer, head_rect, first_element_rect, "top", false, true);
        std::this_thread::sleep_for(std::chrono::milliseconds(delay_time));
        renderArrow(renderer, new_element_rect, first_element_rect, "bottom", true, true);
        SDL_Rect clear_rect = {new_element_rect.x + new_element_rect.w + 15, new_element_rect.y - 15, 200, new_element_rect.y - 15 };
        SDL_SetRenderDrawColor(renderer, 0, 153, 231, 255);
        SDL_RenderFillRect(renderer, &clear_rect);
        SDL_RenderPresent(renderer);
        std::this_thread::sleep_for(std::chrono::milliseconds(delay_time));
    }
    // logic
    new_element->next = singly_head;
    singly_head = new_element;
    renderSinglyLinkedList(renderer);
    generateAndDrawNewValue(renderer);

    is_processing = false;
}