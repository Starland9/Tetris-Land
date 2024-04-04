#include "include/constants.h"

int MAX = BRIC_COUNT;

int square[1][4][4] = {
    {
        {1, 1, 0, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
    },

};

int line[2][4][4] = {{
                         {1, 1, 1, 1},
                         {0, 0, 0, 0},
                         {0, 0, 0, 0},
                         {0, 0, 0, 0},
                     },
                     {
                         {1, 0, 0, 0},
                         {1, 0, 0, 0},
                         {1, 0, 0, 0},
                         {1, 0, 0, 0},
                     }

};

int l_right[4][4][4] = {
    {
        {1, 0, 0, 0},
        {1, 0, 0, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0},
    },
    {
        {0, 0, 1, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
    },
    {
        {1, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 0},
    },
    {
        {1, 1, 1, 0},
        {1, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
    },

};

int l_left[4][4][4] = {
    {
        {1, 1, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
    },
    {
        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0},
    },
    {
        {1, 0, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
    },
    {
        {1, 1, 0, 0},
        {1, 0, 0, 0},
        {1, 0, 0, 0},
        {0, 0, 0, 0},
    },

};

int t[4][4][4] = {
    {
        {1, 1, 1, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
    },
    {
        {0, 1, 0, 0},
        {1, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 0},
    },
    {
        {0, 1, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
    },
    {
        {0, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 0},
    },

};

int chair_right[2][4][4] = {
    {
        {1, 0, 0, 0},
        {1, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 0},
    },
    {
        {0, 1, 1, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
    },
};

int chair_left[2][4][4] = {
    {
        {0, 1, 0, 0},
        {1, 1, 0, 0},
        {1, 0, 0, 0},
        {0, 0, 0, 0},
    },
    {
        {1, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
    },
};

void *get_form(int type, int *r_max)
{

    // switch (type)
    // {
    // case SQUARE:
    //     *r_max = 1;
    //     return &square;
    //     break;

    // case LINE:
    //     *r_max = 2;

    //     return &line;
    //     break;

    // case L_RIGHT:
    //     *r_max = 4;

    //     return &l_right;
    //     break;

    // case L_LEFT:
    //     *r_max = 4;

    //     return &l_left;
    //     break;

    // case T:
    //     *r_max = 4;

    //     return &t;
    //     break;

    // case CHAIR_RIGHT:
    //     *r_max = 2;

    //     return &chair_right;
    //     break;

    // case CHAIR_LEFT:
    //     *r_max = 2;

    //     return &chair_left;
    //     break;

    // default:
    //     break;
    // }
    *r_max = 1;
    return &square;
}

void insert_bric(int x, int y, int r, void *form, int states[MAX][MAX])
{

    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            int(*formArray)[4][4][4] = (int(*)[4][4][4])form;
            int state = (*formArray)[r][i][j];
            if (state == 1)
            {
                states[x + i][y + j] = state;
            }
        }
    }
}
