#include <time.h>
#include <allegro.h>
#define BOARD_ROWS 25
#define BOARD_COLS 45
#define MAX_MOVES 30
#define INITIAL_LIVES 5

int process_move(char board[BOARD_ROWS][BOARD_COLS], int r1, int c1, int r2, int c2) {
    int selected_r = -1, selected_c = -1, score;
    if (key[KEY_UP]) {
        selected_r -= 1;
    } else if (key[KEY_DOWN]) {
        selected_r += 1;
    } else if (key[KEY_LEFT]) {
        selected_c -= 1;
    } else if (key[KEY_RIGHT]) {
        selected_c += 1;
    } else if (key[KEY_SPACE]) {
        if (selected_r >= 0 && selected_r < BOARD_ROWS && selected_c >= 0 && selected_c < BOARD_COLS) {
            int r2 = selected_r, c2 = selected_c;
            if (selected_r > 0) {
                int r1 = selected_r - 1, c1 = selected_c;
                int points = process_move(board, r1, c1, r2, c2);
                score += points;
            } else if (selected_r < BOARD_ROWS - 1) {
                int r1 = selected_r + 1, c1 = selected_c;
                int points = process_move(board, r1, c1, r2, c2);
                score += points;
            } else if (selected_c > 0) {
                int r1 = selected_r, c1 = selected_c - 1;
                int points = process_move(board, r1, c1, r2, c2);
                score += points;
            } else if (selected_c < BOARD_COLS - 1) {
                int r1 = selected_r, c1 = selected_c + 1;
                return 0;
            }
        }
    }
}
