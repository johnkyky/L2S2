#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/cmd.h"

#define CMD_BUFFER	64



struct cmd cmd_init(char* command)
{
    struct cmd res;
    res.argc = 0;

    int i = 0;
    const char * separators = " ";

    char* strToken = strtok(command, separators);
	while(strToken)
    {
    	if(!i)
    	{
    		res.command = malloc(sizeof(char) * (strlen(strToken) + 1));
    		if(!res.command)
    		{
    			printf("ERROR MALLOC[init_cmd]\n");
    			exit(1);
    		}
    		strcpy(res.command, strToken);
    		i++;
    	}
    	else
    	{
            if(!res.argc)
	    	  res.argv = malloc(sizeof(char*));
            else
            {
                res.argv = realloc(res.argv, sizeof(char*) * (res.argc + 1));
            }
			if(!res.argv)
			{
				printf("ERROR MALLOC[init_cmd]\n");
				exit(1);
			}
            res.argv[res.argc] = malloc(sizeof(char) * (strlen(strToken) + 1));
			strcpy(res.argv[res.argc], strToken);
			
            res.argc ++;
		}
        strToken = strtok(NULL,separators);
    }

  	return res;
}


void cmd_fini(struct cmd* command)
{
    if(!command)
        return;

    free(command->command);

    if(command->argc)
    {
        for (int i = 0; i < command->argc; ++i)
        {
            free(command->argv[i]);
        }

        free(command->argv);
    }
}


const void cmd_render(const struct cmd command)
{
    printf("%s\n", command.command);
    printf("%d\n", command.argc);
    for (int i = 0; i < command.argc; ++i)
    {
        printf("%s\n", command.argv[i]);
    }
}


