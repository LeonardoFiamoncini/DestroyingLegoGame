/**
* \author Leonardo de Souza Fiamoncini 
* \date 01/02/2022.
* \version 09/02/2022.
**/

#include <iostream>

#include "prancha.h"

using namespace std;

/**
* \author Leonardo de Souza Fiamoncini 
* \date 01/02/2022.
* \brief Construtor da classe prancha.
* \param renderer Guarda o renderer em questão, que contém 
os estados de atributos da janela.
**/
prancha::prancha(SDL_Renderer* renderer) : objsJogo(renderer){
	/*
	Cria uma superfície e insere o arquivo prancha.png, carregado
	através da função IMG_Load(), nela. 
	*/
	SDL_Surface* surface = IMG_Load("prancha.png");
	/*
	Atribui uma textura para a prancha.
	pam 1 Renderer da janela em questão.
	pam 2 Superfície utilizada que irá criar a textura. 
	*/
	texturaPrancha = SDL_CreateTextureFromSurface(renderer, surface);

	//Libera os recursos RGB usados pela surface criada anteriormente.
	SDL_FreeSurface(surface);

	posicaoX = 0;
	posicaoY = 559;
	largura = 75;
	altura = 25;
}

/**
* \author Leonardo de Souza Fiamoncini 
* \date 01/02/2022.
* \brief Destrutor da classe prancha.
**/
prancha::~prancha(){
	//Destrói a textura da prancha especificada no parâmetro.
	SDL_DestroyTexture(texturaPrancha);
}

/**
* \author Leonardo de Souza Fiamoncini 
* \date 01/02/2022.
* \brief Renderiza a prancha com a textura.
**/
void prancha::render(){
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
	Copia a textura para a prancha.
	pam 1 Renderer em questão.
	pam 2 Textura que será utilizada.
	pam 3 Estrutura SDL_Rect. NULL foi escolhido para utilizar toda a estrutura.
	pam 4 Estrutura SDL_Rect que será preenchida com a textura.
	*/
	SDL_RenderCopy(renderer, texturaPrancha, NULL, &rect1);
}

/**
* \author Leonardo de Souza Fiamoncini 
* \date 02/02/2022.
* \brief Atualiza a prancha. Como vimos na classe objsJogo, o método
update era uma função virtual, por conta disso, as classes herdeiras
poderiam ter um comportamento diferente, mas sempre com a mesma 
assinatura. Nesse caso, temos que a função update() não realiza 
nenhuma ação.
* \param dt Delta time.
**/
void prancha::update(float dt){ }
