/*************************************************************
 * Introdução ao Curso de Micro Jogos em ASC e C 
 * Prof. Kiko
 * Código Olá Mundo!
 *************************************************************/

#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "tecla.c"

int main(){
	//Preparação e configurações iniciais do jogo
	system("setterm -cursor off");
	initscr();
	char texto[]={"Ola Mundo"};
	int posx = (int) COLS/2 - strlen(texto)/2;
	int posy = (int) LINES/2;
	int intervalo = 1000000;
	clock_t relogio = clock();
	char ev;

	while(1){
		//Regras do funcionamento dos Jogos
		if(intervalo+relogio < clock()){
			relogio = clock();
			posy++;
			if(posy > LINES)
				posy = 0;
		}

		//Parte Gráfica do Jogo
		for(int lin = 0; lin < LINES; lin++)
			for(int col = 0; col < COLS; col++)
					mvwprintw(stdscr, lin, col, " ");
		mvwprintw(stdscr, posy, posx, texto);

		refresh();
		
		//Interação com o usuário
		if(tecla()){
			ev=getchar();
			if(ev == 'q'){
				endwin();
				system("setterm -cursor on");
				return 0;
			}
		}
			
	}
}
