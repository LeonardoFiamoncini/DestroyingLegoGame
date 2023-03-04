/**
* \author Leonardo de Souza Fiamoncini 
* \date 31/01/2022.
* \version 04/02/2022.
**/

#ifndef J1_CAMPOJOGO_H
#define J1_CAMPOJOGO_H

#include "objsJogo.h" 
#include "quadrilatero.h"

//Dimensões que indicam a posição e o tamanho que os blocos terão.
const int LARGURA_CAMPO_JOGO = 12;
const int ALTURA_CAMPO_JOGO = 9;
const int LARGURA_BLOCO = 64;
const int ALTURA_BLOCO = 24;

/**
* \author Leonardo de Souza Fiamoncini 
* \date 02/02/2022.
* \brief Classe bloco armazena um atributo booleano que indica o 
estado que um bloco se encontra. Ele servirá para indicar se o 
bloco está inteiro ou se já foi atingido.
**/
class bloco {
	public:
		bool estado;
};

/**
* \author Leonardo de Souza Fiamoncini 
* \date 31/01/2022.
* \brief Classe campoJogo armazena os atributos e métodos da área
onde os blocos serão posicionados para que o usuário os atinja. 
A classe herda os atributos e métodos da classe pai objsJogo.
**/
class campoJogo : public objsJogo {
	public:
		campoJogo(SDL_Renderer* renderer);
		~campoJogo();
		void render() override;
		void update(float dt) override;
		void novoNivel();
		float blocoPosicaoX, blocoPosicaoY;
		//Array que guarda o total de blocos do jogo.
		bloco blocos[LARGURA_CAMPO_JOGO][ALTURA_CAMPO_JOGO];	
	private:
		//Renderer com a textura do bloco.
		SDL_Texture* texturaBloco;
};

#endif 
