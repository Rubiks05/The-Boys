#ifndef ENTIDADES_H
#define ENTIDADES_H

#include <stdbool.h>
#include <stdlib.h>
#include "conjunto.h"
#include <math.h>

struct localizacao
{
        int x;
        int y;
};

struct Heroi
{
        int id_heroi;
        struct cjto_t *habilidade_heroi;
        int paciencia;
        int velocidade;
        int experiencia;
        int base_atual;
	int vivo;
};

struct Base
{
        int id_base;
        int lotacao;
        struct cjto_t *presentes;
        struct lista_t *espera;
        struct localizacao local_base;
	int lotacao_max;
	int participacao_missao;
};

struct Missao
{
        int id_missao;
        struct cjto_t *habilidade_missao;
        int perigo;
        struct localizacao local_missao;
	int cumprida;
	int tentativas;
};

struct Mundo
{
        int nherois;
        struct Heroi **herois;

        int nbases;
        struct Base **bases;

        int nmissoes;
        struct Missao **missoes;

        int nhabilidades;
        struct localizacao tamanhoMundo;
        int relogio;
	struct fprio_t *lef;

	int eventos_tratados;
	int missoes_cumpridas;
	int missoes_realizadas;
	int maior_tentativas;
	int tentativas;
};

#endif
