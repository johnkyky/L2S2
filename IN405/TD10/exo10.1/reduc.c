#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

// Enumération des différents opérateurs possibles
typedef enum {
	OCD_SOMME,
	OCD_MOYENNE,
	OCD_MAX,
	OCD_MIN,
	OCD_TOTAL
} opcode_t;

// Structure contenant les arguments du programme
typedef struct {
	int nbThreads;			//< Nombre de threads à utiliser
	int tailleTableau;		//< Taille du tableau utilisé pour la réduction
	opcode_t code;			//< Opération à réaliser
} arg_t;

// Structure contenant les informations nécessaires au thread
typedef struct {
	int* tab;						//< Tableau d'entiers à traiter
	int i_start;					//< Indice de début de traitement
	int i_end;						//< Indice de fin de traitement (non compris)
	int result;						//< Résultat local
	//exo9.3
	int* global_res;				//< Second resultat gobal dans chaque message
	pthread_mutex_t* mutex;			//< Mutex afin de proteger la var res
} message_t;

// Alias de pointeurs de fonction
typedef int (* ptrVerif) (int *, int, int);

// Fonction thread -- calcule la somme locale d'un tableau
// \param	arg 			Message transmis par le thread père
// \return					NULL
void * sommeTableau (void * arg)
{
	message_t* mess = (message_t*) arg;

	int buffer = 0;
	for(int i = mess->i_start; i < mess->i_end; i++)
		buffer += mess->tab[i];

	mess->result = buffer;

	//exo9.3
	pthread_mutex_lock(mess->mutex);
	*(mess->global_res) += buffer;
	pthread_mutex_unlock(mess->mutex);

	return NULL;
}

// Fin de la réduction -- calcule la somme globale
// \param	msg				Messages issus de l'exécution des threads,
//							contiennent les résultats locaux
// \param	nbThreads		Nombre de threads, et donc de messages
// \return					Résultat global
int reducSomme (message_t * msg, int nbThreads)
{
	int res = 0;
	for(int i = 0; i < nbThreads; i++)
		res += msg[i].result;
	return res;
}

// Fonction thread -- calcule la moyenne locale d'un tableau
// \param	arg 			Message transmis par le thread père
// \return					NULL
void * moyenneTableau (void * arg)
{
	message_t* mess = (message_t*) arg;

	int buffer = 0;
	for(int i = mess->i_start; i < mess->i_end; i++)
		buffer += mess->tab[i];

	int moyenne = buffer / (mess->i_end - mess->i_start);
	mess->result = moyenne;

	//exo9.3
	pthread_mutex_lock(mess->mutex);
	if(*(mess->global_res) != 0)
		*(mess->global_res) = (moyenne + *(mess->global_res)) / 2;
	else
		*(mess->global_res) = moyenne;
	pthread_mutex_unlock(mess->mutex);

	return NULL;
}

// Fin de la réduction -- calcule la moyenne globale
// \param	msg				Messages issus de l'exécution des threads,
//							contiennent les résultats locaux
// \param	nbThreads		Nombre de threads, et donc de messages
// \return					Résultat global
int reducMoyenne (message_t* msg, int nbThreads)
{
	int res = 0;
	for(int i = 0; i < nbThreads; i++)
		res += msg[i].result;

	res /= nbThreads;
	
	return res;
}

// Fonction thread -- calcule le maximum local d'un tableau
// \param	arg 			Message transmis par le thread père
// \return					NULL
void* maxTableau (void * arg)
{
	message_t* mess = (message_t*) arg;

	int max = mess->tab[mess->i_start];
	for(int i = mess->i_start; i < mess->i_end; i++)
	{
		if(max < mess->tab[i])
			max = mess->tab[i];
	}

	mess->result = max;

	//exo9.3
	if(*(mess->global_res) < max)
	{
		pthread_mutex_lock(mess->mutex);
		*(mess->global_res) = max;
		pthread_mutex_unlock(mess->mutex);
	}

	return NULL;
}

// Fin de la réduction -- calcule le maximum global
// \param	msg				Messages issus de l'exécution des threads,
//							contiennent les résultats locaux
// \param	nbThreads		Nombre de threads, et donc de messages
// \return					Résultat global
int reducMax (message_t * msg, int nbThreads) 
{
	int max = msg[0].result;
	for(int i = 0; i < nbThreads; i++)
		if(max < msg[i].result)
			max = msg[i].result;


	return max;
}

// Fonction thread -- calcule le minimum local d'un tableau
// \param	arg 			Message transmis par le thread père
// \return					NULL
void * minTableau (void * arg)
{
	message_t* mess = (message_t*) arg;

	int min = mess->tab[mess->i_start];
	for(int i = mess->i_start; i < mess->i_end; i++)
	{
		if(min > mess->tab[i])
			min = mess->tab[i];
	}

	mess->result = min;

	//exo9.3
	if(*(mess->global_res) > min || *(mess->global_res) == 0)
	{
		pthread_mutex_lock(mess->mutex);
		*(mess->global_res) = min;
		pthread_mutex_unlock(mess->mutex);
	}

	return NULL;
}

// Fin de la réduction -- calcule le minimum global
// \param	msg				Messages issus de l'exécution des threads,
//							contiennent les résultats locaux
// \param	nbThreads		Nombre de threads, et donc de messages
// \return					Résultat global
int reducMin (message_t * msg, int nbThreads)
{
	int min = msg[0].result;
	for(int i = 0; i < nbThreads; i++)
		if(min > msg[i].result)
			min = msg[i].result;


	return min;
}

// NE PAS TOUCHER
// Fonction de vérification -- somme des éléments du tableau
// \param	tableau			Tableau d'entiers
// \param	tailleTableau	Taille du tableau d'entiers
// \param	resultat		Résultat obtenu par la réduction
// \return					VRAI si le résultat est juste, FAUX sinon
int verifSomme (int * tableau, int tailleTableau, int resultat) {
	int i, tmp = 0;

	for (i = 0; i < tailleTableau; ++i)
		tmp += tableau [i];

	return resultat == tmp;
}

// NE PAS TOUCHER
// Fonction de vérification -- moyenne des éléments du tableau
// \param	tableau			Tableau d'entiers
// \param	tailleTableau	Taille du tableau d'entiers
// \param	resultat		Résultat obtenu par la réduction
// \return					VRAI si le résultat est juste, FAUX sinon
int verifMoyenne (int * tableau, int tailleTableau, int resultat) {
	int i, tmp = 0;

	if (tailleTableau == 0)
		return resultat == 0;

	for (i = 0; i < tailleTableau; ++i)
		tmp += tableau [i];

	return resultat == (tmp / tailleTableau);
}

// NE PAS TOUCHER
// Fonction de vérification -- maximum du tableau
// \param	tableau			Tableau d'entiers
// \param	tailleTableau	Taille du tableau d'entiers
// \param	resultat		Résultat obtenu par la réduction
// \return					VRAI si le résultat est juste, FAUX sinon
int verifMax (int * tableau, int tailleTableau, int resultat) {
	int i, tmp = 0;

	for (i = 0; i < tailleTableau; ++i)
		tmp = (tmp < tableau [i] ? tableau [i] : tmp);

	return resultat == tmp;
}

// NE PAS TOUCHER
// Fonction de vérification -- minimum du tableau
// \param	tableau			Tableau d'entiers
// \param	tailleTableau	Taille du tableau d'entiers
// \param	resultat		Résultat obtenu par la réduction
// \return					VRAI si le résultat est juste, FAUX sinon
int verifMin (int * tableau, int tailleTableau, int resultat) {
	int i, tmp = 101;

	for (i = 0; i < tailleTableau; ++i)
		tmp = (tmp > tableau [i] ? tableau [i] : tmp);

	return resultat == tmp;
}

// Analyse des arguments du programme. Quitte si le nombre d'arguments est
// différent de 4. Remplit la structure de données des arguments.
// \param	argc			Nombre d'arguments
// \param	argv			Arguments
// \return					Structure de données des arguments
arg_t analyseArguments (int argc, char ** argv)
{
	int opt;
	int nbThreads = 4, tailleTableau = -1;
	char code = 'A';	
    while ((opt = getopt(argc, argv, "t::s:o:")) != -1)
    {
        switch (opt)
        {
	        case 't':
	        	if(optarg)
	            	nbThreads = atoi(optarg);
	            break;
	        case 's':
				tailleTableau = atoi(optarg);
	            break;
	        case 'o':
	            code = *optarg;
	            break;
	        default:
	            fprintf(stderr, "%s [-t number threads]=4 [-s size of array] [-o optocode]\n", argv[0]);
	    }
    }
    
    if(tailleTableau < 1 || code == 'A' || nbThreads < 1)
    {
    	fprintf(stderr, "%s [-t number threads]=4 [-s size of array] [-o optocode]\n", argv[0]);
    	exit(1);
    }

	arg_t res;
	res.nbThreads = nbThreads;
	res.tailleTableau = tailleTableau;
	switch(code)
	{
		case '+':
			res.code = OCD_SOMME;
			break;
		case '/':
			res.code = OCD_MOYENNE;
			break;
		case 'M':
			res.code = OCD_MAX;
			break;
		case 'm':
			res.code = OCD_MIN;
			break;
		default:
			fprintf(stderr, "%s [-t number threads]=4 [-s size of array] [-o optocode]\n", argv[0]);
			exit(1);
			break;
	}	

	return res;
}

// NE PAS TOUCHER
// Récupération de la fonction de vérification à partir de l'opcode
// \param	opcode 			Code de l'opération
// \return					Pointeur de la fonction de vérification
ptrVerif decodeOpcodeVerif (const opcode_t o) {
	switch (o) {
		case OCD_SOMME:		return verifSomme;
		case OCD_MOYENNE:	return verifMoyenne;
		case OCD_MAX:		return verifMax;
		case OCD_MIN:		return verifMin;
		default:
			printf ("L'opération n'a pas été reconnue\n");
			exit (-1);
	}
}

// Génération du tableau avec des entiers compris entre 1 et 100.
// \param	tailleTableau	Taille du tableau d'entiers
// \return					Tableau d'entiers
int* genereTableau (int tailleTableau)
{
	int* tab = malloc(sizeof(int) * tailleTableau);
	for(int i = 0; i < tailleTableau; i++)
		tab[i] = 1;//rand() % 100 + 1;

	return tab;
}

// Fonction chargée de la réduction multi-threadé, elle va initialiser les
// différentes variables utilisées par les threads (tableau d'entier, messages,
// etc.) puis créer les threads. Une fois l'exécution des threads terminée et
// la réduction opérée, la vérification du résultat est faite.
// \param	arg 			Arguments du programme décodés
void programmePrincipal (arg_t arg)
{
	// Déclaration des variables
	int* tab = genereTableau(arg.tailleTableau);
	int res = 0;
	pthread_t tid[arg.nbThreads];
	message_t tabl_message[arg.nbThreads];

	//global result with mutex
	int global_result = 0;
	pthread_mutex_t mutex;
	pthread_mutex_init(&mutex, NULL);


	for(int i = 0; i < arg.nbThreads; i++)
	{
		tabl_message[i].tab = tab;
		tabl_message[i].i_start = i * (arg.tailleTableau / arg.nbThreads);
		tabl_message[i].i_end = (i + 1) * (arg.tailleTableau / arg.nbThreads);
		tabl_message[i].result = 0;
		tabl_message[i].global_res = &global_result;
		tabl_message[i].mutex = &mutex;
	}
	tabl_message[arg.nbThreads - 1].i_end = arg.tailleTableau;

	switch(arg.code)
	{
		case(OCD_SOMME):
		{
			for(int i = 0; i < arg.nbThreads; i++)
				pthread_create(&tid[i], NULL, sommeTableau, &tabl_message[i]);
			break;
		}
		case(OCD_MOYENNE):
		{
			for(int i = 0; i < arg.nbThreads; i++)
				pthread_create(&tid[i], NULL, moyenneTableau, &tabl_message[i]);
			break;
		}
		case(OCD_MAX):
		{
			for(int i = 0; i < arg.nbThreads; i++)
				pthread_create(&tid[i], NULL, maxTableau, &tabl_message[i]);
			break;
		}
		case(OCD_MIN):
		{
			for(int i = 0; i < arg.nbThreads; i++)
				pthread_create(&tid[i], NULL, minTableau, &tabl_message[i]);
			break;
		}
		default:
			break;
	}
	
	for(int i = 0; i < arg.nbThreads; i++)
		pthread_join(tid[i], NULL);

	switch(arg.code)
	{
		case(OCD_SOMME):
		{
			res = reducSomme(tabl_message, arg.nbThreads);
			break;
		}
		case(OCD_MOYENNE):
		{
			res = reducMoyenne(tabl_message, arg.nbThreads);
			break;
		}
		case(OCD_MAX):
		{
			res = reducMax(tabl_message, arg.nbThreads);
			break;
		}
		case(OCD_MIN):
		{
			res = reducMin(tabl_message, arg.nbThreads);
			break;
		}
		default:
			break;
	}
	printf("sous gros test %d -> %d\n", global_result, res);

	// NE PAS TOUCHER
	if ( (* (decodeOpcodeVerif (arg.code) ) ) (tab, arg.tailleTableau, res) )
		printf ("Le resultat est juste pour l'exo9.2\n");
	else printf ("Le resultat est faux pour l'exo9.2\n");
	if(global_result == res) printf ("Le resultat est juste pour l'exo9.3\n");
	else printf ("Le resultat est faux pour l'exo9.3\n");
	// FIN
	
	// Libération de la mémoire
	free(tab);
	pthread_mutex_destroy(&mutex);
}

// NE PAS TOUCHER
// Fonction main -- analyse les arguments donnés au
// programme, puis exécute le programme principal, chargé de la réduction
// multi-threadée.
// \param	argc			Nombre d'arguments
// \param	argv			Arguments
// \return					Code de retour du programme (0 en cas de réussite)
int main (int argc, char ** argv)
{
	arg_t a;

	srand (time (NULL));

	a = analyseArguments (argc, argv);
	programmePrincipal(a);
	
	return 0;
}
