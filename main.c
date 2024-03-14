// #define STATES states[WINDOW_WIDTH / BRIC_SIZE][WINDOW_HEIGHT / BRIC_SIZE]

#include <SDL2/SDL.h>
#include <include/constants.h>
#include <bric.c>
#include <stdio.h>

int MAX = 20;

void init_states(int states[MAX][MAX])
{
    printf("init states\n %d", MAX);
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

void insert_square_bric(int x, int y, int states[MAX][MAX])
{
    states[x][y] = 1;
    states[x][y + 1] = 1;
    states[x + 1][y] = 1;
    states[x + 1][y + 1] = 1;
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

void delete_lines(int states[MAX][MAX])
{

    for (size_t j = 0; j < MAX; j++)
    {
        if (is_line_occupied(states, j))
        {
            for (size_t i = 0; i < MAX; i++)
            {
                states[i][j] = EMPTY;
            }
        }
    }
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

    SDL_Event event;
    int run = SDL_TRUE;

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
                current_point.x += 1;
            }
            if (event.key.keysym.sym == SDLK_LEFT)
            {
                current_point.x -= 1;
            }
        }

        Uint32 tick = SDL_GetTicks();
        if (tick % 100 == 0)
        {
            current_point.y += 1;
            current_point.x += 0;

            if (has_complete_brik(states) == SDL_TRUE)
            {
                stop_complete_bricks(states);
            }

            if (has_movable_bric(states) == SDL_FALSE)
            {
                current_point.y = 0;
            }
            delete_lines(states);
        }

        SDL_SetRenderDrawColor(renderer, black_color.r, black_color.g, black_color.b, black_color.a);
        SDL_RenderClear(renderer);

        clear_states(states);

        insert_square_bric(current_point.x, current_point.y, states);
        SDL_SetRenderDrawColor(renderer, red_color.r, red_color.g, red_color.b, red_color.a);
        draw_states(renderer, red_color, states);

        draw_grid(renderer, blue_color);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}
