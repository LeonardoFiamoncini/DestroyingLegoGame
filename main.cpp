/**
* \author Leonardo de Souza Fiamoncini 
* \date 26/01/2022.
* \version 01/02/2022.
**/

#include "destroyingLego.h"

#include <iostream>

using namespace std;

/**
* \author Leonardo de Souza Fiamoncini 
* \date 26/01/2022.
* \brief Função main que inicia o jogo Destroying Lego
**/
int main(int argc, char* argv[]){ 

	//Cria um objeto jogo do tipo destroyingLego.
	destroyingLego* jogo = new destroyingLego();

	/**
	Chama o método init() para criar uma janela, e caso seja criada com sucesso, 
	a função retorna true, visto que, tem bool como tipo de retorno. Com isso, 
	entra-se no if e se inicia o jogo. 
	**/
	if (jogo->init()){
		jogo->run();
	}

	/**
	Desabilita o uso dessa função, com isso, desalocando a memória 
	que estava sendo utilizada através de alocação dinâmica.
	**/
	delete jogo;
	
	//Retorna o valor 0 para informar que não houve erros no programa.
	return 0;
}
