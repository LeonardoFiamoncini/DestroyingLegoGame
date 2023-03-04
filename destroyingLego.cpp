/**
* \author Leonardo de Souza Fiamoncini 
* \date 02/02/2022.
* \version 11/02/2022.
**/

#include <iostream>
#include <cmath>
#include <sstream>
#include <vector>

#include "destroyingLego.h"

using namespace std;

/**
* \author Leonardo de Souza Fiamoncini 
* \date 02/02/2022.
* \brief Construtor da classe destroyingLego.
**/
destroyingLego::destroyingLego(){
	/*
	Inicializa os objetos do tipo SDL_Window e SDL_Renderer,
	respectivamente, com o valor NULL.
	*/
	janelaJogo = NULL;
	rendererJogo = NULL;
}

/**
* \author Leonardo de Souza Fiamoncini 
* \date 31/01/2022.
* \brief Destrutor da classe campoJogo.
**/
destroyingLego::~destroyingLego() { }

bool destroyingLego::init(){
	//Inicializa o SDL.
	SDL_Init(SDL_INIT_VIDEO);

	//Cria a janela do jogo Destroying Lego
	janelaJogo = SDL_CreateWindow("Destroying Lego (Projeto - POO)", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
	//Caso ocorra um erro ao criar a janela, é informado.
	if (!janelaJogo){
		cout << "Erro ao criar a janela do jogo!" << SDL_GetError() << endl;
		return false;
	}

	//Cria o renderer para a janela do jogo.
	rendererJogo = SDL_CreateRenderer(janelaJogo, -1, SDL_RENDERER_ACCELERATED);
	//Caso ocorra um erro ao criar o renderer para a janela do jogo, é informado.
	if (!rendererJogo){
		cout << "Erro ao renderizar o jogo!" << SDL_GetError() << endl;
		return false;
	}

	//Inicializa o fps.
	//SDL_GetTicks retorna o número de milissegundos desde a inicialização do SDL.
	ultimoTick = SDL_GetTicks();
	fps = ultimoTick;
	taxaFps = 0;
	countFps = 0;

	return true;
}

/**
* \author Leonardo de Souza Fiamoncini 
* \date 01/02/2022.
* \brief Inicializa os elementos para que o jogo comece a rodar, 
como a prancha, a bola e os blocos, por exemplo.
**/
void destroyingLego::run(){
	prancha1 = new prancha(rendererJogo);
	bola1 = new bola(rendererJogo);
	campo_jogo = new campoJogo(rendererJogo);
	
	objetos.push_back(prancha1);
	objetos.push_back(bola1);
	objetos.push_back(campo_jogo);
	
	//Chama o método novoJogo() para criar uma nova instãncia do jogo.
	novoJogo();

	/*
	Loop de inicialização. 
	evento, do tipo SDL_Event é uma estrutura para diferentes tipos de eventos, 
	ações do mouse ou cliques nas teclas do teclado.
	*/
	SDL_Event evento;
	while (true){
		if (SDL_PollEvent(&evento)){
			if (evento.type == SDL_KEYDOWN){
				//Se clicar no Esc fecha a janela.
				if (evento.key.keysym.sym == SDLK_ESCAPE){	
					break;
				}	
			}
		}

		/*
		Inicializa a taxa de fps e o Delta Time, que nada mais é do que a diferença 
		entre o frame anterior e o atual.
		*/
		unsigned int tickAtual = SDL_GetTicks();
		float dt = (tickAtual - ultimoTick) / 1000.0f;
		if (tickAtual - fps >= DELAY_FPS){
			taxaFps = countFps * (1000.0f / (tickAtual - fps));
			fps = tickAtual;
			countFps = 0;
		} else {
			countFps++;
		}
		ultimoTick = tickAtual;

		//Atualiza e renderiza a janela a cada iteração.
		update(dt);
		render();
	}
	
	/*
	Desabilita o uso das funções, com isso, desalocando a memória 
	que estava sendo utilizada através de alocação dinâmica.
	*/
	delete prancha1;
	delete bola1;
	delete campo_jogo;

	//Destróis os elementos do jogo.
	destruir();

	//Sai do SDL.
	SDL_Quit;
}

/**
* \author Leonardo de Souza Fiamoncini 
* \date 01/02/2022.
* \brief Renderiza constantemente o jogo através do SDL_RenderClear() e 
SDL_RenderPresent().
**/
void destroyingLego::render(){
	SDL_RenderClear(rendererJogo);
	for (size_t i = 0; i < objetos.size(); i++){
		objetos[i]->render();
	}
	SDL_RenderPresent(rendererJogo);
}

/**
* \author Leonardo de Souza Fiamoncini 
* \date 01/02/2022.
* \brief Atualiza constantemente o jogo. Lógica do jogo.
**/
void destroyingLego::update(float dt){
	//Restringe e esconde o mouse na janela.
	SDL_SetRelativeMouseMode(SDL_TRUE); 

	/*
	mouseX guardará a coordenada X atual do mouse
	mouseY guardará a coordenada Y atual do mouse
	*/
	int mouseX, mouseY;
	Uint32 posicaoMouse = SDL_GetMouseState(&mouseX, &mouseY);
	setPranchaX(mouseX - prancha1->largura / 2.0f);

	/*
	Movimenta a prancha de acordo com o mouse e atira a bola 
	quando clica com o botão esquerdo do mouse.
	*/
	if (posicaoMouse & SDL_BUTTON(1)){
		// Atira a bola para cima apenas se estiver com ela posicionada sobre a prancha.
		if (bolaNaPrancha){
			bolaNaPrancha = false;
			bola1->movimentoBola(1, 1);
		}
	}

	if (bolaNaPrancha){
		redefinirBola();
	}

	//Checa as colisões.
	colisaoBolaBorda();
	colisaoBolaPrancha();
	colisaoBolaBloco();

	//Começa um novo jogo se não houver nenhum bloco restante.
	if (getBlocos() == 0){
		novoJogo();
	}
	
	/*
	Passa o valor do Delta Time para o nível, para a prancha e para a bola,
	caso a bola não esteja colada na prancha.
	*/ 
	campo_jogo->update(dt);
	prancha1->update(dt);

	if (!bolaNaPrancha){
		bola1->update(dt);
	}
}

/**
* \author Leonardo de Souza Fiamoncini 
* \date 02/02/2022.
* \brief Destrói a janela, seu renderer e a textura do jogo.
**/
void destroyingLego::destruir(){
	SDL_DestroyWindow(janelaJogo);
	SDL_DestroyRenderer(rendererJogo);
	SDL_DestroyTexture(texturaJogo);
}

/**
* \author Leonardo de Souza Fiamoncini 
* \date 02/02/2022.
* \brief Cria um novo nível redefinindo a posição da bola 
logo acima da prancha.
**/
void destroyingLego::novoJogo(){
	campo_jogo->novoNivel();
	redefinirBola();
}


/**
* \author Leonardo de Souza Fiamoncini 
* \date 02/02/2022.
* \brief Retorna o número de blocos atualmente no nível.
**/
int destroyingLego::getBlocos(){
	int countBloco = 0;
	for (int i = 0; i < LARGURA_CAMPO_JOGO; i++){
		for (int j = 0; j < ALTURA_CAMPO_JOGO; j++){
			bloco brick = campo_jogo->blocos[i][j];
			if (brick.estado){
				countBloco++;
			}
		}
	}
	return countBloco;
}

/**
* \author Leonardo de Souza Fiamoncini 
* \date 02/02/2022.
* \brief Redefine a bola, posicionando-a logo acima da prancha.
**/
void destroyingLego::redefinirBola(){
	bolaNaPrancha = true;
	bola1->posicaoX = prancha1->posicaoX + prancha1->largura / 2 - bola1->largura / 2;
	bola1->posicaoY = prancha1->posicaoY - bola1->altura;
}

/**
* \author Leonardo de Souza Fiamoncini 
* \date 02/02/2022.
* \brief Configura a posição da prancha de acordo com a 
coordenada X atual do mouse.
* \param x Coordenada X atual do mouse.
**/
void destroyingLego::setPranchaX(float x){
	float novoX;
	if (x + prancha1->largura > campo_jogo->posicaoX + campo_jogo->largura){
		//Limites inferiores.
		novoX = campo_jogo->posicaoX + campo_jogo->largura - prancha1->largura;
	} else if (x < campo_jogo->posicaoX){
		//Limites superiores.
		novoX = campo_jogo->posicaoX;
	} else {
		novoX = x;
	}
	prancha1->posicaoX = novoX;
}

/**
* \author Leonardo de Souza Fiamoncini 
* \date 02/02/2022.
* \brief Cálculo da reflexão da bola na prancha.
* \param hitX Ponto X que a bola bateu na prancha.
**/
float destroyingLego::reflexaoBolaPrancha(float hitX){
	if (hitX < 0){
		hitX = 0;
	} else if (hitX > prancha1->largura){
		hitX = prancha1->largura;
	}

	/* 
	Se a bola atinge do centro até a borda esquerda da prancha, ela é refletida para a esquerda.
	Se a bola atinge do centro até a borda direita da prancha, ela é refletida para a direita.
	*/
	hitX -= prancha1->largura / 2.0f;

	//Ajusta a reflexão baseada em quão longe a bola atinge do centro da prancha.
	return 2.0f * (hitX / (prancha1->largura / 2.0f));
}

/**
* \author Leonardo de Souza Fiamoncini 
* \date 02/02/2022.
* \brief Calcula a reflexão baseada na colisão da bola com o bloco.
* \param direcaoIndex .
**/
void destroyingLego::reflexaoBolaBloco(int direcaoIndex){
	//Direção da reflexão da bola com o bloco.
	int movX = 1;
	int movY = 1;

	if (bola1->direcaoX > 0){
		if (bola1->direcaoY > 0){
			if (direcaoIndex == 0 || direcaoIndex == 3){
				movX = -1;
			} else {
				movY = -1;
			}
		}
		else if (bola1->direcaoY < 0){
			if (direcaoIndex == 0 || direcaoIndex == 1){
				movX = -1;
			} else {
				movY = -1;
			}
		}
	} else if (bola1->direcaoX < 0){
		if (bola1->direcaoY > 0){
			if (direcaoIndex == 2 || direcaoIndex == 3){
				movX = -1;
			} else {
				movY = -1;
			}
		} else if (bola1->direcaoY < 0){
			if (direcaoIndex == 1 || direcaoIndex == 2){
				movX = -1;
			} else {
				movY = -1;
			}
		}
	}

	//Direção da reflexão é o produto da direção antiga com a nova.
	bola1->movimentoBola(movX * bola1->direcaoX, movY * bola1->direcaoY);
}

/**
* \author Leonardo de Souza Fiamoncini 
* \date 02/02/2022.
* \brief Checa a colisão da bola com as bordas. 
Reflete a bola se colidir com as bordas da janela.
**/
void destroyingLego::colisaoBolaBorda(){
	if (bola1->posicaoY < campo_jogo->posicaoY){
		bola1->posicaoY = campo_jogo->posicaoY;
		bola1->direcaoY *= -1;
	} else if (bola1->posicaoY + bola1->altura > campo_jogo->posicaoY + campo_jogo->altura){
		//Quando a bola atinge a borda inferior, novoJogo() é chamado.
		novoJogo();
	}

	//Colisão dos lados.
	if (bola1->posicaoX <= campo_jogo->posicaoX){
		//Lado esquerdo.
		bola1->posicaoX = campo_jogo->posicaoX;
		bola1->direcaoX *= -1;
	} else if (bola1->posicaoX + bola1->largura >= campo_jogo->posicaoX + campo_jogo->largura){
		//Lado direito.
		bola1->posicaoX = campo_jogo->posicaoX + campo_jogo->largura - bola1->largura;
		bola1->direcaoX *= -1;
	}
}

/**
* \author Leonardo de Souza Fiamoncini 
* \date 03/02/2022.
* \brief Checa a colisão da bola com a prancha e chama o 
método reflexaoBolaPrancha().
**/
void destroyingLego::colisaoBolaPrancha(){
	
	//Pega a coordenada X do centro da bola.
	float bolaCentroX = bola1->posicaoX + bola1->largura / 2.0f;

	//Checa se a bola colidiu com a prancha.
	if (bola1->colisao(prancha1)){
		bola1->posicaoY = prancha1->posicaoY - bola1->altura;
		bola1->movimentoBola(reflexaoBolaPrancha(bolaCentroX - prancha1->posicaoX), -1);
	}
}

/**
* \author Leonardo de Souza Fiamoncini 
* \date 03/02/2022.
* \brief Checa a colisão da bola com o bloco.  
**/
void destroyingLego::colisaoBolaBloco(){
	for (int i = 0; i < LARGURA_CAMPO_JOGO; i++){
		for (int j = 0; j < ALTURA_CAMPO_JOGO; j++){
			bloco brick = campo_jogo->blocos[i][j];
			//Checa se o bloco está presente.
			if (brick.estado){
				//Pega a posição do bloco.
				float blocoX = campo_jogo->blocoPosicaoX + campo_jogo->posicaoX + i * LARGURA_BLOCO;
				float blocoY = campo_jogo->blocoPosicaoY + campo_jogo->posicaoY + j * ALTURA_BLOCO;

				//Checa se a bola colidiu com o bloco.
				float w = (bola1->largura + LARGURA_BLOCO) / 2.0f;
				float h = (bola1->altura + ALTURA_BLOCO) / 2.0f;
				float dx = (bola1->posicaoX + bola1->largura / 2.0f) - (blocoX + LARGURA_BLOCO / 2.0f);
				float dy = (bola1->posicaoY + bola1->altura / 2.0f) - (blocoY + ALTURA_BLOCO / 2.0f);

				if (fabs(dx) <= w && fabs(dy) <= h){
					campo_jogo->blocos[i][j].estado = false;

					float wy = w * dy;
					float hx = h * dx;

					if (wy > hx){
						if (wy > -hx){
							//Inferior.
							reflexaoBolaBloco(3);
						} else {
							//Esquerda
							reflexaoBolaBloco(0);
						}
					} else {
						if (wy > -hx){
							//Direita
							reflexaoBolaBloco(2);
						} else{
							//Topo.
							reflexaoBolaBloco(1);
						}
					}
					return;
				}
			}
		}
	}
}
