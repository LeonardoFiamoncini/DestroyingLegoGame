/**
* \author Leonardo de Souza Fiamoncini 
* \date 31/01/2022.
* \version 09/02/2022.
**/

#include <iostream>

#include "campoJogo.h"

using namespace std;

/**
* \author Leonardo de Souza Fiamoncini 
* \date 31/01/2022.
* \brief Construtor da classe campoJogo.
* \param renderer Guarda o renderer em questão, que contém 
os estados de atributos da janela.
**/
campoJogo::campoJogo(SDL_Renderer* renderer) : objsJogo(renderer){
	/*
	Cria uma superfície e insere o arquivo bloco.png, carregado
	através da função IMG_Load(), nela. 
	*/
	SDL_Surface* surface = IMG_Load("bloco.png");
	/*
	Atribui uma textura para o bloco.
	pam 1 Renderer da janela em questão.
	pam 2 Superfície utilizada que irá criar a textura. 
	*/
	texturaBloco = SDL_CreateTextureFromSurface(renderer, surface);
	
	//Libera os recursos RGB usados pela surface criada anteriormente.
	SDL_FreeSurface(surface);

	/*
	Atribue um tamanho e as coordenadas de onde o campo 
	será posicionado na tela.
	*/
	posicaoX = 16;
	posicaoY = 16;
	largura = 768;
	altura = 768;
}

/**
* \author Leonardo de Souza Fiamoncini 
* \date 31/01/2022.
* \brief Destrutor da classe campoJogo.
**/
campoJogo :: ~campoJogo(){
	//Destrói a textura do bloco especificada no parâmetro.
	SDL_DestroyTexture(texturaBloco);
}

/**
* \author Leonardo de Souza Fiamoncini 
* \date 31/01/2022.
* \brief Renderiza os blocos com a textura.
**/
void campoJogo::render(){
	//Loop para definir e representar cada um dos blocos.
	for (int i = 0; i < LARGURA_CAMPO_JOGO; i++){
		for (int j = 0; j < ALTURA_CAMPO_JOGO; j++){
			bloco brick = blocos[i][j];

			/*
			Se o estado do bloco não for true, ou seja, se ele não existir,
			um continue é realizado. Dessa forma, ele não será representado 
			na tela.
			*/
			if (!brick.estado){
				continue;
			}

			//Cria um objeto quad1 do tipo quadrilatero.
			quadrilatero* quad1 = new quadrilatero(LARGURA_BLOCO, ALTURA_BLOCO, LARGURA_BLOCO, ALTURA_BLOCO);	
			/*
			Cria uma nova instância rect1 do tipo SDL_Rect que recebe, também do tipo SDL_Rect, 
			um quadrilátero cujos valores são os anteriormente definidos para quad1. 
			*/
			SDL_Rect rect1 = quad1->rect(quad1);
	
			/*
			Cria um outro objeto quad2 do tipo quadrilatero.
			*/
			quadrilatero* quad2 = new quadrilatero(posicaoX + (i * LARGURA_BLOCO), posicaoY + (j * ALTURA_BLOCO), LARGURA_BLOCO, ALTURA_BLOCO);
			/*
			Cria uma nova instância rect1 do tipo SDL_Rect que recebe, também do tipo SDL_Rect, 
			um quadrilátero cujos valores são os anteriormente definidos para quad1. 
			*/
			SDL_Rect rect2 = quad2->rect(quad2);
			/*
			Copia a textura para os quadriláteros criados, que são os blocos.
			pam 1 Renderer em questão.
			pam 2 Textura que será utilizada.
			pam 3 Estrutura SDL_Rect fonte que será a base. 
			pam 4 Estrutura SDL_Rect que será preenchida, a partir do parâmetro anterior,
			com a textura informada.
			*/
			SDL_RenderCopy(renderer, texturaBloco, &rect1, &rect2);
		}
	}
}

/**
* \author Leonardo de Souza Fiamoncini 
* \date 31/01/2022.
* \brief Atualiza a posição do campo do jogo.
* \param dt Delta time.
**/
void campoJogo::update(float dt) { }

/**
* \author Leonardo de Souza Fiamoncini 
* \date 01/02/2022.
* \brief Cria um novo nível, redefinindo todos os blocos que 
serão destruídos.
**/
void campoJogo::novoNivel(){
	for (int i = 0; i < LARGURA_CAMPO_JOGO; i++){
		for (int j = 0; j < ALTURA_CAMPO_JOGO; j++){
			bloco brick;
			/*
			O bloco atual recebe o estado true novamente, indicando 
			que o mesmo existe e deve ser representado.
			*/
			brick.estado = true;
			blocos[i][j] = brick;
		}
	}
}
