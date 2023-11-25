#include "sort.hpp"
#include "utils.hpp"
#include "page.hpp"

const int delay_time = 1;

void Sort::generateArray()
{
    std::uniform_int_distribution<int> random_range(1, square_rect.h / 10 - 1);
    main_vector.clear();
    for (int i = 0; i < square_rect.w / 10; i++)
    {
        main_vector.push_back(random_range(random_number));
    }
}

Sort::Sort(SDL_Renderer *&renderer, SDL_Texture *background_texture)
{
    thread_manager = std::thread(&Sort::threadManager, this, std::ref(renderer));
    cursor = nullptr;
    // Back button set up
    back_button = Utils::loadTexture("images/back_button.png", renderer);
    back_disable = Utils::loadTexture("images/back_disable.png", renderer);
    back_rect = {10, (HEIGHT * 10) - 185, 30, 30};

    // Change button set up
    change_button = Utils::loadTexture("images/change_button.png", renderer);
    change_disable = Utils::loadTexture("images/change_disable.png", renderer);
    change_rect = {back_rect.x + back_rect.w, (HEIGHT * 10) - 190, 180, 40};

    // Cancel button set up
    cancel_button = Utils::loadTexture("images/cancel_button.png", renderer);
    cancel_disable = Utils::loadTexture("images/cancel_disable.png", renderer);
    cancel_rect = {change_rect.x + change_rect.w, (HEIGHT * 10) - 185, 30, 30};

    // Selection sort button set up
    selection_sort_button = Utils::loadTexture("images/selection_sort_button.png", renderer);
    selection_sort_disable = Utils::loadTexture("images/selection_sort_disable.png", renderer);
    selection_sort_rect = {10, (HEIGHT * 10) - 130, 200, 50};

    // Insertion sort button set up
    insertion_sort_button = Utils::loadTexture("images/insertion_sort_button.png", renderer);
    insertion_sort_disable = Utils::loadTexture("images/insertion_sort_disable.png", renderer);
    insertion_sort_rect = {selection_sort_rect.x + selection_sort_rect.w + 10, (HEIGHT * 10) - 130, 200, 50};

    // Bubble sort button set up
    bubble_sort_button = Utils::loadTexture("images/bubble_sort_button.png", renderer);
    bubble_sort_disable = Utils::loadTexture("images/bubble_sort_disable.png", renderer);
    bubble_sort_rect = {insertion_sort_rect.x + insertion_sort_rect.w + 10, (HEIGHT * 10) - 130, 200, 50};

    // Interchange sort button set up
    interchange_sort_button = Utils::loadTexture("images/interchange_sort_button.png", renderer);
    interchange_sort_disable = Utils::loadTexture("images/interchange_sort_disable.png", renderer);
    interchange_sort_rect = {bubble_sort_rect.x + bubble_sort_rect.w + 10, (HEIGHT * 10) - 130, 200, 50};

    // Counting sort button set up
    counting_sort_button = Utils::loadTexture("images/counting_sort_button.png", renderer);
    counting_sort_disable = Utils::loadTexture("images/counting_sort_disable.png", renderer);
    counting_sort_rect = {selection_sort_rect.x, selection_sort_rect.y + selection_sort_rect.h + 10, 200, 50};

    // Quick sort button set up
    quick_sort_button = Utils::loadTexture("images/quick_sort_button.png", renderer);
    quick_sort_disable = Utils::loadTexture("images/quick_sort_disable.png", renderer);
    quick_sort_rect = {counting_sort_rect.x + counting_sort_rect.w + 10, counting_sort_rect.y, 200, 50};

    // Heap sort button set up
    heap_sort_button = Utils::loadTexture("images/heap_sort_button.png", renderer);
    heap_sort_disable = Utils::loadTexture("images/heap_sort_disable.png", renderer);
    heap_sort_rect = {quick_sort_rect.x + quick_sort_rect.w + 10, counting_sort_rect.y, 200, 50};

    // Merge sort button set up
    merge_sort_button = Utils::loadTexture("images/merge_sort_button.png", renderer);
    merge_sort_disable = Utils::loadTexture("images/merge_sort_disable.png", renderer);
    merge_sort_rect = {heap_sort_rect.x + heap_sort_rect.w + 10, counting_sort_rect.y, 200, 50};

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, background_texture, NULL, NULL);
    renderLayout(renderer);
    SDL_RenderPresent(renderer);
}

Sort::~Sort()
{
    do
    {
        exit_thread_manager = true;
    } while (!thread_manager.joinable());
    thread_manager.join();
}

void Sort::firstDraw(std::vector<int> vector, SDL_Renderer *&renderer)
{
    SDL_RenderSetScale(renderer, 10, 10);
    int index = 0;
    for (int i : vector)
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawLine(renderer, index + 1, square_rect.h / 10 - i, index + 1, square_rect.h / 10);
        index += 1;
    }
    SDL_RenderSetScale(renderer, 1, 1);
}

void Sort::renderLayout(SDL_Renderer *&renderer)
{
    SDL_RenderCopy(renderer, change_button, NULL, &change_rect);
    SDL_RenderCopy(renderer, back_button, NULL, &back_rect);
    SDL_RenderCopy(renderer, selection_sort_button, NULL, &selection_sort_rect);
    SDL_RenderCopy(renderer, cancel_disable, NULL, &cancel_rect);
    SDL_RenderCopy(renderer, insertion_sort_button, NULL, &insertion_sort_rect);
    SDL_RenderCopy(renderer, bubble_sort_button, NULL, &bubble_sort_rect);
    SDL_RenderCopy(renderer, interchange_sort_button, NULL, &interchange_sort_rect);
    SDL_RenderCopy(renderer, counting_sort_button, NULL, &counting_sort_rect);
    SDL_RenderCopy(renderer, quick_sort_button, NULL, &quick_sort_rect);
    SDL_RenderCopy(renderer, heap_sort_button, NULL, &heap_sort_rect);
    SDL_RenderCopy(renderer, merge_sort_button, NULL, &merge_sort_rect);

    SDL_SetRenderDrawColor(renderer, 0, 153, 231, 255);
    square_rect = {10, 10, (WIDTH * 10) - 20, (HEIGHT * 10) - 200};
    SDL_RenderFillRect(renderer, &square_rect);
    generateArray();
    firstDraw(main_vector, renderer);
}

void Sort::sortAction(SDL_Event &event, bool &quit, SDL_Renderer *&renderer)
{
    while (SDL_PollEvent(&event) != 0)
    {
        if (!is_sorting)
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }
            else if (event.type == SDL_MOUSEMOTION)
            {
                change_hovered = Utils::isMouseOverButton(change_rect);
                back_hovered = Utils::isMouseOverButton(back_rect);
                selection_sort_hovered = Utils::isMouseOverButton(selection_sort_rect);
                insertion_sort_hovered = Utils::isMouseOverButton(insertion_sort_rect);
                bubble_sort_hovered = Utils::isMouseOverButton(bubble_sort_rect);
                interchange_sort_hovered = Utils::isMouseOverButton(interchange_sort_rect);
                counting_sort_hovered = Utils::isMouseOverButton(counting_sort_rect);
                quick_sort_hovered = Utils::isMouseOverButton(quick_sort_rect);
                heap_sort_hovered = Utils::isMouseOverButton(heap_sort_rect);
                merge_sort_hovered = Utils::isMouseOverButton(merge_sort_rect);

                if (selection_sort_hovered || back_hovered || change_hovered || insertion_sort_hovered || bubble_sort_hovered || interchange_sort_hovered || counting_sort_hovered ||
                    quick_sort_hovered || heap_sort_hovered || merge_sort_hovered)
                {
                    cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
                    SDL_SetCursor(cursor);
                }
                else
                {
                    SDL_FreeCursor(cursor);
                }
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                if (change_hovered)
                {
                    SDL_SetRenderDrawColor(renderer, 0, 153, 231, 255);
                    SDL_RenderFillRect(renderer, &square_rect);
                    generateArray();
                    firstDraw(main_vector, renderer);
                    SDL_RenderPresent(renderer);
                }
                else if (back_hovered)
                {
                    destroy();
                    current_page = menu_page;
                }
                else if (selection_sort_hovered)
                {
                    vector<int> selection_sort_vector(main_vector.begin(), main_vector.end());
                    sort_thread = std::thread(&Sort::selectionSort, this, std::ref(renderer), std::ref(selection_sort_vector), std::ref(is_sorting));
                }
                else if (insertion_sort_hovered)
                {
                    sort_thread = std::thread(&Sort::insertionSort, this, std::ref(renderer));
                }
                else if (bubble_sort_hovered)
                {
                    sort_thread = std::thread(&Sort::bubbleSort, this, std::ref(renderer));
                }
                else if (interchange_sort_hovered)
                {
                    sort_thread = std::thread(&Sort::interchangeSort, this, std::ref(renderer));
                }
                else if (counting_sort_hovered)
                {
                    sort_thread = std::thread(&Sort::countingSort, this, std::ref(renderer));
                }
                else if (quick_sort_hovered)
                {
                    vector<int> sort_vector(main_vector.begin(), main_vector.end());
                    sort_thread = std::thread(&Sort::quickSort, this, std::ref(renderer), std::ref(sort_vector), 0, sort_vector.size() - 1);
                }
                else if (heap_sort_hovered)
                {
                    vector<int> sort_vector(main_vector.begin(), main_vector.end());
                    sort_thread = std::thread(&Sort::heapSort, this, std::ref(renderer));
                }
            }
        }
        else
        {
            if (event.type == SDL_MOUSEMOTION)
            {
                cancel_hovered = Utils::isMouseOverButton(cancel_rect);

                if (cancel_hovered)
                {
                    cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
                    SDL_SetCursor(cursor);
                }
                else
                {
                    SDL_FreeCursor(cursor);
                }
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                if (cancel_hovered)
                {
                    is_sorting = false;
                    sort_thread.join();
                    SDL_SetRenderDrawColor(renderer, 0, 153, 231, 255);
                    SDL_RenderFillRect(renderer, &square_rect);
                    firstDraw(main_vector, renderer);
                    unBlockButton(renderer);
                    SDL_RenderPresent(renderer);
                }
            }
        }
    }
}

void Sort::destroy()
{
    SDL_DestroyTexture(change_button);
    SDL_DestroyTexture(change_disable);
    SDL_DestroyTexture(back_button);
    SDL_DestroyTexture(back_disable);
    SDL_DestroyTexture(selection_sort_button);
    SDL_DestroyTexture(selection_sort_disable);
    SDL_DestroyTexture(insertion_sort_button);
    SDL_DestroyTexture(insertion_sort_disable);
    SDL_DestroyTexture(bubble_sort_button);
    SDL_DestroyTexture(bubble_sort_disable);
    SDL_DestroyTexture(cancel_button);
    SDL_DestroyTexture(cancel_disable);
    SDL_DestroyTexture(interchange_sort_button);
    SDL_DestroyTexture(interchange_sort_disable);
    SDL_DestroyTexture(counting_sort_button);
    SDL_DestroyTexture(counting_sort_disable);
    SDL_DestroyTexture(quick_sort_button);
    SDL_DestroyTexture(quick_sort_disable);
    SDL_DestroyTexture(heap_sort_button);
    SDL_DestroyTexture(heap_sort_disable);
    SDL_DestroyTexture(merge_sort_button);
    SDL_DestroyTexture(merge_sort_disable);
    SDL_FreeCursor(cursor);
}

void Sort::blockButton(SDL_Renderer *&renderer)
{
    SDL_FreeCursor(cursor);
    SDL_RenderCopy(renderer, change_disable, NULL, &change_rect);
    SDL_RenderCopy(renderer, back_disable, NULL, &back_rect);
    SDL_RenderCopy(renderer, selection_sort_disable, NULL, &selection_sort_rect);
    SDL_RenderCopy(renderer, cancel_button, NULL, &cancel_rect);
    SDL_RenderCopy(renderer, insertion_sort_disable, NULL, &insertion_sort_rect);
    SDL_RenderCopy(renderer, bubble_sort_disable, NULL, &bubble_sort_rect);
    SDL_RenderCopy(renderer, interchange_sort_disable, NULL, &interchange_sort_rect);
    SDL_RenderCopy(renderer, counting_sort_disable, NULL, &counting_sort_rect);
    SDL_RenderCopy(renderer, quick_sort_disable, NULL, &quick_sort_rect);
    SDL_RenderCopy(renderer, heap_sort_disable, NULL, &heap_sort_rect);
    SDL_RenderCopy(renderer, merge_sort_disable, NULL, &merge_sort_rect);
}

void Sort::unBlockButton(SDL_Renderer *&renderer)
{
    SDL_RenderCopy(renderer, change_button, NULL, &change_rect);
    SDL_RenderCopy(renderer, back_button, NULL, &back_rect);
    SDL_RenderCopy(renderer, selection_sort_button, NULL, &selection_sort_rect);
    SDL_RenderCopy(renderer, cancel_disable, NULL, &cancel_rect);
    SDL_RenderCopy(renderer, insertion_sort_button, NULL, &insertion_sort_rect);
    SDL_RenderCopy(renderer, bubble_sort_button, NULL, &bubble_sort_rect);
    SDL_RenderCopy(renderer, interchange_sort_button, NULL, &interchange_sort_rect);
    SDL_RenderCopy(renderer, counting_sort_button, NULL, &counting_sort_rect);
    SDL_RenderCopy(renderer, quick_sort_button, NULL, &quick_sort_rect);
    SDL_RenderCopy(renderer, heap_sort_button, NULL, &heap_sort_rect);
    SDL_RenderCopy(renderer, merge_sort_button, NULL, &merge_sort_rect);
}

void Sort::threadManager(SDL_Renderer *&renderer)
{
    while (!exit_thread_manager)
    {
        if (!is_sorting && sort_thread.joinable())
        {
            sort_thread.join();
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            SDL_SetRenderDrawColor(renderer, 0, 153, 231, 255);
            square_rect = {10, 10, (WIDTH * 10) - 20, (HEIGHT * 10) - 200};
            SDL_RenderFillRect(renderer, &square_rect);
            firstDraw(main_vector, renderer);
            SDL_RenderPresent(renderer);
        }
    }
}

void Sort::selectionSort(SDL_Renderer *&renderer, vector<int> &sort_vector, bool &is_sorting)
{
    if (renderer != NULL)
        blockButton(renderer);
    is_sorting = true;
    int min_pos;
    for (unsigned int i = 0; i < sort_vector.size() && is_sorting; i++)
    {
        min_pos = i;
        if (renderer != NULL)
        {
            SDL_SetRenderDrawColor(renderer, 0, 153, 231, 255);
            SDL_RenderFillRect(renderer, &square_rect);
        }
        for (unsigned int j = i + 1; j < sort_vector.size() && is_sorting; j++)
        {
            if (sort_vector[j] < sort_vector[min_pos])
            {
                min_pos = j;
            }

            // // Draw
            if (renderer != NULL)
            {
                drawSelectionSort(sort_vector, renderer, i, min_pos, j);

                // // Show
                if (std::is_sorted(sort_vector.begin(), sort_vector.end()))
                {
                    unBlockButton(renderer);
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                    SDL_RenderSetScale(renderer, 10, 10);
                    SDL_RenderDrawLine(renderer, sort_vector.size(), square_rect.h / 10 - sort_vector[sort_vector.size() - 1], sort_vector.size(), square_rect.h / 10);
                    SDL_RenderDrawLine(renderer, sort_vector.size() - 1, square_rect.h / 10 - sort_vector[sort_vector.size() - 2], sort_vector.size() - 1, square_rect.h / 10);
                    SDL_RenderDrawLine(renderer, sort_vector.size() - 2, square_rect.h / 10 - sort_vector[sort_vector.size() - 3], sort_vector.size() - 2, square_rect.h / 10);
                    SDL_RenderSetScale(renderer, 1, 1);
                }
                else
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(delay_time));
                }
                SDL_RenderPresent(renderer);
            }
        }
        if (renderer != NULL)
        {
            SDL_SetRenderDrawColor(renderer, 0, 153, 231, 255);
            SDL_RenderFillRect(renderer, &square_rect);
            swap(sort_vector[min_pos], sort_vector[i]);
            drawSelectionSort(sort_vector, renderer, i, min_pos, min_pos);
            if (std::is_sorted(sort_vector.begin(), sort_vector.end()))
            {
                unBlockButton(renderer);
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderSetScale(renderer, 10, 10);
                SDL_RenderDrawLine(renderer, sort_vector.size(), square_rect.h / 10 - sort_vector[sort_vector.size() - 1], sort_vector.size(), square_rect.h / 10);
                SDL_RenderDrawLine(renderer, sort_vector.size() - 1, square_rect.h / 10 - sort_vector[sort_vector.size() - 2], sort_vector.size() - 1, square_rect.h / 10);
                SDL_RenderDrawLine(renderer, sort_vector.size() - 2, square_rect.h / 10 - sort_vector[sort_vector.size() - 3], sort_vector.size() - 2, square_rect.h / 10);
                SDL_RenderSetScale(renderer, 1, 1);
            }
            else
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(delay_time));
            }
            SDL_RenderPresent(renderer);
        }
    }
    is_sorting = false;
}

void Sort::drawSelectionSort(std::vector<int> vector, SDL_Renderer *renderer,
                             unsigned int green, unsigned int red, unsigned int blue)
{
    SDL_RenderSetScale(renderer, 10, 10);
    for (int i = 0; i < vector.size(); i++)
    {
        if (i == green)
        {
            SDL_SetRenderDrawColor(renderer, 125, 207, 182, 255);
        }
        else if (i == red)
        {
            SDL_SetRenderDrawColor(renderer, 251, 209, 162, 255);
        }
        else if (i == blue)
        {
            SDL_SetRenderDrawColor(renderer, 0, 178, 202, 255);
        }
        else
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        }
        SDL_RenderDrawLine(renderer, i + 1, square_rect.h / 10 - vector[i], i + 1, square_rect.h / 10);
    }
    SDL_RenderSetScale(renderer, 1, 1);
}

void Sort::insertionSort(SDL_Renderer *&renderer)
{
    blockButton(renderer);
    is_sorting = true;
    vector<int> sort_vector(main_vector.begin(), main_vector.end());
    int x, i, j;
    for (int i = 0; i < sort_vector.size() && is_sorting; i++)
    {
        x = sort_vector[i];
        j = i - 1;
        while (j >= 0 && x < sort_vector[j] && is_sorting)
        {
            SDL_SetRenderDrawColor(renderer, 0, 153, 231, 255);
            SDL_RenderFillRect(renderer, &square_rect);
            swap(sort_vector[j + 1], sort_vector[j]);
            j--;
            drawInsertionSort(sort_vector, renderer, i, j + 1);

            if (std::is_sorted(sort_vector.begin(), sort_vector.end()))
            {
                unBlockButton(renderer);
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderSetScale(renderer, 10, 10);
                SDL_RenderDrawLine(renderer, sort_vector.size(), square_rect.h / 10 - sort_vector[sort_vector.size() - 1], sort_vector.size(), square_rect.h / 10);
                SDL_RenderDrawLine(renderer, j + 2, square_rect.h / 10 - sort_vector[j + 1], j + 2, square_rect.h / 10);
                SDL_RenderSetScale(renderer, 1, 1);
            }
            else
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(delay_time));
            }
            SDL_RenderPresent(renderer);
        }
    }
    is_sorting = false;
}

void Sort::drawInsertionSort(vector<int> vector, SDL_Renderer *renderer,
                             unsigned int green, unsigned int red)
{
    SDL_RenderSetScale(renderer, 10, 10);
    for (int i = 0; i < vector.size(); i++)
    {
        if (i == green)
        {
            SDL_SetRenderDrawColor(renderer, 125, 207, 182, 255);
        }
        else if (i == red)
        {
            SDL_SetRenderDrawColor(renderer, 251, 209, 162, 255);
        }
        else
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        }
        SDL_RenderDrawLine(renderer, i + 1, square_rect.h / 10 - vector[i], i + 1, square_rect.h / 10);
    }
    SDL_RenderSetScale(renderer, 1, 1);
}

void Sort::bubbleSort(SDL_Renderer *&renderer)
{
    blockButton(renderer);
    is_sorting = true;
    vector<int> sort_vector(main_vector.begin(), main_vector.end());
    for (int i = sort_vector.size() - 1; i >= 0 && is_sorting; i--)
    {
        for (int j = 0; j < i && is_sorting; j++)
        {
            SDL_SetRenderDrawColor(renderer, 0, 153, 231, 255);
            SDL_RenderFillRect(renderer, &square_rect);
            if (sort_vector[j] > sort_vector[j + 1])
            {
                swap(sort_vector[j], sort_vector[j + 1]);
            }
            drawBubbleSort(sort_vector, renderer, j);
            if (std::is_sorted(sort_vector.begin(), sort_vector.end()))
            {
                unBlockButton(renderer);
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderSetScale(renderer, 10, 10);
                SDL_RenderDrawLine(renderer, 1, square_rect.h / 10 - sort_vector[0], 1, square_rect.h / 10);
                SDL_RenderDrawLine(renderer, 2, square_rect.h / 10 - sort_vector[1], 2, square_rect.h / 10);
                SDL_RenderSetScale(renderer, 1, 1);
            }
            else
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(delay_time));
            }
            SDL_RenderPresent(renderer);
        }
    }
    is_sorting = false;
}

void Sort::drawBubbleSort(vector<int> vector, SDL_Renderer *renderer, unsigned int red)
{
    SDL_RenderSetScale(renderer, 10, 10);
    for (int i = 0; i < vector.size(); i++)
    {
        if (i == red || i == red + 1)
        {
            SDL_SetRenderDrawColor(renderer, 251, 209, 162, 255);
        }
        else
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        }
        SDL_RenderDrawLine(renderer, i + 1, square_rect.h / 10 - vector[i], i + 1, square_rect.h / 10);
    }
    SDL_RenderSetScale(renderer, 1, 1);
}

void Sort::interchangeSort(SDL_Renderer *&renderer)
{
    blockButton(renderer);
    is_sorting = true;
    vector<int> sort_vector(main_vector.begin(), main_vector.end());
    for (int i = 0; i < sort_vector.size() && is_sorting; i++)
    {
        for (int j = i + 1; j < sort_vector.size() && is_sorting; j++)
        {
            SDL_SetRenderDrawColor(renderer, 0, 153, 231, 255);
            SDL_RenderFillRect(renderer, &square_rect);
            if (sort_vector[i] > sort_vector[j])
            {
                swap(sort_vector[i], sort_vector[j]);
            }
            drawInterchangeSort(sort_vector, renderer, i, j);
            if (std::is_sorted(sort_vector.begin(), sort_vector.end()))
            {
                unBlockButton(renderer);
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderSetScale(renderer, 10, 10);
                SDL_RenderDrawLine(renderer, sort_vector.size(), square_rect.h / 10 - sort_vector[sort_vector.size() - 1], sort_vector.size(), square_rect.h / 10);
                SDL_RenderDrawLine(renderer, sort_vector.size() - 1, square_rect.h / 10 - sort_vector[sort_vector.size() - 2], sort_vector.size() - 1, square_rect.h / 10);
                SDL_RenderSetScale(renderer, 1, 1);
            }
            else
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(delay_time));
            }
            SDL_RenderPresent(renderer);
        }
    }
    is_sorting = false;
}

void Sort::drawInterchangeSort(vector<int> vector, SDL_Renderer *renderer, unsigned int red, unsigned int blue)
{
    SDL_RenderSetScale(renderer, 10, 10);
    for (int i = 0; i < vector.size(); i++)
    {
        if (i == red)
        {
            SDL_SetRenderDrawColor(renderer, 251, 209, 162, 255);
        }
        else if (i == blue)
        {
            SDL_SetRenderDrawColor(renderer, 0, 178, 202, 255);
        }
        else
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        }
        SDL_RenderDrawLine(renderer, i + 1, square_rect.h / 10 - vector[i], i + 1, square_rect.h / 10);
    }
    SDL_RenderSetScale(renderer, 1, 1);
}

void Sort::countingSort(SDL_Renderer *&renderer)
{
    blockButton(renderer);
    is_sorting = true;
    vector<int> sort_vector(main_vector.begin(), main_vector.end());
    auto max_element = std::max_element(sort_vector.begin(), sort_vector.end());
    vector<int> counting_vector(static_cast<int>(*max_element));

    TTF_Font *font = TTF_OpenFont("fonts/arial.ttf", 25);
    SDL_Surface *element_surface = TTF_RenderText_Solid(font, "Element: ", {0, 153, 231, 255});
    SDL_Texture *element_texture = SDL_CreateTextureFromSurface(renderer, element_surface);
    SDL_Rect element_rect = {cancel_rect.x + cancel_rect.w + 5, cancel_rect.y, 70, 16};
    SDL_RenderCopy(renderer, element_texture, NULL, &element_rect);

    SDL_Surface *total_surface = TTF_RenderText_Solid(font, "Total: ", {0, 153, 231, 255});
    SDL_Texture *total_texture = SDL_CreateTextureFromSurface(renderer, total_surface);
    SDL_Rect total_rect = {cancel_rect.x + cancel_rect.w + 5, cancel_rect.y + element_rect.h, 40, 16};
    SDL_RenderCopy(renderer, total_texture, NULL, &total_rect);

    for (int i = 0; i < counting_vector.size() && is_sorting; i++)
    {
        std::string numberString;
        if (i + 1 < 10)
        {
            numberString = "0" + std::to_string(i + 1);
        }
        else
        {
            numberString = std::to_string(i + 1);
        }

        SDL_Surface *counting_surface = TTF_RenderText_Solid(font, numberString.c_str(), {0, 153, 231, 255});
        SDL_Texture *counting_texture = SDL_CreateTextureFromSurface(renderer, counting_surface);

        SDL_Rect first_counting_rect = {element_rect.x + element_rect.w + 17 * i, cancel_rect.y, 12, 15};
        SDL_RenderCopy(renderer, counting_texture, NULL, &first_counting_rect);

        SDL_RenderPresent(renderer);

        SDL_FreeSurface(counting_surface);
        SDL_DestroyTexture(counting_texture);
    }

    SDL_Rect total_square_rect = {element_rect.x + element_rect.w, cancel_rect.y + element_rect.h,
                                  square_rect.x + square_rect.w - (element_rect.x + element_rect.w), total_rect.h};

    renderTotal(counting_vector, renderer, total_square_rect, is_sorting, font, element_rect, total_rect);

    for (int i = 0; i < sort_vector.size() && is_sorting; i++)
    {
        SDL_RenderSetScale(renderer, 10, 10);
        SDL_SetRenderDrawColor(renderer, 251, 209, 162, 255);
        SDL_RenderDrawLine(renderer, i + 1, square_rect.h / 10 - sort_vector[i], i + 1, square_rect.h / 10);
        SDL_RenderSetScale(renderer, 1, 1);
        SDL_RenderPresent(renderer);
        std::this_thread::sleep_for(std::chrono::milliseconds(delay_time * 50));
        counting_vector[sort_vector[i] - 1]++;
        SDL_RenderSetScale(renderer, 10, 10);
        SDL_SetRenderDrawColor(renderer, 0, 153, 231, 255);
        SDL_RenderDrawLine(renderer, i + 1, square_rect.h / 10 - sort_vector[i], i + 1, square_rect.h / 10);
        SDL_RenderSetScale(renderer, 1, 1);
        renderTotal(counting_vector, renderer, total_square_rect, is_sorting, font, element_rect, total_rect);
        SDL_RenderPresent(renderer);
        std::this_thread::sleep_for(std::chrono::milliseconds(delay_time * 50));
    }
    int sort_index = 0;
    for (int i = 0; i < counting_vector.size() && is_sorting; i++)
    {
        while (counting_vector[i] > 0 && is_sorting)
        {
            sort_vector[sort_index] = i + 1;
            renderTotal(counting_vector, renderer, total_square_rect, is_sorting, font, element_rect, total_rect);
            SDL_RenderSetScale(renderer, 10, 10);
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderDrawLine(renderer, sort_index + 1, square_rect.h / 10 - sort_vector[sort_index], sort_index + 1, square_rect.h / 10);
            SDL_RenderSetScale(renderer, 1, 1);
            SDL_RenderPresent(renderer);
            std::this_thread::sleep_for(std::chrono::milliseconds(delay_time * 50));
            sort_index++;
            counting_vector[i]--;
        }
    }

    SDL_Rect full_rect = {cancel_rect.x + cancel_rect.w + 5, cancel_rect.y,
                          square_rect.w - (cancel_rect.x + cancel_rect.w), cancel_rect.h};
    SDL_SetRenderDrawColor(renderer, 239, 241, 250, 255);
    SDL_RenderFillRect(renderer, &full_rect);
    unBlockButton(renderer);
    SDL_RenderPresent(renderer);

    is_sorting = false;
}

void Sort::renderTotal(vector<int> vector, SDL_Renderer *renderer, SDL_Rect square_rect, bool is_sorting,
                       TTF_Font *font, SDL_Rect element_rect, SDL_Rect total_rect)
{
    SDL_SetRenderDrawColor(renderer, 239, 241, 250, 255);
    SDL_RenderFillRect(renderer, &square_rect);

    for (int i = 0; i < vector.size() && is_sorting; i++)
    {
        std::string numberString;
        if (vector[i] < 10)
        {
            numberString = "0" + std::to_string(vector[i]);
        }
        else
        {
            numberString = std::to_string(vector[i]);
        }

        SDL_Surface *counting_surface = TTF_RenderText_Solid(font, numberString.c_str(), {0, 153, 231, 255});
        SDL_Texture *counting_texture = SDL_CreateTextureFromSurface(renderer, counting_surface);

        SDL_Rect first_counting_rect = {element_rect.x + element_rect.w + 17 * i, total_rect.y, 12, 15};
        SDL_RenderCopy(renderer, counting_texture, NULL, &first_counting_rect);

        SDL_RenderPresent(renderer);

        SDL_FreeSurface(counting_surface);
        SDL_DestroyTexture(counting_texture);
    }
}

void Sort::drawQuickSort(vector<int> vector, SDL_Renderer *&renderer, unsigned int green, unsigned int red_left, unsigned int red_right)
{
    SDL_RenderSetScale(renderer, 10, 10);
    for (int i = 0; i < vector.size(); i++)
    {
        if (i == green)
        {
            SDL_SetRenderDrawColor(renderer, 125, 207, 182, 255);
        }
        else if (i == red_left || i == red_right)
        {
            SDL_SetRenderDrawColor(renderer, 251, 209, 162, 255);
        }
        else
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        }
        SDL_RenderDrawLine(renderer, i + 1, square_rect.h / 10 - vector[i], i + 1, square_rect.h / 10);
    }
    SDL_RenderSetScale(renderer, 1, 1);
}

void Sort::quickSort(SDL_Renderer *&renderer, vector<int> &sort_vector, int left, int right)
{
    blockButton(renderer);
    SDL_RenderPresent(renderer);
    is_sorting = true;

    int mid = sort_vector[(left + right) / 2];
    int i = left;
    int j = right;

    drawQuickSort(sort_vector, renderer, (left + right) / 2, i, j);
    SDL_RenderPresent(renderer);
    std::this_thread::sleep_for(std::chrono::milliseconds(delay_time));

    while (i <= j)
    {
        while (sort_vector[i] < mid)
        {
            i++;
            drawQuickSort(sort_vector, renderer, (left + right) / 2, i, j);
            SDL_RenderPresent(renderer);
            std::this_thread::sleep_for(std::chrono::milliseconds(delay_time));
        }
        while (sort_vector[j] > mid)
        {
            j--;
            drawQuickSort(sort_vector, renderer, (left + right) / 2, i, j);
            SDL_RenderPresent(renderer);
            std::this_thread::sleep_for(std::chrono::milliseconds(delay_time));
        }
        if (i <= j)
        {
            swap(sort_vector[i], sort_vector[j]);
            i++;
            j--;
            SDL_SetRenderDrawColor(renderer, 0, 153, 231, 255);
            SDL_RenderFillRect(renderer, &square_rect);
            drawQuickSort(sort_vector, renderer, (left + right) / 2, i, j);
            SDL_RenderPresent(renderer);
            std::this_thread::sleep_for(std::chrono::milliseconds(delay_time));
        }
    }

    if (left < j)
        quickSort(renderer, sort_vector, left, j);
    if (i < right)
        quickSort(renderer, sort_vector, i, right);

    if (std::is_sorted(sort_vector.begin(), sort_vector.end()))
    {
        unBlockButton(renderer);
        SDL_RenderPresent(renderer);
        is_sorting = false;
    }
    else
    {
        // std::this_thread::sleep_for(std::chrono::milliseconds(delay_time));
    }
}

void Sort::heapify(SDL_Renderer *&renderer, vector<int> &sort_vector, int n, int i)
{
    int largest = i;
    // Get child node
    int left = 2*i + 1;
    int right = 2*i + 2;

    SDL_SetRenderDrawColor(renderer, 0, 153, 231, 255);
    SDL_RenderFillRect(renderer, &square_rect);
    drawHeapSort(sort_vector, renderer, i, left, right);
    SDL_RenderPresent(renderer);
    std::this_thread::sleep_for(std::chrono::milliseconds(delay_time));

    if (left < n && sort_vector[left] > sort_vector[largest])
    {
        largest = left;
    }
    if (right < n && sort_vector[right] > sort_vector[largest])
    {
        largest = right;
    }
    if (largest != i) {
        SDL_SetRenderDrawColor(renderer, 0, 153, 231, 255);
        SDL_RenderFillRect(renderer, &square_rect);
        drawHeapSort(sort_vector, renderer, largest, left, right);
        SDL_RenderPresent(renderer);
        std::this_thread::sleep_for(std::chrono::milliseconds(delay_time * 80));
        swap(sort_vector[i], sort_vector[largest]);
        SDL_SetRenderDrawColor(renderer, 0, 153, 231, 255);
        SDL_RenderFillRect(renderer, &square_rect);
        drawHeapSort(sort_vector, renderer, -1, -1, -1);
        SDL_RenderPresent(renderer);
        std::this_thread::sleep_for(std::chrono::milliseconds(delay_time * 80));
        // Heapify child node
        heapify(renderer, sort_vector, n, largest);
    }
}

void Sort::heapSort(SDL_Renderer*& renderer)
{
    blockButton(renderer);
    is_sorting = true;
    vector<int> sort_vector(main_vector.begin(), main_vector.end());

    // Heapify the node which is not a leaf node
    for(int i = sort_vector.size()/2 - 1; i >= 0; i--)
    {
        heapify(renderer, sort_vector, sort_vector.size(), i);
    }
    // Heap sort
    for (int i = sort_vector.size() - 1; i >=0; i--)
    {
        SDL_SetRenderDrawColor(renderer, 0, 153, 231, 255);
        SDL_RenderFillRect(renderer, &square_rect);
        drawHeapSort(sort_vector, renderer, i, -1, -1);
        SDL_RenderPresent(renderer);
        std::this_thread::sleep_for(std::chrono::milliseconds(delay_time * 80));
        // Move the max heap to the last
        swap(sort_vector[0], sort_vector[i]);
        SDL_SetRenderDrawColor(renderer, 0, 153, 231, 255);
        SDL_RenderFillRect(renderer, &square_rect);
        drawHeapSort(sort_vector, renderer, i, -1, -1);
        SDL_RenderPresent(renderer);
        std::this_thread::sleep_for(std::chrono::milliseconds(delay_time * 80));
        // Heapify the array with removed the max heap to find another max heap
        heapify(renderer, sort_vector, i, 0);
    }

    unBlockButton(renderer);
    SDL_RenderPresent(renderer);

    is_sorting = false;
}

void Sort::drawHeapSort(vector<int> vector, SDL_Renderer*& renderer,
 int green, int red_left, int red_right)
{
    SDL_RenderSetScale(renderer, 10, 10);
    for (int i = 0; i < vector.size(); i++)
    {
        if (i == green)
        {
            SDL_SetRenderDrawColor(renderer, 125, 207, 182, 255);
        }
        else if (i == red_left || i == red_right)
        {
            SDL_SetRenderDrawColor(renderer, 251, 209, 162, 255);
        }
        else
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        }
        SDL_RenderDrawLine(renderer, i + 1, square_rect.h / 10 - vector[i], i + 1, square_rect.h / 10);
    }
    SDL_RenderSetScale(renderer, 1, 1);
}