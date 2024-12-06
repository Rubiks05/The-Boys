#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "lista.h"
#include "fprio.h"
#include "conjunto.h"
#include "entidades.h"
#include "funcoes_sec.h"
#include "cria_mundo.h"
#include "destroi_mundo.h"
#include "eventos.h"
#include "chamando_lef.h"

void chamando_lef(struct Mundo *mundo) {

        int continuar = 1;
        while (continuar && fprio_tamanho(mundo->lef) > 0) {
                int tipo, prio;
                void *item = fprio_retira(mundo->lef, &tipo, &prio);

                if (item == NULL) 
                        break;

                switch (tipo) {
                        case CHEGA:
                                funcao_evento_chega(mundo, item);
                                mundo->eventos_tratados += 1;
                                break;
                        case ESPERA:
                                funcao_evento_espera(mundo, item);
                                mundo->eventos_tratados += 1;
                                break;
                        case DESISTE:
                                funcao_evento_desiste(mundo, item);
                                mundo->eventos_tratados += 1;
                                break;
                        case AVISA:
                                funcao_evento_avisa(mundo, item);
                                mundo->eventos_tratados += 1;
                                break;
                        case ENTRA:
                                funcao_evento_entra(mundo, item);
                                mundo->eventos_tratados += 1;
                                break;
                        case SAI:
                                funcao_evento_sai(mundo, item);
                                mundo->eventos_tratados += 1;
                                break;
		        case VIAJA:
                                funcao_evento_viaja(mundo, item);
                                mundo->eventos_tratados += 1;
                                break;
                        case MORRE:
                                funcao_evento_morre(mundo, item);
                                mundo->eventos_tratados += 1;
                                break;
                        case MISSAO:
                                funcao_evento_missao(mundo, item);
                                mundo->eventos_tratados += 1;
                                break;
                        case FIM:
                                funcao_evento_fim(mundo, item);
                                continuar = 0;
                                break;
                }
                free(item);
        }
}
