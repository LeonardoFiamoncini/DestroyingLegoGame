/**
* \author Leonardo de Souza Fiamoncini 
* \date 27/01/2022.
* \version 02/02/2022.
**/

#ifndef J1_OBJSJOGO_H
#define J1_OBJSJOGO_H

#include <SDL.h>
#include <SDL_image.h>
#include <sstream>

/**
* \author Leonardo de Souza Fiamoncini 
* \date 27/01/2022.
* \brief Classe objsJogo armazena os atributos e métodos de
objetos que fazem parte do jogo, sejam eles uma bola, um 
bloco ou uma prancha. Essa classe terá uma característica 
mais abstrata que as outras, visto que, conta com algumas
funções membro virtuais, que poderão ter diferentes 
implementações nas classes derivadas.
**/
class objsJogo {
	public:
		objsJogo(SDL_Renderer* renderer);
		virtual ~objsJogo() = 0;
		virtual void render();
		virtual void update(float dt);
		float posicaoX, posicaoY, largura, altura;
	protected:
		//Renderer do objeto.
		SDL_Renderer* renderer;
};

#endif 
