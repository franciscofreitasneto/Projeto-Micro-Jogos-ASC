#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "tecla.c"

int main(){
	//Configuração inicial
	system("setterm -cursor off");
	initscr();
	char texto[]={"Ola Mundo!"};
	int posx = (int) COLS/2 - strlen(texto)/2;
	int posy = (int) LINES/2;
	char ev;

	while(1){
		//Regras de Funcionamento dos Jogos
		if(posy >= LINES)
			posy=0;
		if(posy < 0)
			posy=LINES-1;
		if(posx < 0)
			posx=COLS-strlen(texto);
		if(posx > COLS-strlen(texto))
			posx=0;
	
		//Saída Gráfica
		for(int lin=0; lin<LINES; lin++)
			for(int col=0; col<COLS; col++)
				mvwprintw(stdscr, lin, col, " ");
		mvwprintw(stdscr, posy, posx, texto);
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
			if(ev == 65){
				posy--;
			}
			if(ev == 66){
				posy++;
			}
			if(ev == 67){
				posx++;
			}
			if(ev == 68){
				posx--;
			}
		}
	}
}
