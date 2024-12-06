#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lista.h"
#include "fprio.h"
#include "conjunto.h"
#include "entidades.h"
#include "funcoes_sec.h"

#define T_INICIO 0
#define T_FIM_DO_MUNDO 525600
#define N_TAMANHO_MUNDO 20000
#define N_HABILIDADES 10
#define N_HEROIS (N_HABILIDADES * 5)
#define N_BASES (N_HEROIS / 5)
#define N_MISSOES (T_FIM_DO_MUNDO / 100)


//inicializando mundo
struct Mundo *cria_mundo() {
	struct Mundo *mundo = malloc(sizeof(struct Mundo));
	if (mundo == NULL) 
                return NULL;

        mundo->nhabilidades = N_HABILIDADES;
        mundo->tamanhoMundo.x = N_TAMANHO_MUNDO;
        mundo->tamanhoMundo.y = N_TAMANHO_MUNDO;
        mundo->relogio = T_INICIO;
	mundo->eventos_tratados = 0;
	mundo->missoes_cumpridas = 0;
	mundo->missoes_realizadas = 0;
        mundo->maior_tentativas = 1;
        mundo->tentativas = 0;

        //inicializando os herois
        mundo->nherois = N_HEROIS;
        mundo->herois = malloc(mundo->nherois * sizeof(struct Heroi *));
	if (mundo->herois == NULL) 
                return NULL;

        for (int i=0 ; i< N_HEROIS ; i++) {
                mundo->herois[i] = malloc(sizeof(struct Heroi));
		if (mundo->herois[i] == NULL) 
                        return NULL;

                mundo->herois[i]->id_heroi = i;
                mundo->herois[i]->experiencia = 0;
                mundo->herois[i]->paciencia = aleat(0,100);
                mundo->herois[i]->velocidade = aleat(50,5000);
		mundo->herois[i]->vivo = 1;

                int tamanho_conjunto = aleat(1,3);
                mundo->herois[i]->habilidade_heroi = cjto_aleat(tamanho_conjunto, 10);
        }
	
	//inicializando as bases
        mundo->nbases = N_BASES;
        mundo->bases = malloc(mundo->nbases * sizeof(struct Base *));
	if (mundo->bases == NULL)
                return NULL;

        for (int i=0 ; i < N_BASES ; i++) {
                mundo->bases[i] = malloc(sizeof(struct Base));
		if (mundo->bases[i] == NULL) 
                        return NULL;

                mundo->bases[i]->id_base = i;

		mundo->bases[i]->lotacao_max = 0;
        	mundo->bases[i]->participacao_missao = 0;

                mundo->bases[i]->local_base.x = aleat(0, N_TAMANHO_MUNDO-1);
                mundo->bases[i]->local_base.y = aleat(0, N_TAMANHO_MUNDO-1);

                mundo->bases[i]->lotacao = aleat(3,10);
                mundo->bases[i]->espera = lista_cria();

                mundo->bases[i]->presentes = cjto_cria(50);
        }

	//inicializando as missoes
        mundo->nmissoes = N_MISSOES;
        mundo->missoes = malloc(mundo->nmissoes * sizeof(struct Missao *));
	if (mundo->missoes == NULL) 
                return NULL;

        for (int i=0 ; i < N_MISSOES ; i++) {
                mundo->missoes[i] = malloc(sizeof(struct Missao));
		if (mundo->missoes[i] == NULL) 
                        return NULL;
		
		//começam como não cumpridas.
		mundo->missoes[i]->cumprida = 0;
		mundo->missoes[i]->tentativas = 1;
                mundo->missoes[i]->id_missao = i;

                mundo->missoes[i]->local_missao.x = aleat(0, N_TAMANHO_MUNDO - 1);
                mundo->missoes[i]->local_missao.y = aleat(0, N_TAMANHO_MUNDO - 1);

                int tamanho_conjunto = aleat(6,10);
                mundo->missoes[i]->habilidade_missao = cjto_aleat(tamanho_conjunto, 10);

                mundo->missoes[i]->perigo = aleat(0,100);
        }

	return mundo;
}
