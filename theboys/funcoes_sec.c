#include <stdio.h>
#include <stdlib.h>
#include "funcoes_sec.h"
#include "eventos.h"
#include <math.h>

/*--------------------------------------------------------------------------------*/
//FUNÇÕES USADAS SECUNDARIAMENTE.

long aleat (long min, long max)
{
        return min + rand() % (max - min + 1);
}

int raiz_quadrada(int numero) {

        if (numero <= 0) 
                return 0;
        int x = numero;
        int y = (x + 1) / 2;
        while (y < x) {
                x = y;
                y = (x + numero / x) / 2;
        }
        return x;
}

void troca(int *xp, int *yp) {

        int temp = *xp;
        *xp = *yp;
        *yp = temp;
}

void selection_sort(int arr[][2], int size) {
	for (int i = 0; i < size - 1; i++) {
		int min_idx = i;
		for (int j = i + 1; j < size; j++) {
			if (arr[j][0] < arr[min_idx][0]) {
                	        min_idx = j;
            	        }
                }

        	if (min_idx != i) {
            		int temp_dist = arr[i][0];
            		int temp_id = arr[i][1];

            		arr[i][0] = arr[min_idx][0];
            		arr[i][1] = arr[min_idx][1];

            		arr[min_idx][0] = temp_dist;
            		arr[min_idx][1] = temp_id;
        }
    }
}
/*--------------------------------------------------------------------------------*/
// CRIAÇÃO DE EVENTOS:

void cria_ev_espera(struct Mundo *mundo, struct Evento *ev)
{
        struct Evento *novo_ev = malloc(sizeof(struct Evento));
        if (!novo_ev) 
                return;

       	novo_ev->tempo = ev->tempo;
        novo_ev->tipo = ESPERA;
        novo_ev->heroi = ev->heroi;
        novo_ev->base = ev->base;
       	fprio_insere(mundo->lef, novo_ev, ESPERA, novo_ev->tempo);
}

void cria_ev_desiste(struct Mundo *mundo, struct Evento *ev)
{
	struct Evento *novo_ev = malloc(sizeof(struct Evento));
        if (!novo_ev) 
                return;

        novo_ev->tempo = ev->tempo;
        novo_ev->tipo = DESISTE;
        novo_ev->heroi = ev->heroi;
        novo_ev->base = ev->base;
      	fprio_insere(mundo->lef, novo_ev, DESISTE, novo_ev->tempo);
}

void cria_ev_avisa(struct Mundo *mundo, struct Evento *ev)
{
	struct Evento *novo_ev = malloc(sizeof(struct Evento));
        if (!novo_ev) 
                return;

        novo_ev->tempo = ev->tempo;
        novo_ev->tipo = AVISA;
        novo_ev->base = ev->base;
        fprio_insere(mundo->lef, novo_ev, AVISA, novo_ev->tempo);
}

void cria_ev_viaja(struct Mundo *mundo, struct Evento *ev) 
{
	struct Evento *novo_ev = malloc(sizeof(struct Evento));
        if (!novo_ev) 
                return;

        novo_ev->tempo = ev->tempo;
        novo_ev->tipo = VIAJA;
        novo_ev->heroi = ev->heroi;
        novo_ev->destino = ev->destino;
	novo_ev->base = ev->base;

        fprio_insere(mundo->lef, novo_ev, VIAJA, novo_ev->tempo);
}

void cria_ev_entra(struct Mundo *mundo, struct Evento *ev, int heroi_retirado)
{
	struct Evento *novo_ev = malloc(sizeof(struct Evento));
        if (!novo_ev) 
                return;

       	novo_ev->tempo = ev->tempo;
       	novo_ev->tipo = ENTRA;
        novo_ev->heroi = heroi_retirado;
        novo_ev->base = ev->base;

        fprio_insere(mundo->lef, novo_ev, ENTRA, novo_ev->tempo);
}

void cria_ev_sai(struct Mundo *mundo, struct Evento *ev, int tpb)
{
        struct Evento *novo_ev = malloc(sizeof(struct Evento));
        if (!novo_ev) 
                return;

        novo_ev->tempo = tpb;
        novo_ev->tipo = SAI;
        novo_ev->heroi = ev->heroi;
        novo_ev->base = ev->base;
        fprio_insere(mundo->lef, novo_ev, SAI, novo_ev->tempo);
}

void cria_ev_chega(struct Mundo *mundo, struct Evento *ev, int duracao)
{
	struct Evento *novo_ev = malloc(sizeof(struct Evento));
        if (!novo_ev) 
                return;
        novo_ev->tempo = ev->tempo + duracao;
        novo_ev->tipo = CHEGA;
        novo_ev->heroi = ev->heroi;
        novo_ev->destino = ev->destino;
	novo_ev->base = ev->base;
        fprio_insere(mundo->lef, novo_ev, CHEGA, novo_ev->tempo);
}

void cria_ev_morre(struct Mundo *mundo, struct Evento *ev, int k, int base_que_deu_boa)
{
	struct Evento *novo_ev = malloc(sizeof(struct Evento));
        if (!novo_ev) 
                return;
        novo_ev->tempo = ev->tempo;
        novo_ev->tipo = MORRE;
        novo_ev->heroi = k;
	novo_ev->base = base_que_deu_boa;
	novo_ev->missao = ev->missao;
        fprio_insere(mundo->lef, novo_ev, MORRE, novo_ev->tempo);
}

void cria_ev_missao(struct Mundo *mundo, struct Evento *ev)
{
	struct Evento *novo_ev = malloc(sizeof(struct Evento));
        if (!novo_ev) 
                return;
        novo_ev->tempo = ev->tempo + 24*60;
        novo_ev->tipo = MISSAO;
        novo_ev->missao = ev->missao;
        fprio_insere(mundo->lef, novo_ev, MISSAO, novo_ev->tempo);
}

/*--------------------------------------------------------------------------------*/
//PRINTS DAS FUNCOES.

void print_chega_espera(struct Mundo *mundo, struct Evento *ev)
{
	printf("%6d: CHEGA  HEROI %2d BASE %d (%2d/%2d) ESPERA\n", ev->tempo, ev->heroi, ev->base, cjto_card(mundo->bases[ev->base]->presentes), mundo->bases[ev->base]->lotacao);
}

void print_chega_desiste(struct Mundo *mundo, struct Evento *ev)
{
	printf("%6d: CHEGA  HEROI %2d BASE %d (%2d/%2d) DESISTE\n", ev->tempo, ev->heroi, ev->base, cjto_card(mundo->bases[ev->base]->presentes), mundo->bases[ev->base]->lotacao);
}

void print_espera(struct Mundo *mundo, struct Evento *ev)
{
	printf("%6d: ESPERA HEROI %2d BASE %d (%2d)\n", ev->tempo, ev->heroi, ev->base, lista_tamanho(mundo->bases[ev->base]->espera));
}

void print_desiste(struct Evento *ev)
{
	printf("%6d: DESIST HEROI %2d BASE %d\n", ev->tempo, ev->heroi, ev->base);
}

void print_avisa_porteiro(struct Mundo *mundo, struct Evento *ev)
{
	printf("%6d: AVISA  PORTEIRO BASE %d (%2d/%2d) ", ev->tempo, ev->base, cjto_card(mundo->bases[ev->base]->presentes), mundo->bases[ev->base]->lotacao);
        printf("FILA [ ");
        lista_imprime(mundo->bases[ev->base]->espera);
        printf(" ]\n");
}

void print_avisa_admite(struct Evento *ev, int heroi_retirado)
{
	printf("%6d: AVISA  PORTEIRO BASE %d ADMITE %2d\n", ev->tempo, ev->base, heroi_retirado);
}

void print_entra(struct Mundo *mundo, struct Evento *ev, int tpb)
{
	printf("%6d: ENTRA  HEROI %2d BASE %d (%2d/%2d) SAI %d\n", ev->tempo, ev->heroi, ev->base, cjto_card(mundo->bases[ev->base]->presentes), mundo->bases[ev->base]->lotacao, tpb);
}

void print_sai(struct Mundo *mundo, struct Evento *ev)
{
	printf("%6d: SAI    HEROI %2d BASE %d (%2d/%2d)\n", ev->tempo, ev->heroi, ev->base, cjto_card(mundo->bases[ev->base]->presentes), mundo->bases[ev->base]->lotacao);
}

void print_viaja(struct Mundo *mundo, struct Evento *ev, int distancia, int duracao)
{
	printf("%6d: VIAJA  HEROI %2d BASE %d BASE %d DIST %d VEL %d CHEGA %d\n", ev->tempo, ev->heroi, ev->base, ev->destino, distancia, mundo->herois[ev->heroi]->velocidade, ev->tempo+duracao);
}

void print_morre(struct Evento *ev)
{
	printf("%6d: MORRE  HEROI %2d MISSAO %d\n", ev->tempo, ev->heroi, ev->missao);
}












