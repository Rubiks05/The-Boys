#ifndef FUNCOES_SEC_H
#define FUNCOES_SEC_H

#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include "eventos.h"
#include "entidades.h"

long aleat (long min, long max);

int raiz_quadrada(int numero);

void selection_sort(int arr[][2], int n);

void troca(int *xp, int *yp);

void cria_ev_espera(struct Mundo *mundo, struct Evento *ev);

void cria_ev_desiste(struct Mundo *mundo, struct Evento *ev);

void cria_ev_avisa(struct Mundo *mundo, struct Evento *ev);

void cria_ev_viaja(struct Mundo *mundo, struct Evento *ev);

void cria_ev_entra(struct Mundo *mundo, struct Evento *ev, int heroi_retirado);

void cria_ev_sai(struct Mundo *mundo, struct Evento *ev, int tpb);

void cria_ev_chega(struct Mundo *mundo, struct Evento *ev, int duracao);

void cria_ev_morre(struct Mundo *mundo, struct Evento *ev, int k, int base_que_deu_boa);

void cria_ev_missao(struct Mundo *mundo, struct Evento *ev);

void print_chega_espera(struct Mundo *mundo, struct Evento *ev);

void print_chega_desiste(struct Mundo *mundo, struct Evento *ev);

void print_espera(struct Mundo *mundo, struct Evento *ev);

void print_desiste(struct Evento *ev);

void print_avisa_porteiro(struct Mundo *mundo, struct Evento *ev);

void print_avisa_admite(struct Evento *ev, int heroi_retirado);

void print_entra(struct Mundo *mundo, struct Evento *ev, int tpb);

void print_sai(struct Mundo *mundo, struct Evento *ev);

void print_viaja(struct Mundo *mundo, struct Evento *ev, int distancia, int duracao);

void print_morre(struct Evento *ev);

#endif
