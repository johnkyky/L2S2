#ifndef __H_CMD__
#define __H_CMD__



struct cmd
{
	char* command;
	int argc;
	char** argv;
};


// Creation d un struct contenant la commande et les arguments
struct cmd cmd_init(char* command);

/// Destruction de la struct cmd
void cmd_fini(struct cmd* command);

///debug affichage de la structure 'struct cmd'
const void cmd_render(const struct cmd command);




#endif