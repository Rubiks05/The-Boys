#include <stdio.h>
#include <stdlib.h>
#include "fprio.h"


struct fprio_t *fprio_cria() {

		struct fprio_t *p = malloc(sizeof(struct fprio_t));
		if (p == NULL) 
				return NULL;

		p->prim = NULL;
		p->num = 0;

		return p;
}

struct fprio_t *fprio_destroi (struct fprio_t *f) {

		if (f == NULL) 
				return NULL;

		struct fpnodo_t *primeiro = f->prim;
		while (primeiro != NULL) {
				struct fpnodo_t *prox = primeiro->prox;
				free(primeiro->item);
				free(primeiro);
				primeiro = prox;
		}

		free(f);
		return NULL;
}

int fprio_insere (struct fprio_t *f, void *item, int tipo, int prio) {
	
		if (f == NULL || item == NULL) 
				return -1;

		struct fpnodo_t *aux;
		aux = f->prim;
		//Confere se há elementos iguais.
		while(aux != NULL) {
				if (aux->item == item)
						return -1;
				aux = aux->prox;
		}
		aux = f->prim;

		struct fpnodo_t *p = malloc(sizeof(struct fpnodo_t));
		if (p == NULL) 
				return -1;
		p->item = item;
		p->tipo = tipo;
		p->prio = prio;
		p->prox = NULL;
	
		if (f->prim == NULL || f->prim->prio > prio) {
				p->prox = f->prim;
				f->prim = p;
		}
		else {
				aux = f->prim;
				while(aux->prox != NULL && aux->prox->prio <= p->prio) {
						aux = aux->prox;
				}
				p->prox = aux->prox;
				aux->prox = p;
		}

		f->num++;
		return f->num;
}
	
void *fprio_retira (struct fprio_t *f, int *tipo, int *prio) {
	
		if (f == NULL) 
				return NULL;
		if (f->prim == NULL) 
				return NULL;
		if (tipo == NULL || prio == NULL) 
				return NULL;

		struct fpnodo_t *aux = f->prim;
		f->prim = aux->prox;
	
		*tipo = aux->tipo;
		*prio = aux->prio;
		void *item = aux->item;

		free(aux);
		f->num--;
		return item;
}

int fprio_tamanho (struct fprio_t *f) {

		if (f == NULL) 
				return -1;
	
		return f->num;
}

void fprio_imprime (struct fprio_t *f) {
	
		struct fpnodo_t *aux;
		aux = f->prim;
		int first = 1;

		while(aux != NULL) {
				if (!first) 
						printf(" ");
				printf("(%d %d)", aux->tipo, aux->prio);
				aux = aux->prox;
				first = 0;
		}
}
