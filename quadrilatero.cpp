/**
* \author Leonardo de Souza Fiamoncini
* \date 12/11/2021.
* \version 01/12/2021.
**/

#include <iostream>

#include <SDL.h>
#include "quadrilatero.h"

using namespace std;

/**
* \author Leonardo de Souza Fiamoncini
* \date 12/11/2021.
* \brief Construtor da classe quadrilatero.
* \param x Guarda a coordenada x do ponto superior 
esquerdo do quadrilátero.
* \param y Guarda a coordenada y do ponto superior 
esquerdo do quadrilátero.
* \param w Guarda a largura do quadrilátero.
* \param h Guarda a altura do quadrilátero.
**/
quadrilatero::quadrilatero(int x, int y, int w, int h){
	pontoX = x;
	pontoY = y;
	largura = w;
	altura = h;
}

/**
* \author Leonardo de Souza Fiamoncini
* \date 12/11/2021.
* \brief Método que, a partir dos atributos de um quadrilatero, 
constrói uma estrutura retangular, por isso o nome SDL_Rect.
* \param q Recebe um quadrilatero.
* \return quad, estrutura retangular do tipo SDL_Rect.
**/
SDL_Rect quadrilatero::rect(quadrilatero* q){
	//Inicializa um objeto quad do tipo SDL_Rect.
	SDL_Rect quad;
	/*
	Estrutura contém x, y, w e h.
	x guarda a coordenada x do ponto superior 
	esquerdo do quadrilátero, então recebe 
	pontoX. 
	*/
	quad.x = q->pontoX;
	/*	
	y guarda a coordenada y do ponto superior 
	esquerdo do quadrilátero, então recebe 
	pontoY. 
	*/
	quad.y = q->pontoY;
	//w guarda a largura do quadrilátero, então recebe largura.
	quad.w = q->largura;
	//h guarda a altura do quadrilátero, então recebe altura.
	quad.h = q->altura;
	return quad;
}

/**
* \author Leonardo de Souza Fiamoncini
* \date 12/11/2021.
* \brief Método que imprime os atributos do quadrilatero.
**/
void quadrilatero::printQuadrilatero(){
	cout << "Ponto x: " << pontoX << endl;
	cout << "Ponto y: " << pontoY << endl;
	cout << "Largura: " << largura << endl;
	cout << "Altura: " << altura << endl;
}

/**
* \author Leonardo de Souza Fiamoncini
* \date 12/11/2021.
* \brief Método que define o pontoX do quadrilatero.
* \param x Guarda a coordenada x do ponto superior 
esquerdo do quadrilatero.
**/
void quadrilatero::setX(int x){
	pontoX = x;
}

/**
* \author Leonardo de Souza Fiamoncini
* \date 12/11/2021.
* \brief Método que define o pontoY do quadrilatero.
* \param y Guarda a coordenada y do ponto superior 
esquerdo do quadrilatero.
**/
void quadrilatero::setY(int y){
	pontoY = y;
}

/**
* \author Leonardo de Souza Fiamoncini
* \date 12/11/2021.
* \brief Método que define a largura do quadrilatero.
* \param w Guarda a largura do quadrilatero.
**/
void quadrilatero::setW(int w){
	largura = w;
}

/**
* \author Leonardo de Souza Fiamoncini
* \date 12/11/2021.
* \brief Método que define a altura do quadrilatero.
* \param h Guarda a altura do quadrilatero.
**/
void quadrilatero::setH(int h){
	altura = h;
}

/**
* \author Leonardo de Souza Fiamoncini
* \date 12/11/2021.
* \brief Método que retorna a coordenada x do ponto superior 
esquerdo do quadrilatero.
* \return pontoX.
**/
int quadrilatero::getX(){
	return pontoX;
}

/**
* \author Leonardo de Souza Fiamoncini
* \date 12/11/2021.
* \brief Método que retorna a coordenada y do ponto superior 
esquerdo do quadrilatero.
* \return pontoY.
**/
int quadrilatero::getY(){
	return pontoY;
}

/**
* \author Leonardo de Souza Fiamoncini
* \date 12/11/2021.
* \brief Método que retorna a largura do quadrilatero.
* \return largura.
**/
int quadrilatero::getW(){
	return largura;
}

/**
* \author Leonardo de Souza Fiamoncini
* \date 12/11/2021.
* \brief Método que retorna a altura do quadrilatero.
* \return altura.
**/	
int quadrilatero::getH(){
	return altura;
}

