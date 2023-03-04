/**
* \author Leonardo de Souza Fiamoncini
* \date 12/11/2021.
* \version 01/12/2021.
**/

#ifndef J1_QUADRILATERO_H
#define J1_QUADRILATERO_H

#include <SDL.h>

/**
* \author Leonardo de Souza Fiamoncini
* \date 12/11/2021.
* \brief Classe quadrilatero armazena os atributos de uma figura 
geométrica com quatro lados. 
**/
class quadrilatero{
	public:
		quadrilatero(int x, int y, int w, int h);
		SDL_Rect rect(quadrilatero* q);
		void printQuadrilatero();
		void setX(int x);
		void setY(int y);
		void setW(int w);
		void setH(int h);
		int getX();
		int getY();
		int getW();
		int getH();	
	private:
		int pontoX;
		int pontoY;
		int largura;
		int altura;
};

#endif

