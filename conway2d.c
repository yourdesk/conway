#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lut.h"

int w, h;

int** alloc_2d(int w, int h)
{
    int **arr = malloc(h * sizeof(int*));
    
    for(int i = 0; i < h; i++) 
    {
        arr[i] = malloc(w * sizeof(int)); 
    }

    return arr ;
}

int neighbors_key(int** board, int x, int y)
{
    int key = 0 ;
    
    key |= board[y-1][x-1] << 8 ; // neighbor 0
    key |= board[y-1][x] << 7 ; // neighbor 1
    key |= board[y-1][x+1] << 6 ; // neighbor 2

    key |= board[y][x-1] << 5 ; // neighbor 3
    key |= board[y][x] << 4 ; // neighbor 4 (self alive)
    key |= board[y][x+1] << 3 ; // neighbor 5

    key |= board[y+1][x-1] << 2 ; // neighbor 6
    key |= board[y+1][x] << 1 ; // neighbor 7
    key |= board[y+1][x+1] ; // neighbor 8 (no shift)

    return key ;
}


int** iteration(int** board, int* lut, int w, int h)
{
    int** board_copy = alloc_2d(w+2, h+2) ;

    for (int y = 1; y < h + 1; y++)
    {
        for (int x = 1; x < w + 1; x++)
        {
            board_copy[y][x] = lut[ neighbors_key(board, x, y) ] ;
        }
    }

    return board_copy;
}

int** fill_random(int w, int h)
{
    int** new_board = alloc_2d(w+2, h+2);

    for ( int y = 1; y < h + 1; y++ )
    {
        for ( int x = 1; x < w + 1; x++ )
        {
            new_board[y][x] = random() % 10 > 6 ;
        }
    }

    return new_board;
}

void padded_print_board(int** board, int w, int h)
{
    for (int y = 1; y < h + 1; y++)
    {
        for (int x = 1; x < w + 1; x++)
        {
            printf( "%d ", board[y][x] );
        }

        printf("\n");
    }
}

int** neighbor_map(int** board, int* lut, int w, int h)
{
    int** temp = alloc_2d(w+2, h+2) ;

    for (int y = 1; y < h + 1; y++)
    {
        for (int x = 1; x < w + 1; x++)
        {
            temp[y][x] = lut[ neighbors_key(board, x, y) ] ;
        }
    }

    return temp;
}

int main()
{
    srandom(time(NULL));
    int* lut = LUT() ;

    w = h = 10000 ;

    printf("start\n");
    int** board = fill_random(w, h);
    
    printf("generated random board\n");

    board = iteration(board, lut, w, h);

    printf("calculation finished :)\n");

    return 0;
}
