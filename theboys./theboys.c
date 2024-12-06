// programa principal do projeto "The Boys - 2024/2"
// Autor: Antonio da Ressurreição Filho, GRR 20245202

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "lista.h"
#include "fprio.h"
#include "conjunto.h"
#include "entidades.h"
#include "funcoes_sec.h"
#include "cria_mundo.h"
#include "destroi_mundo.h"
#include "eventos.h"
#include "chamando_lef.h"

#define T_INICIO 0
#define T_FIM_DO_MUNDO 525600
#define N_TAMANHO_MUNDO 20000
#define N_HABILIDADES 10
#define N_HEROIS (N_HABILIDADES * 5)
#define N_BASES (N_HEROIS / 5)
#define N_MISSOES (T_FIM_DO_MUNDO / 100)


int main ()
{

srand(time(NULL));

/*----------------------------------------------------------------------------------*/
//CRIANDO MUNDO E INICIALIZANDO:

	struct Mundo *mundo = cria_mundo();

/*----------------------------------------------------------------------------------*/
// EVENTOS INICIAIS:

	ev_iniciais(mundo);

/*----------------------------------------------------------------------------------*/
// CHAMANDO A LEF:

	chamando_lef(mundo);

/*----------------------------------------------------------------------------------*/
//DESTRUINDO O MUNDO:

	destroi_mundo(mundo);
	
/*----------------------------------------------------------------------------------*/
	return (0) ;
}

