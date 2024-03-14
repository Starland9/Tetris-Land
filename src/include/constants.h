#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600

#define BRIC_SIZE WINDOW_HEIGHT / 20

SDL_Color white_color = {255, 255, 255, 255};
SDL_Color black_color = {0, 0, 0, 0};

SDL_Color red_color = {255, 0, 0, 255};
SDL_Color blue_color = {0, 0, 255, 255};

enum brick_state
{
    EMPTY = 0,
    FULL = 1,
    OCCUPIED = 2
};