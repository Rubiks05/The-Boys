#ifndef EVENTOS_INICIAIS_H
#define EVENTOS_INICIAIS_H

#include "entidades.h"
#include "lista.h"
#include "fprio.h"
#include "conjunto.h"

#define CHEGA 1
#define ESPERA 2
#define DESISTE 3
#define AVISA 4
#define ENTRA 5
#define SAI 6
#define VIAJA 7
#define MORRE 8
#define MISSAO 9
#define FIM 10

struct Evento {

	int tempo;
	int tipo;
	int base;
	int heroi;
	int destino;
	int missao;

};

void ev_iniciais(struct Mundo *mundo);

void funcao_evento_chega(struct Mundo *mundo, struct Evento *ev);

void funcao_evento_espera(struct Mundo *mundo, struct Evento *ev);

void funcao_evento_desiste(struct Mundo *mundo, struct Evento *ev);

void funcao_evento_avisa(struct Mundo *mundo, struct Evento *ev);

void funcao_evento_entra(struct Mundo *mundo, struct Evento *ev);

void funcao_evento_sai(struct Mundo *mundo, struct Evento *ev);

void funcao_evento_viaja(struct Mundo *mundo, struct Evento *ev);

void funcao_evento_morre(struct Mundo *mundo, struct Evento *ev);

void funcao_evento_missao(struct Mundo *mundo, struct Evento *ev);

void funcao_evento_fim(struct Mundo *mundo, struct Evento *ev);

#endif

