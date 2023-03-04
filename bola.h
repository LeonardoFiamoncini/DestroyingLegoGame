/**
* \author Leonardo de Souza Fiamoncini 
* \date 28/01/2022.
* \version 10/02/2022.
**/

#ifndef J1_BOLA_H
#define J1_BOLA_H

#include "objsJogo.h"
#include "quadrilatero.h"

/**
* \author Leonardo de Souza Fiamoncini 
* \date 28/01/2022.
* \brief Classe bola armazena os atributos e métodos da bola. 
No caso, a bola terá a função de destruir os blocos do jogo. 
A classe herda os atributos e métodos da classe pai objsJogo.
**/
class bola : public objsJogo {
	public:
		bola(SDL_Renderer* renderer);
		~bola();
		void render() override;
		void update(float dt) override;
		bool colisao(objsJogo* obj);
		void movimentoBola(float novaDirecaoX, float novaDirecaoY);
		float direcaoX, direcaoY;
	private:
		//Renderer da textura da bola.
		SDL_Texture* texturaBola;
};

#endif 
