/**
 * Largeur de la fenètre
 */
#define WINDOW_WIDTH 600

/**
 * Auteur
 */
#define WINDOW_HEIGHT 600

#define BRIC_COUNT 10
#define BRIC_SIZE WINDOW_HEIGHT / BRIC_COUNT

#define DOWN_TIME 300

#define FORM_COUNT 7

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

/// @brief Type de brique
enum bric_type
{
    SQUARE = 0,
    LINE = 1,
    L_RIGHT = 2,
    L_LEFT = 3,
    T = 4,
    CHAIR_RIGHT = 5,
    CHAIR_LEFT = 6,
};