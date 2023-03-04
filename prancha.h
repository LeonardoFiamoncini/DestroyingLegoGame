/**
* \author Leonardo de Souza Fiamoncini 
* \date 01/02/2022.
* \version 03/02/2022.
**/

#ifndef J1_PRANCHA_H
#define J1_PRANCHA_H

#include "objsJogo.h"
#include "quadrilatero.h"

/**
* \author Leonardo de Souza Fiamoncini 
* \date 01/02/2022.
* \brief Classe prancha armazena os atributos e métodos da prancha. 
No caso, a prancha terá a função de rebater a bola com o objetivo 
de acertar todos os blocos e, assim, ganhar o jogo. Além disso, 
ela que será a responsável por não deixar a bola cair, 
impedindo assim, que o jogo reinicie. A classe herda os 
atributos e métodos da classe pai objsJogo.
**/
class prancha : public objsJogo {
	public:
		prancha(SDL_Renderer* renderer);
		~prancha();
		void render() override;
		void update(float dt) override;
	private:
		//Renderer com a textura da prancha.
		SDL_Texture* texturaPrancha;
};

#endif 
