//TP4
// TAD lista de números inteiros
// Carlos Maziero - DINF/UFPR, Out 2024
//
// Implementação do TAD - a completar
//
// Implementação com lista encadeada dupla não-circular

#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

struct lista_t *lista_cria() {

        struct lista_t *l = malloc(sizeof(struct lista_t));
        if (l == NULL) 
				return NULL;

        l->prim = NULL;
        l->ult = NULL;
        l->tamanho = 0;

        return l;
}

struct lista_t *lista_destroi(struct lista_t *lst) {

        if (lst == NULL) 
				return NULL;

        struct item_t *primeiro = lst->prim;
        while (primeiro != NULL) {
                struct item_t *prox = primeiro->prox;
                free(primeiro);
                primeiro = prox;
        }

        free(lst);
        return NULL;
}
int lista_insere (struct lista_t *lst, int item, int pos) {
	
		if (lst == NULL) 
			return -1;

		if (pos == -1 || pos >= lst->tamanho) 
				pos = lst->tamanho-1;

    	struct item_t *p = malloc(sizeof(struct item_t));
    	if (p == NULL) 
				return -1;
		p->valor = item;
		p->prox = NULL;
		p->ant = NULL;

        if (lst->prim == NULL) {
                lst->prim = p;
                lst->ult = p;
        }
        else if (pos == 0) {
                p->prox = lst->prim;
				lst->prim->ant = p;
				lst->prim = p;
        }
        else if(pos == lst->tamanho-1) {
                p->ant = lst->ult;
				lst->ult->prox = p;
				lst->ult = p;
        }
        else {
				struct item_t *aux = lst->prim;
				for (int i = 0; i < pos; i++) 
						aux = aux->prox;
				p->prox = aux;
				p->ant = aux->ant;
				aux->ant->prox = p;
				aux->ant = p;
        }

				lst-> tamanho++;
				return lst->tamanho;
}
int lista_retira (struct lista_t *lst, int *item, int pos) {
	
		if (lst == NULL || lst->prim == NULL) 
				return -1;

		if (pos == -1) 
				pos = lst->tamanho-1;

		if (pos < 0 || pos >= lst->tamanho) 
				return -1;

        struct item_t *aux;
        aux = lst->prim;

        for (int i = 0 ; i< pos ; i++) 
				aux = aux->prox;

        *item = aux->valor;

		if (pos == 0) {
				lst->prim = aux->prox;
				if(lst->prim != NULL) 
						lst->prim->ant = NULL;
				else 
						lst->ult = NULL;
		}
		else if(pos == lst->tamanho-1) {
				lst->ult = aux->ant;
				if (lst->ult != NULL) 
						lst->ult->prox = NULL;
				else 
						lst->prim = NULL;
		}
		else {
				aux->ant->prox = aux->prox;
				if (aux->prox != NULL) 
						aux->prox->ant = aux->ant;
		}

		free(aux);

		lst->tamanho--;

		return lst->tamanho;
}

int lista_consulta (struct lista_t *lst, int *item, int pos) {

		if (lst == NULL || lst->prim == NULL) 
				return -1;
	
		struct item_t *aux;

		if (pos == -1) {
				aux = lst->ult;
				if (aux == NULL) 
						return -1;
		}
		else {
				if (pos < 0 || pos >= lst->tamanho) 
						return -1;
				aux = lst->prim;
				for (int i = 0 ; i<pos ; i++) 
						aux = aux->prox;
		}


		*item = aux->valor;

		return lst->tamanho;
}

int lista_procura (struct lista_t *lst, int valor) {

		if (lst == NULL || lst->prim == NULL) 
				return -1;

		struct item_t *aux;
		aux = lst->prim;
		int pos = 0;

		while (aux != NULL) {
				if (aux->valor == valor) 
						return pos;
			aux = aux->prox;
			pos++;
		}
	
		return -1;
}

int lista_tamanho (struct lista_t *lst) {

		if (lst == NULL) 
				return -1;
		return lst->tamanho;
}

void lista_imprime (struct lista_t *lst) {
	
		if (lst == NULL || lst->prim == NULL) 
				return;

		struct item_t *aux;
		aux = lst->prim;
		printf("%d", aux->valor);

		aux = aux->prox;
		while (aux != NULL) {
				printf(" %d", aux->valor);
				aux = aux->prox;
		}
}
