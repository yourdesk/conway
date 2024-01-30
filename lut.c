#include <math.h>
#include <stdlib.h>

#define LUT_SIZE 512

int get_bit(int n, int bit_number)
{
    return 1 & ( n >> bit_number ) ;
}

int life(int self_alive, int neighbor_count)
{
    if ( self_alive == 0 && neighbor_count == 3 )
    {
        return 1;
    }
    
    if ( self_alive == 1 && (neighbor_count == 2 || neighbor_count == 3) )
    {
        return 1;
    }

    return 0;
}

int count_bits(int n)
{
    int v, c;
    for (c = 0; v; c++)
    {
        v &= v - 1 ;
    }
}

int* LUT()
{
    int* lut = malloc(LUT_SIZE * sizeof(int));

    for (int key = 0; key < LUT_SIZE; key++)
    {
        int self_alive = get_bit(key, 4) ;
        int neighbor_count = count_bits(key) - self_alive ;

        int is_alive = life(self_alive, neighbor_count) ;

        lut[key] = is_alive ;
    }

    return lut;
}