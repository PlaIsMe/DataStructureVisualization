// sort.hpp
#ifndef SORT_HPP
#define SORT_HPP

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>
#include <SDL2/SDL_ttf.h>
#include <random>
#include <algorithm>
#include <thread>
#include <chrono>

using std::random_device;
using std::uniform_int_distribution;
using std::vector;
using std::swap;
using std::is_sorted;

class Sort {
    public:
        Sort(SDL_Renderer*& renderer, SDL_Texture* background_texture);
        ~Sort();
        void firstDraw(vector<int> vector, SDL_Renderer*& renderer);
        void sortAction(SDL_Event& event, bool& quit, SDL_Renderer*& renderer);
        void renderLayout(SDL_Renderer*& renderer);
        void generateArray();
        void destroy();        
        void blockButton(SDL_Renderer*& renderer);
        void unBlockButton(SDL_Renderer*& renderer);
        void threadManager(SDL_Renderer*& renderer);
        void selectionSort(SDL_Renderer*& renderer, vector<int>& sort_vector, bool& is_sorting);
        void drawSelectionSort(vector<int> vector, SDL_Renderer* renderer, unsigned int green, unsigned int red, unsigned int blue);
        void insertionSort(SDL_Renderer*& renderer);
        void drawInsertionSort(vector<int> vector, SDL_Renderer* renderer, unsigned int green, unsigned int red);
        void bubbleSort(SDL_Renderer*& renderer);
        void drawBubbleSort(vector<int> vector, SDL_Renderer* renderer, unsigned int red);
        void interchangeSort(SDL_Renderer*& renderer);
        void drawInterchangeSort(vector<int> vector, SDL_Renderer* renderer, unsigned int red, unsigned int blue);
        void countingSort(SDL_Renderer*& renderer);
        void renderTotal(vector<int> vector, SDL_Renderer* renderer, SDL_Rect square_rect,
                            bool is_sorting, TTF_Font *font, SDL_Rect element_rect, SDL_Rect total_rect);
        void quickSort(SDL_Renderer*& renderer, vector<int>& vector, int left, int right);
        void drawQuickSort(vector<int> vector, SDL_Renderer*& renderer, unsigned int green, unsigned int red_left, unsigned int red_right);
        void heapify(SDL_Renderer *&renderer, vector<int> &sort_vector, int n, int i);
        void heapSort(SDL_Renderer*& renderer);
        void drawHeapSort(vector<int> vector, SDL_Renderer*& renderer, int green, int red_left, int red_right);

    private:
        SDL_Cursor* cursor;
        vector<int> main_vector;
        SDL_Rect square_rect;
        random_device random_number;
        bool is_sorting = false;
        std::thread sort_thread;
        bool exit_thread_manager = false;
        std::thread thread_manager;

        // Change array button variable
        SDL_Texture* change_button;
        SDL_Texture* change_disable;
        SDL_Rect change_rect;
        bool change_hovered = false;

        
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

        // Selection sort button variable
        SDL_Texture* selection_sort_button;
        SDL_Texture* selection_sort_disable;
        SDL_Rect selection_sort_rect;
        bool selection_sort_hovered = false;

        // Insertion sort button variable
        SDL_Texture* insertion_sort_button;
        SDL_Texture* insertion_sort_disable;
        SDL_Rect insertion_sort_rect;
        bool insertion_sort_hovered = false;

        // Bubble sort button variable
        SDL_Texture* bubble_sort_button;
        SDL_Texture* bubble_sort_disable;
        SDL_Rect bubble_sort_rect;
        bool bubble_sort_hovered = false;

        // Interchange sort button variable
        SDL_Texture* interchange_sort_button;
        SDL_Texture* interchange_sort_disable;
        SDL_Rect interchange_sort_rect;
        bool interchange_sort_hovered = false;

        // Couting sort button variable
        SDL_Texture* counting_sort_button;
        SDL_Texture* counting_sort_disable;
        SDL_Rect counting_sort_rect;
        bool counting_sort_hovered = false;

        // Quick sort button variable
        SDL_Texture* quick_sort_button;
        SDL_Texture* quick_sort_disable;
        SDL_Rect quick_sort_rect;
        bool quick_sort_hovered = false;

        // Heap sort button variable
        SDL_Texture* heap_sort_button;
        SDL_Texture* heap_sort_disable;
        SDL_Rect heap_sort_rect;
        bool heap_sort_hovered = false;

        // Merge sort button variable
        SDL_Texture* merge_sort_button;
        SDL_Texture* merge_sort_disable;
        SDL_Rect merge_sort_rect;
        bool merge_sort_hovered = false;
};


#endif // SORT_HPP
