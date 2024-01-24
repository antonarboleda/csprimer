#include <stdio.h>
#include <unistd.h>
#include <curses.h>

int main()
{
    // set terminal mode to cbreak;
    initscr();
    cbreak();

    char c;
    while (1)
    {
        c = getchar();
        if (c >= '1' && c <= '9')
        {
            int beeps = c - '0';
            while (beeps--)
            {
                printf("\a");
                fflush(stdout);
                sleep(1);
            }
        }
    }
    return 0;
}