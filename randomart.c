#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "randomart.h"

Board *generate_board(int rows, int columns)
{
    Board *board = malloc(sizeof(Board *));
    if(!board) {
        exit(1);
    }

    board->rows = rows;
    board->columns = columns;
    board->field = malloc(sizeof(Position *) * rows);
    if(!board->field) {
        exit(1);
    }

    int x, y;
    for(y = 0; y < rows; y++) {
        board->field[y] = malloc(sizeof(Position) * columns);
        if(!board->field[y]) {
            exit(1);
        }

        for(x = 0; x < columns; x++) {
            board->field[y][x].x = x;
            board->field[y][x].y = y;
            board->field[y][x].p = x + 17 * y;
            board->field[y][x].iterations = 0;
            board->field[y][x].start = 0;
            board->field[y][x].end = 0;

            board->field[y][x].directions = NORTH | EAST | SOUTH | WEST;

            if(y == 0) { // NORTH
                board->field[y][x].directions ^= NORTH;
            } else if(y == rows - 1) { // SOUTH
                board->field[y][x].directions ^= SOUTH;
            }

            if(x == 0) { // WEST
                board->field[y][x].directions ^= WEST;
            } else if(x == columns - 1) { // EAST
                board->field[y][x].directions ^= EAST;
            }
        }
    }

    return board;
}

int __h2d(char hex)
{
    if(hex >= 'a' && hex <= 'z') return (hex - 'a') + 0xa;
    else return hex - '0';
}

int *parse_partial_fingerprint(const char *fingerprint)
{
    static int _partial[4];

    _partial[0] = __h2d((fingerprint + 1)[0]) & 3;
    _partial[1] = (__h2d((fingerprint + 1)[0]) & 0xc) >> 2;
    _partial[2] = __h2d(fingerprint[0]) & 3;
    _partial[3] = (__h2d(fingerprint[0]) & 0xc) >> 2;

    return _partial;
}

void display_board(Board *board)
{
    const char *symbols = " .o+=*B0X@%&#/^";
    int x, y;

    printf("+----[RSA1024]----+\n");

    for(y = 0; y < board->rows; y++) {
        printf("|");

        for(x = 0; x < board->columns; x++) {
            if(board->field[y][x].start) {
                printf("S");
            } else if(board->field[y][x].end) {
                printf("E");
            } else {
                printf("%c", symbols[board->field[y][x].iterations]);
            }
        }

        printf("|\n");
    }

    printf("+-----------------+\n");
}

void free_board(Board *board)
{
    printf("ok1\n");

    if(board) {
        if(board->field) {
            int y;
            for(y = 0; y < board->rows; y++) {
                if(board->field[y]) {
                    free(board->field[y]);
                }
            }

            printf("nok2\n");
            free(board->field);
            printf("nok3\n");
        }

        printf("ok\n");
        free(board);
        printf("nok\n");
    }
}
