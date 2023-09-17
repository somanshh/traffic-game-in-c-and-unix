#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "headers.h"


int isValidInput(char user_input)
{
    if( user_input == 'w' || user_input == 's' || user_input == 'a' || user_input == 'd' ) 
    	return 1;
    else
    {
    	printf("Please enter a valid input to continue further\n");
    	return 0;
    }
}

void move_player(int row, int col, char **map, int *player_row, int *player_col , int *thePlayerHasHitByCar , char user_input )
{

    switch (user_input)
    {
    case 'w':
        if (*player_row > 0 && map[*player_row - 1][*player_col] != MAP_BORDER)
        {
            if (*player_row % 2 != 0)
                map[*player_row][*player_col] = ROAD;
            else
                map[*player_row][*player_col] = ' ';
            (*player_row)--;
        }
        break;
    case 's':
        if (*player_row < row - 1 && map[*player_row + 1][*player_col] != MAP_BORDER)
        {
            if (*player_row % 2 != 0)
                map[*player_row][*player_col] = ROAD;
            else
                map[*player_row][*player_col] = ' ';
            (*player_row)++;
        }
        break;
    case 'a':
        if (*player_col > 0 && map[*player_row][*player_col - 1] != MAP_BORDER)
        {
            if (*player_row % 2 != 0)
                map[*player_row][*player_col] = ROAD;
            else
                map[*player_row][*player_col] = ' ';
            (*player_col)--;
        }
        break;
    case 'd':
        if (*player_col < col - 1 && map[*player_row][*player_col + 1] != MAP_BORDER)
        {
            if (*player_row % 2 != 0)
                map[*player_row][*player_col] = ROAD;
            else
                map[*player_row][*player_col] = ' ';
            (*player_col)++;
        }
        break;
    default:
    	printf("Please enter a valid input to continue further\n");
        break;
    }

    
    if( map[*player_row][*player_col] == '<' || map[*player_row][*player_col] == '>' ) 
    {
    
        *thePlayerHasHitByCar = 1;
    } 

    // Update the map with the new position of the player
//    move_cars(row,col,map);
    map[*player_row][*player_col] = PLAYER;
   
}

void move_cars(int row, int col, char **map)
{
    // Initialize the random number generator with the current time
    srand(time(NULL));

    // Iterate over each road on the map
    for (int i = 1; i < row - 1; i += 2)
    {
        // Get a random starting position for the car
        int new_rand_col = rand() % (col-2) + 1;
        
        while( map[i][new_rand_col] == PLAYER ) new_rand_col = rand() % (col-2) + 1;

        int curr_posOf_car = 0;
        char curr_dirOf_car ;

        for (int j = 1; j < col; j++)
        {
            if (map[i][j] == '<')
            {
                curr_dirOf_car = '<';
                map[i][j] = ROAD;
                curr_posOf_car = j;
                new_rand_col = (rand() % j)+1;
            }
            else if (map[i][j] == '>')
            {
                curr_dirOf_car = '>';
                map[i][j] = ROAD;
                curr_posOf_car = j;
                new_rand_col = (rand() % (j)) + (j+1);
                while(new_rand_col >= col-1) new_rand_col = (rand()%j)+(j+1);
            }
        }

        if (new_rand_col == 1)
        {
            map[i][curr_posOf_car] = ROAD;
            map[i][new_rand_col] = '>';
            curr_dirOf_car = '>';
            continue;
        }

        else if (new_rand_col == col - 2 )
        {
            map[i][curr_posOf_car] = ROAD;
            map[i][new_rand_col] = '<';
            curr_dirOf_car = '<';
            continue;
        }

        if( curr_dirOf_car == '>' ) map[i][new_rand_col] = '>';

        else if( curr_dirOf_car == '<' ) map[i][new_rand_col] = '<';
        
    }
}
