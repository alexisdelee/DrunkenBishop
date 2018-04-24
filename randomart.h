#ifndef RANDOMART_H_INCLUDED
#define RANDOMART_H_INCLUDED

/**
 * position on 4 bits
 */

#define NORTH       1
#define EAST        2
#define SOUTH       4
#define WEST        8

typedef struct
{
    int x;
    int y;
    int p;
    int iterations;
    int start;
    int end;
    int directions;
} Position;

typedef struct
{
    Position **field;
    int rows;
    int columns;
} Board;

Board *generate_board(int, int);
int *parse_partial_fingerprint(const char *);
int *move_into_board(int *, Board *, int, int);
void display_board(Board *);
void free_board(Board *);

#endif // RANDOMART_H_INCLUDED
