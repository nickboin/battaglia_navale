#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 4

#define HIT 2
#define WATER 3
#define SHIP 1
#define EMPTY 0

void clears(int table[N][N]) {
	int i,j;
	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			table[i][j]=0;
}

void print(int table[N][N]) {
	char cell;
	int i, j;
	printf("  1 2 3 4\n ---------\n");
	for (i = 0; i < N; i++) {
		printf("%d", i + 1);
		for (j = 0; j < N; j++) {
			if (table[i][j] == HIT)
				cell = 'x';
			else if (table[i][j] == WATER)
				cell = 'o';
			else
				cell = ' ';
			printf("|%c", cell);
		}
		printf("|\n ---------\n");
	}
}

void printInit(int table[N][N]) {
	char cell;
	int i, j;
	printf("  1 2 3 4\n ---------\n");
	for (i = 0; i < N; i++) {
		printf("%d", i + 1);
		for (j = 0; j < N; j++) {
			if (table[i][j] == HIT || table[i][j] == SHIP)
				cell = 'x';
			else
				cell = ' ';
			printf("|%c", cell);
		}
		printf("|\n ---------\n");
	}
}

int init(int table[N][N]) {
	int ships = 0,x,y;
	do {
		system("clear");
		printInit(table);
		printf("Where i have to put the ship overbearingly (x,y) (0,0 to exit) ? ");
		scanf("%d,%d", &x, &y);
		if (x > 0 && x <= 4 && y > 0 && y <= 4 && table[x-1][y-1]==EMPTY) {
			table[x - 1][y - 1] = SHIP;
			ships++;
		} else if (x == 0 && y == 0)
			system("clear");
		else
			printf("No ok, seriously.\n");
	} while (x != 0 || y != 0);
	return ships;
}

int isThere(int matrix[N][N], int num) {
	int i, j;
	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			if (matrix[i][j] = num)
				return 1;
	return 0;
}


void status(int table[N][N], int attempt) {
	printf("Performed attempts: %d\n\n", attempt);
	print(table);
}


//return 0 if already used, 1 if hit, 3 if hole in the water
int fight(int table[N][N], int x, int y) {
	if (table[x][y] == EMPTY) {
		table[x][y] = WATER;
		return WATER;
	} else if (table[x][y] == SHIP) {
		table[x][y] = HIT;
		return 1;
	} else
		return 0;
}

//return the result of "fight" or 4 of out of coordinates
int input(int table[N][N], int *attempts, int *ships) {
	int x, y, result;
	status(table, *attempts);
	printf("\nEnter coordinates where shoot (x,y): ");
	scanf("%d,%d", &x, &y);
	if (x > 0 && x <= 4 && y > 0 && y <= 4) {
		result = fight(table, x-1, y-1);
		(*attempts)++;
		if (result == 1)
			(*ships)--;
		return result;
	} else
		return 4;
}

int main() {
	int attempts=0,table[N][N],ships,result;
	clears(table);
	
	ships=init(table);

	result = input(table, &attempts, &ships);

	do {
		system("clear");
		if (result == 0)
			printf("Already hit there, baby!\n\n");
		else if (result == 1)
			printf("Hit!\n\n");
		else if (result == 3)
			printf("Hole in the water!\n\n");
		else if (result == 4)
			printf("Enter the coordinates correctly\n\n");
		else;
		result = input(table, &attempts, &ships);
	} while (attempts<10&&ships>0);

	system("clear");
	status(table, attempts);
	printf("\nGood, game over.\n");
	if (ships <= 0)
		printf("Very good, you win.\n\n");
	else
		printf("You lose, end of attempts.\n\n");
}