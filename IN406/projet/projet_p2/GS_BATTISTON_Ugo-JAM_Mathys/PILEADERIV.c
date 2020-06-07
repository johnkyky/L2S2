#include "PILEADERIV.h"

PILEADERIV pAderiv_push(PILEADERIV n, ADERIV val)
{
    PILEADERIV tmp = malloc(sizeof(struct adrADERIV));
    tmp->val = val;
    tmp->next = n;
    return tmp;
}

ADERIV pAderiv_pop(PILEADERIV* n)
{
    if (n == NULL || *n == NULL)
        return NULL;
    ADERIV res = (*n)->val;
    PILEADERIV tmp = (*n);
    (*n) = (*n)->next;
    free(tmp);
    return res;
}

ADERIV pAderiv_peek(PILEADERIV n)
{
    return n->val;
}

void pAderiv_free(PILEADERIV n)
{
    PILEADERIV tmp;
    while (n)
    {
        tmp = n->next;
        free(n);
        n = tmp;
    }
}


void pAderiv_print(PILEADERIV n)
{
    if(!n)
        return;

    while(n)
    {
        if (!n->val)
            printf("%d ", n->val->s);
        else
            printf("NULL ");
        n = n->next;
    }
    printf("\n");
}