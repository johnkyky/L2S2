#include "regexp.h"
#include <string.h>
#include "PILEADERIV.h"

ADERIV nouvel_arbre(STATE s, char c){
	ADERIV a = malloc(sizeof(struct aderiv));
	if(!a) {printf("Plus de mémoire, malloc a échoué.\n"); exit(5);}
	a->s = s;
	a->caractere = c;
	a->fils[0] = NULL;
	a->fils[1] = NULL;
	a->fils[2] = NULL;
	return a;
}

void liberer_arbre(ADERIV a){
	if(a){
		for(int i = 0; i < 3; i++) liberer_arbre(a->fils[i]);
		free(a);
	}
}

//retourne l'indice correspondant au caractère dans le tableau des états
int indice_char(char c)
{
	switch(c){
		case '+': return 0;
		case '.': return 1;
		case '*': return 2;
		case '(': return 3;
		case ')': return 4;
		case '#': return 6;
		default:
			if( c >= 'a' && c <= 'z') return 5;
			printf("Caractère inconnu dans l'expression régulière.\n");
			exit(3);
	}
}

/// Fonction convertissant un char en un state
/// retourne un state correspondant au char
STATE char2State(char a)
{
	switch (a)
	{
		case '.' :
			return POINT;
		case '+' :
			return PLUS;
		case '(':
			return PARO;
		case ')':
			return PARF;
		case '*' :
			return ETOILE;
		default :
			return CAR;
	}
}

// Fonction convertissant un state en caractère
// retourne le caractère, sinon "?"
STATE state2car(STATE a)
{
	switch (a)
	{
		case PLUS :
			return '+';
		case POINT :
			return '.';
		case PARO:
			return '(';
		case PARF:
			return ')';
		case ETOILE :
			return '*';
		default:
			return '?';
	}
}

/// Fonction vérifiant que le mot est bien un mot de dyck
int mot_de_dyck(char* expr)
{
	int taille = strlen(expr);
	int nbr_par = 0;

	for (int i = 0; i < taille; i++)
	{
		if (expr[i] == '(')
			nbr_par++;
		if (expr[i] == ')')
			nbr_par--;
	}

	return nbr_par != 0;
}

ADERIV construire_arbre_derivation(char *expr){
	if (expr == NULL || mot_de_dyck(expr))
		return NULL;

	static STATELISTE table[7][7] = {//cette table représente la table des transitions de l'énoncé
		{{-1},{-1},{-1},{2,{A,B}},{-1},{2,{A,B}},{-1}}, // transition quand le STATE S est lu
		{{-1},{-1},{-1},{2,{C,D}},{-1},{2,{C,D}},{-1}},//STATE A
		{{3,{PLUS,A,B}},{-1},{-1},{-1},{0},{-1},{1,{CAR}}},//STATE B
		{{-1},{-1},{-1},{2,{E,F}},{-1},{2,{E,F}},{-1}},//STATE C
		{{0},{3,{POINT,C,D}},{-1},{-1},{0},{-1},{0}},//STATE D
		{{0},{0},{-1},{3,{PARO,S,PARF}},{-1},{1,{CAR}},{-1}},//STATE E
		{{0},{0},{1,{ETOILE}},{-1},{0},{-1},{0}}//STATE F
	};
	//Une STATELISTE de taille 0 correspond à une règle dont la production est epsilon.
	//Une STATELISTE de taille -1 correspond à une erreur (expression rejetée)
	

	/// Creation des variable, l'abre de dérivation res, la pile des transition p, 
	/// et la pile d'adresses d'ADERIV.
	ADERIV res = nouvel_arbre(S, 0);
	int index = 0;
	int taille = strlen(expr);
	PILE p = nouvelle_pile(taille * 3);
	PILEADERIV pn = NULL;

	/// On initilise les 2 pile avec le premier élement S
	pn = pAderiv_push(pn, res);
	p = empiler(p, S);

	// Tant que la pile de transition n'est pas vide et que le caractère courant est pas "#"
	while(!est_vide(p) && expr[index] != '#')
	{
		/// On depile le sommet de la pile de transition
		STATE s = depiler(&p);
		
		/// Si s correspond à un terminal
		if(s >= PLUS)
		{	
			/// Si le haut de la pile qu'on convertie en caractere est different du CAR
			if(state2car(pAderiv_peek(pn)->s) != expr[index] && pAderiv_peek(pn)->caractere != expr[index])
			{
				printf("[ERREUR] %c != %c, non reconnu !!!!!", pAderiv_peek(pn)->caractere, expr[index]);
				return liberer_arbre(res), liberer_pile(p), pAderiv_free(pn), NULL;
			}
			/// On depile le dernière élément de la pile et le caractère courant devient le suivant dans l'expression
			pAderiv_pop(&pn);
			index++;
			continue;
		}
		/// S n'est pas un terminal
		/// tmp correspond au state (abscisse de la table)
		STATE tmp = char2State(expr[index]);

		/// Si dans la tabl il n'y a pas de transition, alors on libère, l'expression n'est pas reconnu
		if (table[s][tmp - PLUS].taille == -1)
			return liberer_arbre(res), liberer_pile(p), pAderiv_free(pn), NULL;

		/// Sinon on récupère la feuille dans la pile d'adresse d'ADERIV
		ADERIV target_node = pAderiv_pop(&pn);

		/// Pour chaque element de la recette de la table de transition
		for (int i = table[s][tmp - PLUS].taille - 1; i > -1; i--)
		{
			/// On empile le resultat
			STATE to_add = table[s][tmp - PLUS].liste[i];
			p = empiler(p, to_add);
			/// On empile le nouveau noeud de l'arbre
			target_node->fils[i] = nouvel_arbre(to_add, 0);
			pn = pAderiv_push(pn, target_node->fils[i]);
			
			/// Si on ajoute un CAR on renseigne que c'est un caractère dans l'arbre
			if (to_add == CAR)
				target_node->fils[i]->caractere = expr[index];
		}
	}

	/// On libère la mémoire des piles
	pAderiv_free(pn);
	liberer_pile(p);
	
	printf("L'expression est reconnue : \n");
	return res;
}

void affiche_aderiv(ADERIV a, int space){//rendre joli
	//affiche les fils de gauche à droite
	if(a){
		affiche_aderiv(a->fils[2], space + 1);
		affiche_aderiv(a->fils[1], space + 1);
		for(int i = 0; i < space; i++) printf("   ");
		affiche_state(a->s);
		if(a->s == CAR) printf(" : %c",a->caractere);
		printf("\n");
	    affiche_aderiv(a->fils[0], space + 1);
	}
}