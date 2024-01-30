#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lut.h"

int w, h, board_size;

int padded_to_1d(int w, int h, int x, int y)
{
    return (w * y) + x + w + 1 ;
}

int neighbors_key(int* board, int w, int h, int x, int y)
{
    int key = 0 ;
    
    key |= board[padded_to_1d(w, h, x-1, y-1)] << 8 ; // neighbor 0
    key |= board[padded_to_1d(w, h, x, y-1)] << 7 ; // neighbor 1
    key |= board[padded_to_1d(w, h, x+1, y-1)] << 6 ; // neighbor 2

    key |= board[padded_to_1d(w, h, x-1, y)] << 5 ; // neighbor 3
    key |= board[padded_to_1d(w, h, x, y)] << 4 ; // neighbor 4 (self alive)
    key |= board[padded_to_1d(w, h, x+1, y)] << 3 ; // neighbor 5

    key |= board[padded_to_1d(w, h, x-1, y+1)] << 2 ; // neighbor 6
    key |= board[padded_to_1d(w, h, x, y+1)] << 1 ; // neighbor 7
    key |= board[padded_to_1d(w, h, x+1, y+1)] ; // neighbor 8 (no shift)

    return key ;
}


int* iteration(int* board, int* lut, int w, int h)
{
    int* board_copy = malloc( padded_to_1d(w, h, w+1, h+1) * sizeof(int) ) ;

    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            int current_pos = padded_to_1d(w, h, x, y) ;
            board_copy[current_pos] = lut[neighbors_key(board, w, h, x, y)] ;
        }
    }

    return board_copy;
}

int *fill_random(int w, int h)
{
    int *new_board = malloc( padded_to_1d(w, h, w+1, h+1) * sizeof(int) );

    for ( int y = 0; y < h; y++ )
    {
        for ( int x = 0; x < w; x++ )
        {
            new_board[ padded_to_1d(w, h, x, y) ] = random() % 10 > 6 ;
        }
    }

    return new_board;
}

void padded_print_board(int board[], int w, int h)
{
    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            printf( "%d ", board[ padded_to_1d(w, h, x, y) ] );
        }

        printf("\n");
    }
}

int* neighbor_map(int* board, int* lut, int w, int h)
{
    int* temp = malloc(sizeof(board));

    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            temp[ padded_to_1d(w, h, x, y) ] = lut[ neighbors_key(board, w, h, x, y) ] ;
        }
    }

    return temp;
}

void print_array(int* array, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", array[i]);
    }

    printf("\n");
}

int main()
{
    srandom(time(NULL));
    int* lut = LUT() ;

    int w = h = 10000 ;

    printf("start\n");
    int* board = fill_random(w, h);
    
    printf("generated random board\n");

    board = iteration(board, lut, w, h);

    printf("calculation finished :)\n");
    // padded_print_board(board, w, h);

    return 0;
}
