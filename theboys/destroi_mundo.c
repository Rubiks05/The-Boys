#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lista.h"
#include "fprio.h"
#include "conjunto.h"
#include "entidades.h"
#include "funcoes_sec.h"

void destroi_mundo(struct Mundo *mundo)
{
		//destruindo os herois, de dentro para fora
		for (int i=0 ; i < mundo->nherois ; i++) {
				cjto_destroi(mundo->herois[i]->habilidade_heroi);
				free(mundo->herois[i]);
		}
		free(mundo->herois);

		//destruindo as bases, de dentro para fora
		for (int i=0 ; i < mundo->nbases ; i++) {
				cjto_destroi(mundo->bases[i]->presentes);
				lista_destroi(mundo->bases[i]->espera);
				free(mundo->bases[i]);
		}
		free(mundo->bases);

		//destruindo as missões, de dentro para fora
		for (int i=0 ; i < mundo->nmissoes ; i++) {
				jto_destroi(mundo->missoes[i]->habilidade_missao);
				free(mundo->missoes[i]);
		}
		free(mundo->missoes);
	
		fprio_destroi(mundo->lef);

		//dando free no mundo agora, por último.
		free(mundo);
}

