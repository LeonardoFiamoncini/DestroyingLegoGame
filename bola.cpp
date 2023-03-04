/**
* \author Leonardo de Souza Fiamoncini
* \date 28/01/2022.
* \version 10/02/2022.
**/

#include <iostream>
#include <cmath>
#include <math.h>

#include "bola.h"

//Velocidade da bola.
const float VELOCIDADE_BOLA = 500.0f;

using namespace std;

/**
* \author Leonardo de Souza Fiamoncini
* \date 28/01/2022.
* \brief Construtor da classe bola.
* \param renderer Guarda o renderer em questão, que contém 
os estados de atributos da janela.
**/
bola::bola(SDL_Renderer* renderer) : objsJogo(renderer){
	/*
	Cria uma superfície e insere o arquivo bola.png, carregado
	através da função IMG_Load(), nela. 
	*/
	SDL_Surface* surface = IMG_Load("bola.png");
	/*
	Atribui uma textura para a bola.
	pam 1 Renderer da janela em questão.
	pam 2 Superfície utilizada que irá criar a textura. 
	*/
	texturaBola = SDL_CreateTextureFromSurface(renderer, surface);
	
	//Largura da bola.
	largura = 20;
	//Altura da bola.
	altura = 20;
}

/**
* \author Leonardo de Souza Fiamoncini
* \date 28/01/2022.
* \brief Destrutor da classe bola.
**/
bola::~bola(){
	//Destrói a textura especificada no par�metro.
	SDL_DestroyTexture(texturaBola);
}

/**
* \author Leonardo de Souza Fiamoncini 
* \date 28/01/2022.
* \brief Renderiza a bola com a textura.
**/
void bola::render(){
	/*
	Cria um objeto quad1 do tipo quadrilatero, informando suas coordenadas X e Y,
	sua largura e sua altura.
	*/
	quadrilatero* quad1 = new quadrilatero(posicaoX, posicaoY, largura, altura);	
	/*
	Cria uma nova instância rect1 do tipo SDL_Rect que recebe, também do tipo SDL_Rect, 
	um quadrilátero cujos valores são os anteriormente definidos para quad1. 
	*/
	SDL_Rect rect1 = quad1->rect(quad1);
	/*
	Copia a textura para a bola.
	pam 1 Renderer em questão.
	pam 2 Textura que será utilizada.
	pam 3 Estrutura SDL_Rect. NULL foi escolhido para utilizar toda a estrutura.
	pam 4 Estrutura SDL_Rect que será preenchida com a textura.
	*/
	SDL_RenderCopy(renderer, texturaBola, NULL, &rect1);
}

/**
* \author Leonardo de Souza Fiamoncini 
* \date 28/01/2022.
* \brief Atualiza a posição da bola.
* \param dt Delta time.
**/
void bola::update(float dt){
	//Adiciona uma direção para a bola. 
	posicaoX += direcaoX * dt;
	posicaoY += direcaoY * dt;
}

/**
* \author Leonardo de Souza Fiamoncini 
* \date 28/01/2022.
* \brief Método que verifica se a bola colidiu com o objeto passado.
* \param obj Objeto indicado.
* \returns boolean true se colidir ou false se não colidir.
**/
bool bola::colisao(objsJogo* obj){
	if (posicaoX + largura > obj->posicaoX && posicaoX < obj->posicaoX + obj->largura &&
		posicaoY + altura > obj->posicaoY && posicaoY < obj->posicaoY + obj->altura) {
		return true;
	}
	return false;
}

/**
* \author Leonardo de Souza Fiamoncini 
* \date 29/01/2022.
* \brief Método que movimenta a bola de acordo com a direção.
* \param novaDirecaoX Direção do vetor de X.
* \param novaDirecaoY Direção do vetor de Y.
**/
void bola::movimentoBola(float novaDirecaoX, float novaDirecaoY){
	//Normaliza e multiplica o vetor direção pela velocidade da bola.
	float tamanho = sqrtf(novaDirecaoX * novaDirecaoX + novaDirecaoY * novaDirecaoY);
	direcaoX = VELOCIDADE_BOLA * (novaDirecaoX / tamanho);
	direcaoY = VELOCIDADE_BOLA * (novaDirecaoY / tamanho);
}
