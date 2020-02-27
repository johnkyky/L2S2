#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/cmd.h"

#define ACTION_SIZE 16
#define WORD_SIZE   48


/////////////////////////////////////////////////////////////////////////////////


///Defines a lexicon.
struct word
{
	char* word;
	struct word* next_word;
};
struct lexc {
    char* name;
    struct word* first_word;
    size_t number;
    int modifiable;
};


/////////////////////////////////////////////////////////////////////////////////

struct cell
{
	struct lexc *lexc;
	struct cell* next_cell;
};


struct vector
{
	size_t size;
	struct cell* first_cell;
};


/////////////////////////////////////////////////////////////////////////////////


/**
 * Initializes a lexicon data structure.
 * 
 * The lexicon must be freed using the lexc_fini() function.
 *
 * @param[in]  name             Lexicon name.
 * @param[in]  mutable          TRUE if the lexicon is mutable.
 *
 * @return     New lexicon.
 */
struct lexc *lexc_init(const char *name, const int mutable)
{
    struct lexc* res = malloc(sizeof(struct lexc));

    if(!res)
    {
    	printf("ERROR MALLOC[lexc_init]\n");
    	exit(1);
    }
    
    res->name = malloc(sizeof(char) * (strlen(name)+ 1));
    if(!res->name)
    {
    	printf("ERROR MALLOC[lexc_init]\n");
    }
	strcpy(res->name,name);
    res->first_word = NULL;
    res->number = 0;
    res->modifiable = mutable;

    return res;
}


/**
 * Releases a lexicon data structure.
 *
 * @param[in]      lexc             Lexicon to release.
 */
void lexc_fini(struct lexc **lexc)
{
	if(!*lexc)
		return;

	free((*lexc)->name);
	
	while((*lexc)->first_word)
	{
		struct word* buffer = (*lexc)->first_word;
		(*lexc)->first_word = (*lexc)->first_word->next_word;
		free(buffer->word);
		free(buffer);
	}

	free(*lexc);
	*lexc = NULL;
}


/**
 * Check the lexicon to find a word 
 *
 * @param[in]      lexc             Lexicon to release.
 *
 * @return 1 fail 0 else
 */
int lexc_check(struct lexc *lexc, const char *word)
{
	if(!lexc || !lexc->first_word)
		return 1;

	struct word* buffer = lexc->first_word;


	while(strcmp(buffer->word, word))
	{
		if(!buffer->next_word)
			return 1;
		buffer = buffer->next_word;
	}

    return 0;
}


/**
 * Add a word in data structure.
 *
 * @param      lexc             Lexicon to add word.
 * @param      word             word to add in the lexicon.
 *
 * @return 1 fail 0 else
 */
int lexc_add(struct lexc *lexc, const char *word)
{
	if(!lexc)
		return 1;

	if(!lexc_check(lexc, word))
		return 1;

	lexc->number++;

	struct word* res = malloc(sizeof(struct word));
	if(!res)
		return 1;

	res->word = malloc(sizeof(char) * (strlen(word) + 1));
	if(!res->word)
    {
    	printf("ERROR MALLOC[lexc_add]\n");
    	exit(1);
    }

	strcpy(res->word, word);
	res->next_word = NULL;

	if(!lexc->first_word)
		lexc->first_word = res;
	else
	{
		struct word* buffer = lexc->first_word;

		while(buffer->next_word)
			buffer = buffer->next_word;

		buffer->next_word = res;
	}
    return 0;
}


/**
 * Remove a word in data structure.
 *
 * @param      lexc             Lexicon to remove word.
 * @param      word             word to remove in the lexicon.
 *
 * @return 1 fail 0 else
 */
int lexc_remove(struct lexc *lexc, const char *word)
{
	if(!lexc || !lexc->first_word)
		return 1;

	struct word* buffer = lexc->first_word;

	if(!strcmp(buffer->word, word))
	{
		lexc->first_word = lexc->first_word->next_word;
		free(buffer->word);
		free(buffer);
		lexc->number--;
		return 0;
	}

	while(buffer->next_word && strcmp(buffer->next_word->word, word))
	{
		buffer = buffer->next_word;
	}

	if(!buffer->next_word)
		return 1;

	struct word* supp = buffer->next_word;
	buffer->next_word = buffer->next_word->next_word;
	free(supp->word);
	free(supp);

	lexc->number--;
    return 0;
}


/**
 * Show a lexicon.
 *
 * @param      lexc             Lexicon to show.
 */
void lexc_render(struct lexc *lexc)
{
	if(!lexc)
		return;

	printf("\t> lexc->name = '%s'\n", lexc->name);
	printf("\t> lexc->number = %ld\n", lexc->number);
	printf("\t> lexc->modifiable = %hd\n", lexc->modifiable);

	if(!lexc->first_word)
	{
		printf("\t> lexc->word = empty\n");
		return;
	}

	printf("\t> lexc->word = {");
	struct word* buffer = lexc->first_word;

	while(buffer)
	{
		printf(" %s ", buffer->word);
		buffer = buffer->next_word;
	}

	printf("}\n");
}


/////////////////////////////////////////////////////////////////////////////////



struct vector* vector_init()
{
	struct vector* res = malloc(sizeof(struct vector));
	if(!res)
    {
    	printf("ERROR MALLOC[vector_init]\n");
    	exit(1);
    }

    res->size = 0;
    res->first_cell = NULL;

    return res;
}

void vector_fini(struct vector **vector)
{
	if(!(*vector))
		return;

	while((*vector)->first_cell)
	{
		struct cell* buffer = (*vector)->first_cell;

		(*vector)->first_cell = buffer->next_cell;

		lexc_fini(&buffer->lexc);
		free(buffer);
	}
}

int vector_check(struct vector *vector, const char *name, struct lexc **lexc)
{
	if(!vector)
		return 1;

	struct cell* buffer = vector->first_cell;

	while(buffer)
	{
		if(!strcmp(buffer->lexc->name, name))
		{
			*lexc = buffer->lexc;
			return 0;
		}
		buffer = buffer->next_cell;
	}

	return 1;
}

int vector_add(struct vector *vector, const char *name, const int mutable)
{
	if(!vector)
		return 1;

	struct cell* res = malloc(sizeof(struct cell));
	if(!res)
    {
    	printf("ERROR MALLOC[vector_add]\n");
    	exit(1);
    }
    res->lexc = lexc_init(name, mutable);
    res->next_cell = NULL;

    if(!vector->first_cell)
    	vector->first_cell = res;
    else
    {
		struct cell* buffer = vector->first_cell;

	    while(buffer->next_cell)
	    	buffer = buffer->next_cell;

    	buffer->next_cell = res;
	}

	vector->size++;

	return 0;
}

int vector_remove(struct vector *vector, const char *name)
{
	if(!vector || !vector->first_cell)
		return 1;

	struct cell* buffer = vector->first_cell;

	if(!strcmp(buffer->lexc->name, name))
	{
		vector->first_cell = vector->first_cell->next_cell;
		lexc_fini(&buffer->lexc);
		free(buffer);
		vector->size--;
		return 0;
	}

	while(buffer->next_cell && strcmp(buffer->next_cell->lexc->name, name))
	{
		buffer = buffer->next_cell;
	}

	if(!buffer->next_cell)
		return 1;

	struct cell* supp = buffer->next_cell;
	buffer->next_cell = buffer->next_cell->next_cell;
	lexc_fini(&supp->lexc);
	free(supp);

	return 0;
}

void vector_render(struct vector *vector)
{
	if(!vector)
		exit(1);

	if(!vector->size)
		printf("\t> empty\n");
	else
	{
		struct cell* buffer = vector->first_cell;

		while(buffer)
		{
			printf("\t> name : %s\n", buffer->lexc->name);
			buffer = buffer->next_cell;
		}
	}
}


/////////////////////////////////////////////////////////////////////////////////

/**
 * Make terminal command
 *
 * @param      lexc            Lexicon variable.
 * @param      cmd             cmd with command.
 */
short cmd_interpret(struct vector **vector, struct lexc **lexc, const struct cmd cmd)
{	
	if(!strcmp(cmd.command, "exit"))
	{
		if(cmd.argc)
		{
			printf("too much arguments\n");
			return 0;
		}
		lexc_fini(lexc);
		vector_fini(vector);
		return 1;
	}
	else if(!strcmp(cmd.command, "help"))////a modifier
	{
		if(cmd.argc)
			printf("too much arguments\n");
		else
			printf("list of command : \n\t> help\n\t> exit\n\t> add\n\t> rm\n\t> check\n\t> show\n");
		return 0;
	}
	else if(!strcmp(cmd.command, "mklexc"))
	{
		if(!cmd.argc)
			printf("mettre les bon arguments\n");
		else
			vector_add(*vector, cmd.argv[0], 1);
		return 0;
	}
	else if(!strcmp(cmd.command, "rmlexc"))
	{
		if(!cmd.argc)
			printf("mettre des arguments\n");
		else
		{
			for(int i = 0; i < cmd.argc; ++i)
				if(vector_remove(*vector, cmd.argv[i]))
					printf("lexc '%s' not found\n", cmd.argv[i]);
		}
		return 0;
	}
	else if(!strcmp(cmd.command, "checklexc"))
	{
		if(cmd.argc == 0)
			printf("mettre des arguments\n");	
		else
		{
			for (int i = 0; i < cmd.argc; ++i)
			{
				struct lexc* buffer = NULL;
				if(!vector_check(*vector, cmd.argv[i], &buffer))
					printf("lexc '%s' found\n", cmd.argv[i]);
				else
					printf("lexc '%s' not found\n", cmd.argv[i]);
			}
		}

		return 0;
	}
	else if(!strcmp(cmd.command, "add"))
	{
		if(cmd.argc < 2)
			printf("mettre les bon arguments\n"); 
		else
		{
			struct lexc* buffer = NULL;
			if(vector_check(*vector, cmd.argv[0], &buffer))
				printf("lexique '%s' not found\n", cmd.argv[0]);
			else
			{
				for (int i = 1; i < cmd.argc; ++i)
				{
					if(lexc_add(buffer, cmd.argv[i]))
						printf("'%s' deja existant\n", cmd.argv[i]);
				}
			}
		}
		return 0;
	}
	else if(!strcmp(cmd.command, "rm"))
	{
		if(cmd.argc < 2)
			printf("mettre les bon arguments\n"); 
		else
		{
			struct lexc* buffer = NULL;
			if(vector_check(*vector, cmd.argv[0], &buffer))
				printf("lexique '%s' not found\n", cmd.argv[0]);
			else
			{
				for (int i = 1; i < cmd.argc; ++i)
				{
					if(lexc_remove(buffer, cmd.argv[i]))
						printf("'%s' not found\n", cmd.argv[i]);
				}
			}
		}
		return 0;
	}
	else if(!strcmp(cmd.command, "ls"))
	{
		if(!cmd.argc)
			vector_render(*vector);
		else
		{
			for (int i = 0; i < cmd.argc; ++i)
			{
				struct lexc* buffer = NULL;
				if(vector_check(*vector, cmd.argv[i], &buffer))
					printf("lexique '%s' not found\n", cmd.argv[i]);
				else
					lexc_render(buffer);
				if(i != cmd.argc - 1)
					printf("\n");
			}
		}
		
		return 0;
	}
	else if(!strcmp(cmd.command, "check"))
	{
		if(cmd.argc < 2)
			printf("mettre des arguments\n");
		else
		{
			struct lexc* buffer = NULL;
			if(vector_check(*vector, cmd.argv[0], &buffer))
				printf("lexique '%s' not found\n", cmd.argv[0]);
			else
			{
				for (int i = 1; i < cmd.argc; ++i)
				{
					if(lexc_check(buffer, cmd.argv[i]))
						printf("'%s' not found\n", cmd.argv[i]);
					else
						printf("'%s' found\n", cmd.argv[i]);
				}
			}
		}
		return 0;
	}
	else
		printf("command unknown\n");

	return 0;
}