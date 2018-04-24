#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "randomart.h"

int main(int argc, char **argv)
{
    if(argc < 2 || strlen(argv[1]) != 47) {
        printf("./randomart [:fingerprint]\n");
        printf("Example: ./randomart fc:94:b0:c1:e5:b0:98:7c:58:43:99:76:97:ee:9f:b7");
        exit(1);
    }

    const char *fingerprint = argv[1];
    int size = strlen(fingerprint), i;
    int x, y;

    Board *board = generate_board(9, 17);
    x = 8;
    y = 4;

    board->field[y][x].start = 1; // set START POSITION

    for(i = 0; i < size; i += 3) {
        int *_partial = parse_partial_fingerprint(fingerprint + i);
        int *_coords = move_into_board(_partial, board, x, y);

        x = _coords[0];
        y = _coords[1];
    }

    board->field[y][x].end = 1; // set END POSITION
    display_board(board);

    free_board(board);

    return 0;
}
