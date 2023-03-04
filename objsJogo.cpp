/**
* \author Leonardo de Souza Fiamoncini 
* \date 27/01/2022.
* \version 02/02/2022.
**/

#include <iostream>

#include "objsJogo.h"

using namespace std;

/**
* \author Leonardo de Souza Fiamoncini 
* \date 27/01/2022.
* \brief Construtor da classe objsJogo.
* \param renderer Guarda o renderer em questão, que contém 
os estados de atributos da janela.
**/
objsJogo::objsJogo(SDL_Renderer* renderer){
	this->renderer = renderer;
	posicaoX = 0;
	posicaoY = 0;
	largura = 1;
	altura = 1;
}

/**
* \author Leonardo de Souza Fiamoncini 
* \date 27/01/2022.
* \brief Destrutor da classe objsJogo. Como foi possível perceber
no header dessa classe, esse é um método virtual, ou seja, seus 
herdeiros poderão sobrescrevê-la, com isso, tendo 
comportamentos divergentes uns dos outros.
**/
objsJogo::~objsJogo(){ }

/**
* \author Leonardo de Souza Fiamoncini 
* \date 27/01/2022.
* \brief Função virtual que renderiza o objeto. Por se tratar de 
uma função virtual, seus herdeiros poderão sobrescrevê-la, com 
isso, tendo comportamentos divergentes uns dos outros.
**/
void objsJogo::render(){ }

/**
* \author Leonardo de Souza Fiamoncini 
* \date 28/01/2022.
* \brief Função virtual que atualiza o objeto. Por se tratar de 
uma função virtual, seus herdeiros poderão sobrescrevê-la, com 
isso, tendo comportamentos divergentes uns dos outros.
* \param dt Delta time.
**/
void objsJogo::update(float dt){ }
