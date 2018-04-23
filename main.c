#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "randomart.h"

int main(int argc, char **argv)
{
    const char *fingerprint = "fc:94:b0:c1:e5:b0:98:7c:58:43:99:76:97:ee:9f:b7";
    int size = strlen(fingerprint), i, j;
    int x, y, _x, _y;

    Board *board = generate_board(9, 17);
    x = _x = 8;
    y = _y = 4;

    board->field[y][x].start = 1; // START POSITION

    for(i = 0; i < size; i += 3) {
        int *_partial = parse_partial_fingerprint(fingerprint + i);

        for(j = 0; j < 4; j++) {
            if(_partial[j] & 2) { // SOUTH
                if(board->field[y][x].directions & SOUTH) {
                    _y++;
                }
            } else { // NORTH
                if(board->field[y][x].directions & NORTH) {
                    _y--;
                }
            }

            if(_partial[j] & 1) { // EAST
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
    }

    board->field[y][x].end = 1; // END POSITION
    display_board(board);

    free_board(board);

    return 0;
}
