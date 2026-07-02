#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

bool check(int board[], int size, int index) {
    int side = (int)sqrt(size);
    int x = index % side;
    int y = (int)(index / side);
    int value = board[index];
    int box_start_pos = (index % (int)(side * sqrt(side))) % side;

    for (int i = 0; i < side; i++) {
        int hor_current_index = i + y * side;
        if (board[hor_current_index] == value && hor_current_index != index) {
            return false;
        }

        int box_current_index = (int)(index / (side * sqrt(side))) * side * (int)sqrt(side) + (int)((int)(index % side / sqrt(side)) * sqrt(side)) + (int)(i / sqrt(side)) * side + i % (int)sqrt(side);
        if (board[box_current_index] == value && box_current_index != index) {
            return false;
        }

        int ver_current_index = x + i * side;
        if (board[ver_current_index] == value && ver_current_index != index) {
            return false;
        }
    }
    
    return true;
}

void print_line(int length) {
    for (int i = 0; i < length; i++) {
        printf("-");
    }

    printf("\n");
}

void show(int board[], int size) {

    int side = (int)sqrt(size);
    for (int i = 0; i < size; i++) {
        if (i % side == 0 && i > 0) {
            printf("|\n");
        }

        if (i % ((int)sqrt(side) * side) == 0) {
            print_line(side * 3 + (int)sqrt(side) + 1);
        }

        if (i % (int)sqrt(side) == 0) {
            printf("|");
        }


        printf(" %d ", board[i]);
    }

    printf("|\n");
    print_line(side * 3 + (int)sqrt(side) + 1);
}

int main() {
    int board[] = {
        8, 0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0, 3, 6, 0, 0, 0, 0, 0, 
        0, 7, 0, 0, 9, 0, 2, 0, 0, 
        0, 5, 0, 0, 0, 7, 0, 0, 0, 
        0, 0, 0, 0, 4, 5, 7, 0, 0, 
        0, 0, 0, 1, 0, 0, 0, 3, 0, 
        0, 0, 1, 0, 0, 0, 0, 6, 8, 
        0, 0, 8, 5, 0, 0, 0, 1, 0, 
        0, 9, 0, 0, 0, 0, 4, 0, 0 
    }; 
    /*int board[] = {
       0, 0, 0, 0,  
       0, 0, 0, 0, 
       0, 0, 0, 0,
       0, 0, 0, 0 
    }; */
    
    int size = *(&board + 1) - board;
    int side = (int)sqrt(size);

    int *mod = malloc(sizeof(int) * size);

    for (int i = 0; i < size; i++) {
        if (board[i] == 0) {
            mod[i] = 1;
        }
    }

    int direction = 1;
    
    int current_index = 0;
    int loop_count = 0;
    while (true) {
        loop_count += 1;

        if (mod[current_index] == 0) {
            current_index += direction;
            continue;
        }

        if (board[current_index] == side) {
            board[current_index] = 0;
            current_index -= 1;
            direction = -1;
            continue;
        }

        board[current_index] += 1;
        if (check(board, size, current_index)) {
            if (current_index == size - 1) {
                break;
            }
            current_index += 1;
            direction = 1;
        }

        //show(board, size);
    }

    show(board, size);

    return 0;
}
