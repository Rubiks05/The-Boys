#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "lista.h"
#include "fprio.h"
#include "conjunto.h"
#include "entidades.h"
#include "eventos.h"
#include "funcoes_sec.h"

#define T_INICIO 0
#define T_FIM_DO_MUNDO 525600
#define N_TAMANHO_MUNDO 20000
#define N_HABILIDADES 10
#define N_HEROIS (N_HABILIDADES * 5)
#define N_BASES (N_HEROIS / 5)
#define N_MISSOES (T_FIM_DO_MUNDO / 100)

void ev_iniciais(struct Mundo *mundo)
{
    	mundo->lef = fprio_cria();

        //inserindo herói na lef.
        for (int i=0 ; i<mundo->nherois ; i++) {
                struct Evento *ev = malloc(sizeof(struct Evento));
                ev->tempo = aleat (0, 4320);
                ev->tipo  = CHEGA;
                ev->heroi = i;
                ev->base = aleat(0, mundo->nbases -1);

                //insere (lista(lef), item(ev), tipo(chega = 1), prio(tempo)).
                fprio_insere(mundo->lef, ev, CHEGA, ev->tempo);

        }

        //inserindo missoes na lef.
        for (int i=0 ; i<mundo->nmissoes ; i++) {
        		struct Evento *ev = malloc(sizeof(struct Evento));
            	ev->tempo = aleat(0, T_FIM_DO_MUNDO);
            	ev->tipo = MISSAO;
            	ev->missao = mundo->missoes[i]->id_missao;

                //insere (lista(lef), item(ev), tipo(missao = 9), prio(tempo)).
				assert(mundo->missoes[i]->id_missao < mundo->nmissoes);
            	fprio_insere(mundo->lef, ev, MISSAO , ev->tempo);
        }

        //inserindo evento_fim na lef.
        struct Evento *ev = malloc(sizeof(struct Evento));
        ev->tempo = T_FIM_DO_MUNDO;
        ev->tipo = FIM;

        //insere (lista(lef), item(ev), tipo(fim_do_mundo = 10), prio(tempo)).
        fprio_insere(mundo->lef, ev, FIM, ev->tempo);

}

void funcao_evento_chega(struct Mundo *mundo, struct Evento *ev)
{

		if (!mundo || !ev) 
				return;

        if (ev->tipo != CHEGA) 
				return;

		mundo->herois[ev->heroi]->base_atual = ev->base;
	  
		bool espera_evento;

        if (lista_tamanho(mundo->bases[ev->base]->espera) == 0 && mundo->bases[ev->base]->presentes->num < mundo->bases[ev->base]->lotacao) {
                espera_evento = true;
        }
        else {
                if (mundo->herois[ev->heroi]->paciencia > (10 * lista_tamanho(mundo->bases[ev->base]->espera))) {
                        espera_evento = true;
                }
                else 
						espera_evento = false;
        }
	

        if (espera_evento) {
				cria_ev_espera(mundo, ev);

				//print da função.
				print_chega_espera(mundo, ev);
		}
		else {
				cria_ev_desiste(mundo, ev);

				//print da função.
				print_chega_desiste(mundo, ev);
		}
}

void funcao_evento_espera(struct Mundo *mundo, struct Evento *ev)
{

		if (!mundo || !ev) 
				return;

        if (ev->tipo != ESPERA) 
				return;

		// insere na lista: lista_insere (struct lista_t *lst, int item, int pos);
		lista_insere(mundo->bases[ev->base]->espera, ev->heroi, -1);

		if (lista_tamanho(mundo->bases[ev->base]->espera) > mundo->bases[ev->base]->lotacao_max) {
				mundo->bases[ev->base]->lotacao_max = lista_tamanho(mundo->bases[ev->base]->espera);
		}
	
        cria_ev_avisa(mundo, ev);

		//print da função.
		print_espera(mundo, ev);
}

void funcao_evento_desiste(struct Mundo *mundo, struct Evento *ev)
{

		if (!mundo || !ev) 
				return;

        if (ev->tipo != DESISTE) 
				return;

		ev->destino = aleat(0,9);
	
		cria_ev_viaja(mundo, ev);

		//print da função.
		print_desiste(ev);
}

void funcao_evento_avisa(struct Mundo *mundo, struct Evento *ev)
{

		if (!mundo || !ev) 
				return;

        if (ev->tipo != AVISA) 
				return;
	
		int presentes_base = cjto_card(mundo->bases[ev->base]->presentes);
		int lotacao_base = mundo->bases[ev->base]->lotacao;
		int tam_lista_base = lista_tamanho(mundo->bases[ev->base]->espera);
	
		//print função.
		print_avisa_porteiro(mundo, ev);

		while (presentes_base < lotacao_base && tam_lista_base > 0) {
				// Pega primeiro herói da lista;
				int heroi_retirado;

				lista_retira(mundo->bases[ev->base]->espera, &heroi_retirado, 0);
		
				cjto_insere(mundo->bases[ev->base]->presentes, heroi_retirado);
		
				//print função.
                print_avisa_admite(ev, heroi_retirado);

				cria_ev_entra(mundo, ev, heroi_retirado);

				presentes_base = cjto_card(mundo->bases[ev->base]->presentes);
				tam_lista_base = lista_tamanho(mundo->bases[ev->base]->espera);
		}
}

void funcao_evento_entra(struct Mundo *mundo, struct Evento *ev)
{

		int tpb;
		int aleatorio = aleat(1, 20);
		tpb = 15 + (mundo->herois[ev->heroi]->paciencia * aleatorio) + ev->tempo;
	
		cria_ev_sai(mundo, ev, tpb);

		//print da função.
		print_entra(mundo, ev, tpb);
}

void funcao_evento_sai(struct Mundo *mundo, struct Evento *ev)
{
		if (mundo->herois[ev->heroi]->vivo == 0) {
				mundo->eventos_tratados--;
				return;
		}
	
		cjto_retira (mundo->bases[ev->base]->presentes, ev->heroi);
	
		//print da função.
        print_sai(mundo, ev);

		ev->destino = aleat(0,9);
	
		cria_ev_viaja(mundo, ev);

		cria_ev_avisa(mundo, ev);
}

void funcao_evento_viaja(struct Mundo *mundo, struct Evento *ev)
{

		int x_atual = mundo->bases[ev->base]->local_base.x;
		int y_atual = mundo->bases[ev->base]->local_base.y;
	
		int x_destino = mundo->bases[ev->destino]->local_base.x;
		int y_destino = mundo->bases[ev->destino]->local_base.y;

		int temp1,temp2,temp3;
		temp1 = (x_atual - x_destino) * (x_atual - x_destino);
		temp2 = (y_atual - y_destino) * (y_atual - y_destino);
		temp3 = temp1 + temp2;

		int distancia = raiz_quadrada(temp3);

		int duracao = distancia / mundo->herois[ev->heroi]->velocidade;

		//print da função.
        print_viaja(mundo, ev, distancia, duracao);

		ev->base = ev->destino;

		cria_ev_chega(mundo, ev, duracao);
}

void funcao_evento_morre(struct Mundo *mundo, struct Evento *ev)
{
		mundo->herois[ev->heroi]->vivo = 0;

		cjto_retira(mundo->bases[ev->base]->presentes, ev->heroi);

		//print da função.
        print_morre(ev);

		cria_ev_avisa(mundo, ev);
}

void funcao_evento_missao(struct Mundo *mundo, struct Evento *ev) {

/*-----------------------------------------------------------------------------------*/
// PARTE DA FUNÇÃO EM QUE PEGO AS DISTÂNCIAS DE CADA BASE
		int x_missao = mundo->missoes[ev->missao]->local_missao.x;
		int y_missao = mundo->missoes[ev->missao]->local_missao.y;

		// Vetor bidimensional para distâncias e IDs das bases
		int vector_das_dist[10][2]; // [0] = distância, [1] = id_base

		for (int i = 0; i < mundo->nbases; i++) {
				int x_base = mundo->bases[i]->local_base.x;
				int y_base = mundo->bases[i]->local_base.y;
		
				//distância ao quadrado
				int temp1 = (x_base - x_missao) * (x_base - x_missao) + (y_base - y_missao) * (y_base - y_missao);

				vector_das_dist[i][0] = temp1;
				vector_das_dist[i][1] = i;
		}

		// Ordenando o vetor em ordem crescente de distância
		selection_sort(vector_das_dist, mundo->nbases);
	
/*-----------------------------------------------------------------------------------*/
	
	//inicia variável bpm como falsa
		bool bpm = false;

		int base_que_deu_boa;
	
		int i;
		struct cjto_t *copia_uniao = cjto_cria(mundo->nhabilidades);
		struct cjto_t *aux1, *aux2;


        for (i=0 ; i< mundo->nbases ; i++) {
				struct cjto_t *uniao = cjto_cria(mundo->nhabilidades);

				//print da função.
                printf("%6d: MISSAO %d TENT %d HAB REQ: [ ", ev->tempo, ev->missao,mundo->missoes[ev->missao]->tentativas);
                cjto_imprime(mundo->missoes[ev->missao]->habilidade_missao);
                printf("]\n");

                //print da função.
                printf("%6d: MISSAO %d BASE %d DIST %d HEROIS [ ", ev->tempo, ev->missao, mundo->bases[vector_das_dist[i][1]]->id_base,raiz_quadrada(vector_das_dist[i][0]));
                cjto_imprime(mundo->bases[vector_das_dist[i][1]]->presentes);
                printf("]\n");

		for (int j=0 ; j < mundo->nherois ; j++) {
				// se o heroi[j] pertence a base mais perto.
				if (cjto_pertence (mundo->bases[vector_das_dist[i][1]]->presentes, j) ) {
						aux1 = cjto_uniao (mundo->herois[j]->habilidade_heroi, uniao);
						cjto_destroi(uniao);
						uniao = aux1;	
				
						//print da função.
						printf("%6d: MISSAO %d HAB HEROI %2d: [ ", ev->tempo, ev->missao, j);
                        cjto_imprime(mundo->herois[j]->habilidade_heroi);
                        printf("]\n");
				}
		}

		//print da função.
		printf("%6d: MISSAO %d UNIAO HAB BASE %d: [ ", ev->tempo, ev->missao, mundo->bases[vector_das_dist[i][1]]->id_base);
		cjto_imprime(uniao);
		printf("]\n");

		if (cjto_contem (uniao, mundo->missoes[ev->missao]->habilidade_missao)) {

				base_que_deu_boa = mundo->bases[vector_das_dist[i][1]]->id_base;
				mundo->bases[base_que_deu_boa]->participacao_missao += 1;

				aux2 = cjto_uniao (copia_uniao, uniao);
                cjto_destroi(copia_uniao);
                copia_uniao = aux2;
				if (uniao) 
						cjto_destroi(uniao);
				bpm = true;
				break;
		}
		mundo->missoes[ev->missao]->tentativas += 1;

		//Se a base não servir, tiro as habilidades do conjunto união para a próxima base.
		cjto_destroi(uniao);
		}
		
		if (bpm) {

				//missao recebe como cumprida.
				mundo->missoes[ev->missao]->cumprida = 1;
				mundo->missoes_cumpridas += 1;

				for (int k=0 ; k < mundo->nherois ; k++) {
						if (cjto_pertence (mundo->bases[base_que_deu_boa]->presentes, k)) {
								int numerador = mundo->missoes[ev->missao]->perigo;
								double denominador = mundo->herois[k]->paciencia + mundo->herois[k]->experiencia + 1.0;
								double risco = numerador / denominador;
								int aleatorio = aleat(1,30);

								if (risco > aleatorio) {
										cria_ev_morre(mundo, ev, k, base_que_deu_boa);
								}
								else 
										mundo->herois[k]->experiencia += 1;
						}
				}

				//print da função.
				printf("%6d: MISSAO %d CUMPRIDA BASE %d HABS: [ ", ev->tempo, ev->missao, base_que_deu_boa);
				cjto_imprime(copia_uniao);
				printf("]\n");

				mundo->missoes_realizadas += 1;
		}

		else {
				//print da função.
				printf("%6d: MISSAO %d IMPOSSIVEL\n", ev->tempo, ev->missao);

				mundo->missoes[ev->missao]->tentativas += 1;
				cria_ev_missao(mundo, ev);
		}

		if (mundo->missoes[ev->missao]->tentativas > mundo->maior_tentativas) {
				mundo->maior_tentativas = mundo->missoes[ev->missao]->tentativas;
		}
	
		cjto_destroi(copia_uniao);
}

void funcao_evento_fim(struct Mundo *mundo, struct Evento *ev)
{	
		int mort = 0;

		//imprimindo heróis.
		for (int o=0 ; o<mundo->nherois ; o++) {
				if (mundo->herois[o]->vivo == 1) {
						int heroi_id = mundo->herois[o]->id_heroi;
						int paciencia = mundo->herois[o]->paciencia;
						int velocidade = mundo->herois[o]->velocidade;
						int experiencia = mundo->herois[o]->experiencia;

						printf("HEROI %2d VIVO  PAC %3d VEL %4d EXP %4d HABS [ ", heroi_id, paciencia, velocidade, experiencia);
						cjto_imprime(mundo->herois[o]->habilidade_heroi);
						printf("]\n");
				}
				else {
						mort += 1;
						int heroi_id = mundo->herois[o]->id_heroi;
						int paciencia = mundo->herois[o]->paciencia;
						int velocidade = mundo->herois[o]->velocidade;
						int experiencia = mundo->herois[o]->experiencia;

						printf("HEROI %2d MORTO  PAC %3d VEL %4d EXP %4d HABS [ ", heroi_id, paciencia, velocidade, experiencia);
                        cjto_imprime(mundo->herois[o]->habilidade_heroi);
                        printf("]\n");
				}
		}

		//imprimindo bases.
		for (int y=0 ; y<mundo->nbases ; y++) {
				int base = mundo->bases[y]->id_base;
				int lotacao = mundo->bases[y]->lotacao;
				int lotacao_max = mundo->bases[y]->lotacao_max;
				int participacao_missao = mundo->bases[y]->participacao_missao;

				printf("BASE %2d LOT %2d FILA MAX %2d MISSOES %d\n", base, lotacao, lotacao_max, participacao_missao);
		}

		//Estatísticas.
		printf("%6d: FIM\n", ev->tempo);
		printf("EVENTOS TRATADOS: %d\n", mundo->eventos_tratados);
		double porcentagem = 100.0 * ((double)mundo->missoes_cumpridas / mundo->nmissoes);
		printf("MISSOES CUMPRIDAS: %d/%d (%.1f%%)\n", mundo->missoes_cumpridas, mundo->nmissoes, porcentagem);
		int min_missoes = 1;

		int count = 0;
		for (int p=0 ; p<mundo->nmissoes ; p++) {
				count += mundo->missoes[p]->tentativas;
		}
		double media = (double)count / mundo->missoes_realizadas;
		printf("TENTATIVAS/MISSAO: MIN %d, MAX %d, MEDIA %.1f\n", min_missoes, mundo->maior_tentativas, media);


		double taxa_mort = 100.0 * ((double)mort / 50);
		printf("TAXA MORTALIDADE: %.1f%%\n", taxa_mort);

		int tamanho_lef = fprio_tamanho(mundo->lef);
		for (int i=0 ; i<tamanho_lef ; i++) {
				int tipo, prio;
        		struct Evento *ev = fprio_retira(mundo->lef, &tipo, &prio);

				free(ev);
				ev = NULL;
		}
}




