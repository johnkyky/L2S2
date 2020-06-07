#pragma once
#include "regexp.h"

struct adrADERIV
{
    ADERIV val;
    struct adrADERIV* next;
};
typedef struct adrADERIV* PILEADERIV;

PILEADERIV pAderiv_push(PILEADERIV n, ADERIV val);
ADERIV pAderiv_pop(PILEADERIV* n);
ADERIV pAderiv_peek(PILEADERIV n);
void pAderiv_free();
void pAderiv_print(PILEADERIV n);
