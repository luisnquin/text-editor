#include "stdbool.h"
#include "curses.h"
#include "stdlib.h"
#include "string.h"
#include "signal.h"

#include "ascii.h"

#define DEBUG_FILE_NAME "build/keys.debug"

const int TEXT_CHUNK_SIZE = 10;

void signal_handler()
{
    endwin();
    printf("nao~ nao~\n");
    exit(0);
}

int main(int argc, char const *argv[])
{
    signal(SIGTERM, signal_handler);
    signal(SIGINT, signal_handler);

    initscr();
    noecho();
    keypad(stdscr, true);

    int text_cap = TEXT_CHUNK_SIZE;
    int text_length = 0;

    char *text = malloc(text_cap * sizeof(char));

    FILE *debug_file = fopen(DEBUG_FILE_NAME, "a");

    for (int i = 0; i < text_cap; i++)
    {
        if (i + 1 == text_cap)
        {
            text_cap += TEXT_CHUNK_SIZE;

            text = realloc(text, text_cap * sizeof(char));
            if (text == NULL)
            {
                fprintf(stderr, "Failed to allocate memory :(\n");
                exit(EXIT_FAILURE);
            }
        }

        wclear(stdscr);
        printw("[%d/%d] %s", text_length, text_cap, text);

        int c = getch();

        fprintf(debug_file, "Char: %c | Dec: %d\n", c, c);
        fflush(debug_file);

        switch (c)
        {
        case DELETE_KEY:
            int prev = i - 1;

            if (prev >= 0)
            {
                text[prev] = NULL_KEY;
                i -= 2;
                text_length--;
            }

            break;

        default:
            text[i] = (char)c;
            move(0, i);
            text_length++;
            break;
        }
    }

    fclose(debug_file);
    free(text);

    return 0;
}