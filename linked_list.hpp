// linked_list.hpp
#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>
#include <SDL2/SDL_ttf.h>
#include <random>
#include <algorithm>
#include <thread>
#include <vector>
#include <string.h>

class LinkedList {
    public:
        struct SinglyNode {
            int value;
            SinglyNode* next;
            SinglyNode(int data) : value(data), next(nullptr) {}
        };
        LinkedList(SDL_Renderer*& renderer, SDL_Texture* background_texture);
        ~LinkedList();
        void renderLayout(SDL_Renderer*& renderer);
        void linkedListAction(SDL_Event& event, bool& quit, SDL_Renderer*& renderer);
        void destroy();
        void generateAndDrawNewValue(SDL_Renderer*& renderer);
    

    private:
        int new_value;
        TTF_Font *font;
        SDL_Cursor* cursor;
        SDL_Rect square_rect;
        SDL_Rect number_rect;
        SinglyNode* singly_head;
        std::vector<int> number_arrays;
        SDL_Surface *text_surface;
        SDL_Surface *value_surface;

        SDL_Texture *new_value_text;
        SDL_Texture *new_value_value;

        // SDL_Texture* new_value;
        SDL_Rect new_value_rect;

        // Change number button variable
        SDL_Texture* change_number_button;
        SDL_Texture* change_number_disable;
        SDL_Rect change_number_rect;
        bool change_number_hovered = false; 

        // Back button variable
        SDL_Texture* back_button;
        SDL_Texture* back_disable;
        SDL_Rect back_rect;
        bool back_hovered = false; 

        // Cancel button variable
        SDL_Texture* cancel_button;
        SDL_Texture* cancel_disable;
        SDL_Rect cancel_rect;
        bool cancel_hovered = false;

        // Singly button variable
        SDL_Texture* singly_linked_active;
        SDL_Rect singly_linked_rect;

        // Doubly button variable
        SDL_Texture* doubly_linked_disable;
        SDL_Rect doubly_linked_rect;

        // Circular button variable
        SDL_Texture* circular_linked_disable;
        SDL_Rect circular_linked_rect;

        // Circular doubly button variable
        SDL_Texture* circular_doubly_linked_disable;
        SDL_Rect circular_doubly_linked_rect;

        // Init button variable
        // SDL_Texture* init_button;
        // SDL_Texture* init_disable;
        // SDL_Rect init_rect;
        // bool init_hovered;

        // Add first button variable
        SDL_Texture* add_first_button;
        SDL_Texture* add_first_disable;
        SDL_Rect add_first_rect;
        bool add_first_hovered;
};

#endif // LINKED_LIST_HPP