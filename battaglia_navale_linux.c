#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 4

#define COLPITO 2
#define ACQUA 3
#define BARCA 1
#define VUOTO 0

void azzera(int tabella[N][N]) {
	int i,j;
	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			tabella[i][j]=0;
}

void printa(int tabella[N][N]) {
	char cella;
	int i, j;
	printf("  1 2 3 4\n ---------\n");
	for (i = 0; i < N; i++) {
		printf("%d", i + 1);
		for (j = 0; j < N; j++) {
			if (tabella[i][j] == COLPITO)
				cella = 'x';
			else if (tabella[i][j] == ACQUA)
				cella = 'o';
			else
				cella = ' ';
			printf("|%c", cella);
		}
		printf("|\n ---------\n");
	}
}

void printaInit(int tabella[N][N]) {
	char cella;
	int i, j;
	printf("  1 2 3 4\n ---------\n");
	for (i = 0; i < N; i++) {
		printf("%d", i + 1);
		for (j = 0; j < N; j++) {
			if (tabella[i][j] == COLPITO || tabella[i][j] == BARCA)
				cella = 'x';
			else
				cella = ' ';
			printf("|%c", cella);
		}
		printf("|\n ---------\n");
	}
}

int inizializza(int tabella[N][N]) {
	int navi = 0,x,y;
	do {
		system("clear");
		printaInit(tabella);
		printf("Dove piazzo la nave (x,y) (0,0 per uscire) ? ");
		scanf("%d,%d", &x, &y);
		if (x > 0 && x <= 4 && y > 0 && y <= 4 && tabella[x-1][y-1]==VUOTO) {
			tabella[x - 1][y - 1] = BARCA;
			navi++;
		} else if (x == 0 && y == 0)
			system("clear");
		else
			printf("No dai sul serio.\n");
	} while (x != 0 || y != 0);
	return navi;
}

int isThere(int matrice[N][N], int numero) {
	int i, j;
	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			if (matrice[i][j] = numero)
				return 1;
	return 0;
}


void status(int tabella[N][N], int attempt) {
	printf("Tentativi effettuati: %d\n\n", attempt);
	printa(tabella);
}


//restituisce 0 se già usata, 1 se colpito, 3 se buco nell'acqua
int battaglia(int tabella[N][N], int x, int y) {
	if (tabella[x][y] == VUOTO) {
		tabella[x][y] = ACQUA;
		return ACQUA;
	} else if (tabella[x][y] == BARCA) {
		tabella[x][y] = COLPITO;
		return 1;
	} else
		return 0;
}

//restituisce l'esito di "battaglia" o 4 se fuori coordinate
int input(int tabella[N][N], int *tentativi, int *navi) {
	int x, y, esito;
	status(tabella, *tentativi);
	printf("\nInserisci le coordinate dove sparare (x,y): ");
	scanf("%d,%d", &x, &y);
	if (x > 0 && x <= 4 && y > 0 && y <= 4) {
		esito = battaglia(tabella, x-1, y-1);
		(*tentativi)++;
		if (esito == 1)
			(*navi)--;
		return esito;
	} else
		return 4;
}

int main() {
	int tentativi=0,tabella[N][N],navi,esito;
	azzera(tabella);
	
	navi=inizializza(tabella);

	esito = input(tabella, &tentativi, &navi);

	do {
		system("clear");
		if (esito == 0)
			printf("Gia' colpito li' baby!\n\n");
		else if (esito == 1)
			printf("Colpito!\n\n");
		else if (esito == 3)
			printf("Buco nell'acqua!\n\n");
		else if (esito == 4)
			printf("Inseriscile bene le coordinate\n\n");
		else;
		esito = input(tabella, &tentativi, &navi);
	} while (tentativi<10&&navi>0);

	system("clear");
	status(tabella, tentativi);
	printf("\nBene, gioco finito.\n");
	if (navi <= 0)
		printf("Bravissimo, hai vinto.\n\n");
	else
		printf("Hai perzo, fine tentativi.\n\n");
}
