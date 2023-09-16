#ifndef HEADER_H
#define HEADER_H

#define MAP_BORDER '*'
#define PLAYER 'P'
#define GOAL 'G'
#define ROAD '.'
#define CAR '<'

void create_map(int row, int col, char **map);
void print_map(int row, int col, char **map);
char get_user_input();
int isValidInput(char input);
void move_player(int row, int col, char **map, int *player_row, int *player_col, int *thePlayerHasHitByCar, char user_input);
void move_cars(int row, int col, char **map);

#endif
