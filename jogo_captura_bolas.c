#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "tecla.c"

typedef struct BOLA{
	int pos_lin;
	int pos_col;
	int vel;
}Bola;

typedef struct JOGADOR{
	int pos_col;
	char apar[8];
}Jogador;

int main(){
	//Configuração inicial
	system("setterm -cursor off");
	initscr();
	Jogador jogador;
	strcpy(jogador.apar, "-------");
	jogador.pos_col = (int) COLS/2 - strlen(jogador.apar)/2;
	char ev;

	while(1){
		//Regras de Funcionamento dos Jogos
		if(jogador.pos_col < 0)
			jogador.pos_col=0;
		if(jogador.pos_col > COLS-strlen(jogador.apar))
			jogador.pos_col = COLS-strlen(jogador.apar);
	
		//Saída Gráfica
		for(int lin=0; lin<LINES; lin++)
			for(int col=0; col<COLS; col++)
				mvwprintw(stdscr, lin, col, " ");
		mvwprintw(stdscr, LINES - 1, jogador.pos_col, jogador.apar);
		///mvwprintw(stdscr, 0, 0, "%d", ev);
		refresh();

		//Interação com Jogador
		if(tecla()){
			ev=getchar();
			if(ev == 'q'){
				endwin();
				system("setterm -cursor on");
				return 0;
			}
			if(ev == 67){
				jogador.pos_col++;
			}
			if(ev == 68){
				jogador.pos_col--;
			}
		}
	}
}
