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

int *move_into_board(int *_partial, Board *board, int x, int y)
{
    static int _coords[2];
    int i, _x = x, _y = y;

    for(i = 0; i < 4; i++) {
        if(_partial[i] & 2) { // SOUTH
            if(board->field[y][x].directions & SOUTH) {
                _y++;
            }
        } else { // NORTH
            if(board->field[y][x].directions & NORTH) {
                _y--;
            }
        }

        if(_partial[i] & 1) { // EAST
            if(board->field[y][x].directions & EAST) {
                _x++;
            }
        } else { // WEST
            if(board->field[y][x].directions & WEST) {
                _x--;
            }
        }

        x = _x;
        y = _y;

        board->field[y][x].iterations++;
    }

    _coords[0] = x;
    _coords[1] = y;

    return _coords;
}

void display_board(Board *board)
{
    const char *symbols = " .o+=*B0X@%&#/^";
    int x, y;

    printf("+----[       ]----+\n");

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
    if(board) {
        if(board->field) {
            int y;
            for(y = 0; y < board->rows; y++) {
                if(board->field[y]) {
                    free(board->field[y]);
                }
            }

            free(board->field);
        }

        free(board);
    }
}
