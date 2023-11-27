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
        void renderSinglyLinkedList(SDL_Renderer*& renderer);
        void renderElement(SDL_Renderer*& renderer, std::string text, SDL_Rect render_rect, bool is_bordered);
        void renderArrow(SDL_Renderer*& renderer, SDL_Rect from_rect, SDL_Rect to_rect, std::string direction, bool is_start_bordered, bool is_end_bordered);
        void renderDestroyArrow(SDL_Renderer*& renderer, SDL_Rect from_rect, SDL_Rect to_rect, std::string direction, bool is_start_bordered, bool is_end_bordered);
        void singlyLinkedAddFirst(SDL_Renderer*& renderer);
        void increaseAndDrawNewValue(SDL_Renderer*& renderer);
        void decreaseAndDrawNewValue(SDL_Renderer*& renderer);
        void threadManager(SDL_Renderer*& renderer);

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
        SDL_Rect head_rect;
        SDL_Rect null_rect;
        bool is_processing = false;
        std::thread processing_thread;
        bool exit_thread_manager = false;
        std::thread thread_manager;

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

        // Up button variable
        SDL_Texture* up_button;
        SDL_Texture* up_disable;
        SDL_Rect up_rect;
        bool up_hovered;

        // Down button variable
        SDL_Texture* down_button;
        SDL_Texture* down_disable;
        SDL_Rect down_rect;
        bool down_hovered;
};

#endif // LINKED_LIST_HPP