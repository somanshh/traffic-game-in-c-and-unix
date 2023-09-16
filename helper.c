#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>
#include "headers.h"

//this helper file consists of all the helper funcitons like create map , print map , get_user_input etc.

void create_map(int row, int col, char **map)
{
    // Initialize the map
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if ((j == 0 || j == col - 1))
            {
                map[i][j] = MAP_BORDER;
            }
            else if (i % 2 != 0)
            {
                map[i][j] = ROAD;
            }
            else
            {
                map[i][j] = ' ';
            }
        }
    }
}

void print_map(int row, int col, char **map)
{
    // for clearing the terminal
    system("clear");
    
    // Print the map borders
    for (int i = 0; i < col; i++)
    {
        printf("%c", MAP_BORDER);
    }
    printf("\n");

    // Print the map contents
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if( j == 0 || j == col-1 ) printf("%c" , MAP_BORDER); 
            else printf("%c", map[i][j]);
        }
        printf("\n");
    }

    // Print the map borders
    for (int i = 0; i < col; i++)
    {
        printf("%c", MAP_BORDER);
    }
    printf("\n");

    printf("Press w to move up \n");
    printf("Press s to move down \n");
    printf("Press a to move left \n");
    printf("Press d to move right \n");
}

char get_user_input() {
    char user_input;

    // Store the current terminal attributes
    struct termios old_attributes;
    tcgetattr(STDIN_FILENO, &old_attributes);

    // Put the terminal into raw mode
    struct termios new_attributes = old_attributes;
    new_attributes.c_lflag &= ~(ICANON | ECHO);
    new_attributes.c_cc[VMIN] = 1;
    new_attributes.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &new_attributes);

    // Get the user's input
    read(STDIN_FILENO, &user_input, 1);

    // Restore the terminal attributes
    tcsetattr(STDIN_FILENO, TCSANOW, &old_attributes);

    return user_input;
}
