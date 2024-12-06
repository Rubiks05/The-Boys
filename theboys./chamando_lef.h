#ifndef CHAMANDO_LEF_H
#define CHAMANDO_LEF_H

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

void chamando_lef(struct Mundo *mundo);

#endif
