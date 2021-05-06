#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "tecla.c"

typedef struct BOLA{
	int pos_lin;
	int pos_col;
	int vel;
	clock_t tempo;
}Bola;

typedef struct JOGADOR{
	int pos_col;
	char apar[8];
}Jogador;

int vidas  = 30;
int pontos = 0;
int est_jg = 0; //Estados possíveis: 	0 - Rodando; 1 - Fim do Jogo; 2 - Reiniciando o jogo
		//			3 - Pausa para reiniciar o jogo

int main(){
	/*******************************
	 * Configuração inicial do Jogo 
	 *******************************/
	system("setterm -cursor off");
	initscr();

	//Dados iniciais do jogador
	Jogador jogador; 		  //Criando o ator do Jogo - Jogador
	strcpy(jogador.apar, "-------");  //Dando aparência ao jogador - Uma simples barra
	jogador.pos_col = (int) COLS/2 - strlen(jogador.apar)/2; //Posicionando o jogador no meio da tela

	//Dados iniciais da bola
	Bola bola[5];
	for(int b = 0; b < 5; b++){
		bola[b].pos_lin = LINES + 1;
		bola[b].tempo = clock();
	}

	char ev;

	while(1){
		/**********************************
		 * Regras de Funcionamento do Jogo
		 **********************************/

		//Verificando os diversos estados do jogo
		if(est_jg == 1){	//Finalizando o jogo
			endwin();
			system("setterm -cursor on");
			return 0;
		}else if(est_jg == 2){	//Reiniciando o jogo
			for(int b = 0; b < 5; b++)
				bola[b].pos_lin = LINES + 1;
			vidas  = 30;
			pontos = 0;
			est_jg = 0;
		}else if(est_jg == 3){	//Pausa para reiniciar o jogo
			if(ev == 'q') est_jg = 1;
			if(ev == 'r') est_jg = 2;
		}

		//Verificando o fim do jogo
		if(est_jg == 0)
			if(vidas <= 0){
				est_jg = 3;
			}

		//Verificando se o perdemos vidas
		if(est_jg == 0)
			for(int b = 0; b < 5; b++)
				if(bola[b].pos_lin >= LINES + 1)
					vidas--;
		
		//Verificando a pontuação
		if(est_jg == 0)
			for(int b = 0; b < 5; b++){
				if(bola[b].pos_col >= jogador.pos_col && 
			   		bola[b].pos_col <= jogador.pos_col + strlen(jogador.apar) &&
			   		bola[b].pos_lin == LINES - 1){
					bola[b].pos_lin = LINES + 1;
					pontos +=5;
				}
			}
		
		//Regras e limites para a bola
		if(est_jg == 0){
			for(int b = 0; b < 5; b++){
				//Bola passou da Tela
				if(bola[b].pos_lin > LINES){
					bola[b].pos_lin = 1;
					bola[b].pos_col = (rand()%(COLS - 2)) + 1;
					bola[b].vel = (rand()%300000) + 100000;
				}
				//Mover a bola
				if(bola[b].vel + bola[b].tempo < clock()){
					bola[b].tempo = clock();
					bola[b].pos_lin++;
				}
			}
		}

		//Regras e limites para o Jogador
		if(jogador.pos_col < 0)
			jogador.pos_col=0;
		if(jogador.pos_col > COLS-strlen(jogador.apar))
			jogador.pos_col = COLS-strlen(jogador.apar);
	
		/*****************
		 * Saída Gráfica
		 *****************/
		//Limpando a Tela
		for(int lin=0; lin<LINES; lin++)
			for(int col=0; col<COLS; col++)
				mvwprintw(stdscr, lin, col, " ");

		//Plotando a mensagem de fim de jogo
		if(est_jg == 3)
			mvwprintw(stdscr, LINES / 2, COLS / 2 - 15, "Fim de Jogo 'r' Reiniciar  ou 'q' Sair");

		//Plotando vidas e pontos
		mvwprintw(stdscr, 0, 0, "Vidas: %d  |  Placar: %d", vidas, pontos);

		//Plotando a bola na Tela
		for(int b = 0; b < 5; b++)
			mvwprintw(stdscr, bola[b].pos_lin, bola[b].pos_col, "O");

		//Plotando o Jogador na Tela
		mvwprintw(stdscr, LINES - 1, jogador.pos_col, jogador.apar);
		
		//Atualizando a Tela
		refresh();

		/*************************
		 * Interação com Jogador
		 *************************/
		if(tecla()){ 			//Jogador pressinou uma tecla?
			ev=getchar();
			if(ev == 'q'){		//Foi a tecla de sair?
				est_jg = 1;
			}

			if(ev == 'r' && est_jg == 3)
				est_jg = 2;

			if(ev == 67  && est_jg == 0){		//Foi a seta para a direita?
				jogador.pos_col+=6;
			}

			if(ev == 68  && est_jg == 0){		//Foi a seta para a esquerda?
				jogador.pos_col-=6;
			}
		}
	}
}
