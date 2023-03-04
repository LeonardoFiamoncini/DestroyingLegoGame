/**
* \author Leonardo de Souza Fiamoncini 
* \date 02/02/2022.
* \version 10/02/2022.
**/

#ifndef J1_DESTROYINGLEGO_H
#define J1_DESTROYINGLEGO_H

#include <SDL.h>
#include <SDL_image.h>
#include <vector>


#include "bola.h"
#include "campoJogo.h"
#include "prancha.h"

#define DELAY_FPS 500

using namespace std;

/**
* \author Leonardo de Souza Fiamoncini 
* \date 02/02/2022.
* \brief Classe destroyingLego armazena os atributos e métodos 
que compõem as características e os comportamentos gerais do 
jogo, sejam eles funções que criam a janela, a interface do 
game, ou fenômenos físicos de colisão e reflexão da bola. 
**/
class destroyingLego {
	public:
		destroyingLego();
		~destroyingLego();
		bool init();
		void run();
	private:
		void render(); 
		void update(float dt); 
		void destruir(); 
		void novoJogo(); 
		int getBlocos(); 
		void redefinirBola();
		void setPranchaX(float x); 
		float reflexaoBolaPrancha(float hitX); 
		void reflexaoBolaBloco(int direcaoIndex); 
		void colisaoBolaBorda(); 
		void colisaoBolaPrancha(); 
		void colisaoBolaBloco();  
		
		SDL_Window* janelaJogo;
		SDL_Renderer* rendererJogo;
		SDL_Texture* texturaJogo;
		campoJogo* campo_jogo;
		bola* bola1;
		prancha* prancha1;
		//Flag que indica se a bola está posicionada sobre a prancha.
		bool bolaNaPrancha;
		//Timing.
		unsigned int ultimoTick, fps, taxaFps, countFps;
		vector <objsJogo*> objetos;
};

#endif 
