#include "gfx.h"
#include <stdio.h>  /* printf */
#include <unistd.h> /* sleep  */
#include <math.h>

/*Desenha um triangulo equilatero com uma das ponta apontando para baixo.
Parametros:
x - Posicao X da ponta esquerda
y - Posição Y da ponta esquerda
size - Tamanho do lado

Retorno: Nenhum
*/
void triangle(unsigned int x, unsigned int y, unsigned int size, double h){	
	gfx_line(x, y, x + size, y);
	gfx_line(x, y, x + (size / 2), y + h);
	gfx_line(x + size, y, x + (size / 2), y + h);
}

/*Funçao recursiva que desenha o Triangulo de Sierpinski
Parametros:
x - Posição X da ponta esquerda
y - Posição Y da ponta esquerda
size - Tamanho do lado
amount - Ponteiro para a somatoria da quantidade de triangulos

Retorno: Nenhum
*/
void sierpinski(unsigned int x, unsigned int y, unsigned int size, unsigned int* amount){
	double h;
	if(size > 5){ /*Se o novo triangulo não for muito pequeno*/
		h = (size * sqrt(3)) / 2;
	
		sierpinski(x + 3 * (size / 4), y + (h / 2), size / 2, amount);/*Desenha o triangulo da direita*/
		sierpinski(x - (size / 4), y + (h / 2), size / 2, amount);/*Desenha o triangulo da Esquerda*/
		sierpinski(x + (size / 4), y - (((size / 2) * sqrt(3)) / 2), size / 2, amount);/*Desenha o triangulo de cima*/
		
		triangle(x, y, size, h); /*Desenha o triangulo*/
		*amount += 1; /*Incrementa a quantidade de triangulos*/
	}
}
		
int main(int argc, char* argv[]){
	unsigned int size;/*Tamanho do triangulo*/
	unsigned int default_size;/*Tamanho padrão do triangulo*/
	unsigned int amount; /*Quantidade de triangulos*/
	int quit; /*Verifica se o programa deve ser encerrado*/
	char* msg; /*Auxiliar para colocar as informaçoes na tela*/
	SDL_Event event; /*guarda um evento ocorrido*/
	
	msg = (char*) malloc(sizeof(char) * 30); /*Aloca memoria para a string auxiliar*/
	if(!msg){/*Verifica se foi alocado*/
		printf("Erro ao alocar memoria.\n");
		exit (0);
	}

	amount = 0;/*Inicializa o contador de triangulos*/
	default_size = 100;/*Define o tamanho padrão do triangulo para caso o usuario não tenha definido*/

	if(argc != 1){/*Verifica se foi passado algum argumento na chamada do programa*/
		if(atoi(argv[1]) != 0){/*Se o argumento for um numero ele sera o tamanho padrão do triangulo*/
			default_size = atoi(argv[1]);
		}
	}
	
	size = default_size;/*Define o tamanho com o tamanho padrão*/
	
	gfx_init("Sierpinski");/*Seta o nome da janela*/
	
	sierpinski((gfx_get_width() / 2) - (size / 2), gfx_get_height() - (int)((size * 1.732050808) / 2), size, &amount);/*Desenha o triangulo com o tamanho incial*/
	sprintf(msg, "Lado: %d     Quantidade: %u", size, amount);
	gfx_text(10, 10, msg);/*Imprime as informacões do triangulo*/
	gfx_text(10, 30, "Atalhos: Zoom(i)n - Zoom(o)ut - (C)lear - (esc)ape");/*Imprime o menu*/
	gfx_paint();
	
	while(!quit){/*Loop principal*/
		while(SDL_PollEvent(&event)){/*Verifica se ocorreu algum evento*/
			switch(event.type){/*Seleciona o tipo de evento*/
				case SDL_QUIT:/*Clique no botão de fechar*/
					quit = 1;/*sair do loop principal*/
					break;
				case SDL_KEYDOWN:/*Tecla pressionada*/
					while(event.key.state == SDL_PRESSED && quit == 0){/*Tecla continua pressionada e não é o ESC*/
						switch (event.key.keysym.sym){/*Seleciona a tecla*/
							case SDLK_i:/*Caso seja 'i' os triangulos aumentam*/
								size += 5;/*Incrementa o tamanho do triangulo*/
								gfx_clear();/*Limpa a tela*/
								amount = 0;/*Zera o contador de triangulos*/
								sierpinski((gfx_get_width() / 2) - (size / 2), gfx_get_height() - (int)((size * 1.732050808) / 2), size, &amount);/*Desenha o triangulo de Sierpinski*/
								sprintf(msg, "Lado: %d     Quantidade: %u", size, amount);
								gfx_text(10, 10, msg);/*Imprime as informacões do triangulo*/
								gfx_text(10, 30, "Atalhos: Zoom(i)n - Zoom(o)ut - (C)lear - (esc)ape");/*Imprime o menu*/
								break;

							case SDLK_o:/*Caso seja 'o' os triangulos diminuem*/
								size -= 5;
								gfx_clear();
								amount = 0;
								sierpinski((gfx_get_width() / 2) - (size / 2), gfx_get_height() - (int)((size * 1.732050808) / 2), size, &amount);
								sprintf(msg, "Lado: %d     Quantidade: %u", size, amount);
								gfx_text(10, 10, msg);/*Imprime as informacões do triangulo*/
								gfx_text(10, 30, "Atalhos: Zoom(i)n - Zoom(o)ut - (C)lear - (esc)ape");/*Imprime o menu*/
								break;

							case SDLK_c: /*Caso seja 'c' o triangulo é resetado*/
								size = default_size;/*Define o tamanho com o tamanho padrão*/
								gfx_clear();/*Limpa tela*/
								amount = 0;/*Zera o contador de triangulos*/
								sierpinski((gfx_get_width() / 2) - (size / 2), gfx_get_height() - (int)((size * 1.732050808) / 2), size, &amount);/*Desenha o triangulo com o tamanho padrão*/
								sprintf(msg, "Lado: %d     Quantidade: %u", size, amount);
								gfx_text(10, 10, msg);/*Imprime as informacões do triangulo*/
								gfx_text(10, 30, "Atalhos: Zoom(i)n - Zoom(o)ut - (C)lear - (esc)ape");/*Imprime o menu*/
								break;

							case SDLK_ESCAPE: /*Caso seja 'ESC' encerra o programa*/
								quit = 1;
								break;
							
							default:/*Outra tecla nada é feito*/
								break;
						}
						gfx_refresh();/*Atualiza a tela*/
						usleep(120000);/*Delay para ler um novo evento*/
						SDL_PollEvent(&event);/*Le um novo evento*/
					}
					break;
			}
		}
	}

	gfx_quit();/*Fecha a janela*/
	free(msg);/*Libera a memoria alocada*/
	return 0;
}

