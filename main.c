#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "headers.h"
#include <unistd.h>

int main(int argc, char *argv[])
{
    int row, col;
    char **map;

    // Check the number of command-line arguments
    if (argc != 3)
    {
        printf("Usage: %s <row> <col>\n", argv[0]);
        return 1;
    }

    // Get the row and column sizes from the command-line arguments
    row = atoi(argv[1]);
    col = atoi(argv[2]);

    col += 2;

    // Check the row and column sizes
    if (row < 3 || col < 5 || row % 2 == 0 )
    {
        printf("The <ROW> and <COLUMN> sizes must be at least 3 and 5, respectively. And <ROW> needs to be an ODD NUMBER \n");
        return 1;
    }

    // Create the map
    map = (char **)malloc(sizeof(char *) * row);
	for (int i = 0; i < row; i++)
	{
	    map[i] = (char *)malloc(sizeof(char) * (col + 2));
        }

    create_map(row, col, map);

    // Initialize the cars
    for (int i = 1; i < row; i += 2)
    {
        // Get the random row and column for the car
        int car_row = i;
        int car_col = rand() % col+2;

        // Set the car's direction
        char car_dir = '<';
        if (rand() % 2 == 0)
        {
            car_dir = '>';
        }

        // Place the car on the map
        map[car_row][car_col] = car_dir;
    }

    int player_row = 0;
    int player_col = 1;

    // to finish the game if the player is hitted by the car
    int thePlayerHasHitByCar = 0;
    int memoryIsFreed = 0;

    // Place the player and goal on the map
    map[0][1] = PLAYER;
    map[row - 1][col - 2] = GOAL;

    // Start the game loop
    while (1)
    {
        // Print the map
        print_map(row, col, map);
        
        // break the current loop if the user is hit by the car
        if( thePlayerHasHitByCar )
        {
            printf("You Lose!\n");
            break;
        }

        // Check if the player has reached the goal
        if (map[row - 1][col - 2] == PLAYER)
        {
            printf("You win!\n");
            break;
        }
        
        char input = get_user_input();
        while(isValidInput(input) != 1) input = get_user_input(); 
        
        // Move the cars
        move_cars(row, col, map);

        // Move the player
        move_player(row, col, map, &player_row, &player_col , &thePlayerHasHitByCar , input);

       

    }
	
    // Free the memory allocated for the map
    if( !memoryIsFreed ){
    	for (int i = 0; i < row; i++)
    	{	
	    	memoryIsFreed = 1;
		free(map[i]);
    	}
    	free(map);
    }

    return 0;
}

