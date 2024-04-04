// #define STATES states[WINDOW_WIDTH / BRIC_SIZE][WINDOW_HEIGHT / BRIC_SIZE]

#include <SDL2/SDL.h>
#include <stdio.h>
#include "bric.c"

void init_states(int states[MAX][MAX])
{
    for (size_t i = 0; i < MAX; i++)
    {
        for (size_t j = 0; j < MAX; j++)
        {
            states[i][j] = EMPTY;
        }
    }
}

void clear_states(int states[MAX][MAX])
{
    for (size_t i = 0; i < MAX; i++)
    {
        for (size_t j = 0; j < MAX; j++)
        {
            if (states[i][j] == OCCUPIED)
            {
                continue;
            }

            states[i][j] = EMPTY;
        }
    }
}

void draw_states(SDL_Renderer *renderer, SDL_Color color, int states[MAX][MAX])
{

    for (size_t i = 0; i < MAX; i++)
    {
        for (size_t j = 0; j < MAX; j++)
        {
            int state = states[i][j];
            if (state == FULL || state == OCCUPIED)
            {
                SDL_Rect rec = {i * BRIC_SIZE, j * BRIC_SIZE, BRIC_SIZE, BRIC_SIZE};
                SDL_RenderFillRect(renderer, &rec);
            }
        }
    }
}

SDL_bool has_complete_brik(int states[MAX][MAX])
{
    for (size_t i = 0; i < MAX; i++)
    {

        for (size_t j = 0; j < MAX; j++)
        {
            int state = states[i][j];
            if (state == FULL)
            {

                if (j * BRIC_SIZE == WINDOW_HEIGHT - BRIC_SIZE)
                {

                    return SDL_TRUE;
                }
                if (states[i][j + 1] == OCCUPIED)
                {
                    return SDL_TRUE;
                }
            }
        }
    }
}

void stop_complete_bricks(int states[MAX][MAX])
{
    for (size_t i = 0; i < MAX; i++)
    {
        for (size_t j = 0; j < MAX; j++)
        {
            int state = states[i][j];
            if (state == FULL)
            {
                states[i][j] = OCCUPIED;
            }
        }
    }
}

SDL_bool has_movable_bric(int states[MAX][MAX])
{
    for (size_t i = 0; i < MAX; i++)
    {

        for (size_t j = 0; j < MAX; j++)
        {
            int state = states[i][j];
            if (state == FULL)
            {
                return SDL_TRUE;
            }
        }
    }
    return SDL_FALSE;
}

void draw_grid(SDL_Renderer *renderer, SDL_Color color)
{

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    for (size_t i = 0; i < MAX; i++)
    {
        SDL_RenderDrawLine(renderer, 0, i * BRIC_SIZE, WINDOW_WIDTH, i * BRIC_SIZE);
    }
    for (size_t i = 0; i < MAX; i++)
    {
        SDL_RenderDrawLine(renderer, i * BRIC_SIZE, 0, i * BRIC_SIZE, WINDOW_HEIGHT);
    }
}

SDL_bool is_line_occupied(int states[MAX][MAX], int y)
{
    SDL_bool occupied = SDL_TRUE;
    for (size_t i = 0; i < MAX; i++)
    {
        if (states[i][y] != OCCUPIED)
        {
            occupied = SDL_FALSE;
        }
    }
    return occupied;
}

void move_occupieds_down(int states[MAX][MAX], int deleted_lines_count, int deleted_line_y)
{
    printf("fayyaa");
    for (size_t i = 0; i < MAX; i++)
    {
        for (size_t j = 0; j < deleted_line_y; j++)
        {
            if (states[i][j] == OCCUPIED)
            {
                states[i][j + deleted_lines_count] = OCCUPIED;
                states[i][j] = EMPTY;
            }
        }
    }
}
SDL_bool delete_lines(int states[MAX][MAX], int *deleted_lines_count, int *deleted_line_y)
{
    SDL_bool deleted = SDL_FALSE;
    for (size_t j = 0; j < MAX; j++)
    {
        if (is_line_occupied(states, j))
        {
            for (size_t i = 0; i < MAX; i++)
            {
                states[i][j] = EMPTY;
            }
            deleted = SDL_TRUE;
            *deleted_lines_count = *deleted_lines_count + 1;
            if (*deleted_line_y == 0)
            {
                *deleted_line_y = j;
            }
        }
    }

    return deleted;
}

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *window = SDL_CreateWindow("Tetris",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          WINDOW_WIDTH,
                                          WINDOW_HEIGHT,
                                          SDL_WINDOW_SHOWN);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    int states[MAX][MAX];
    init_states(states);

    SDL_Point current_point = {0, 0};
    int orientation = 0;
    int current_form = rand() & FORM_COUNT;
    int speed_factor = 1;

    int r_max = 4;
    void *form = get_form(current_form, &r_max);
    int z = orientation % r_max;

    SDL_Event event;
    int run = SDL_TRUE;
    int ticks = 0;

    while (run)
    {
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT)
        {
            run = SDL_FALSE;
        }

        if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == SDLK_RIGHT)
            {
                if (current_point.x < MAX - 2)
                    current_point.x += 1;
            }
            if (event.key.keysym.sym == SDLK_LEFT)
            {
                if (current_point.x > 0)
                    current_point.x -= 1;
            }
            if (event.key.keysym.sym == SDLK_UP)
            {
                orientation += 1;
            }
            speed_factor = 1;
            if (event.key.keysym.sym == SDLK_DOWN)
            {
                speed_factor = 5;
            }
        }

        int current_tick = SDL_GetTicks();
        if (current_tick - ticks > DOWN_TIME / speed_factor)
        {
            ticks = current_tick;
            current_point.y += 1;

            if (has_complete_brik(states) == SDL_TRUE)
            {
                stop_complete_bricks(states);
            }

            if (has_movable_bric(states) == SDL_FALSE)
            {
                current_form = rand() & FORM_COUNT;
                current_point.y = 0;
                current_point.x = MAX / 2;
                form = get_form(current_form, &r_max);
            }

            int deleted_lines_count = 0;
            int deleted_line_y = 0;

            if (delete_lines(states, &deleted_lines_count, &deleted_line_y) == SDL_TRUE)
            {
                // printf("deleted_lines_count : %d, deleted_line_y : %d\n", deleted_lines_count, deleted_line_y);

                move_occupieds_down(states, deleted_lines_count, deleted_line_y);
                deleted_lines_count = 0;
                deleted_line_y = 0;
            }
        }

        SDL_SetRenderDrawColor(renderer, black_color.r, black_color.g, black_color.b, black_color.a);
        SDL_RenderClear(renderer);

        clear_states(states);

        SDL_SetRenderDrawColor(renderer, red_color.r, red_color.g, red_color.b, red_color.a);

        int x = current_point.x;
        int y = current_point.y;
        z = orientation % r_max;

        // printf("x : %d, y : %d, orientation : %d, form : %d, z : %d, r_max : %d\n", x, y, orientation, current_form, z, r_max);

        insert_bric(x, y, z, form, states);

        draw_states(renderer, red_color, states);

        draw_grid(renderer, blue_color);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}
