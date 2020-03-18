#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "atlacan.h"



void atl_find(const int distance)
{
	int buffer_distance = distance;
	char** buffer_ls;
	int nbr_ls;

	if(atl_ls(&buffer_ls, &nbr_ls))
		return;
	
	///Parse the entire directory	
	for (int i = 0; i < nbr_ls; ++i)
	{
		struct atl_stat stats;
		if(atl_stat(buffer_ls[i], &stats))
			return;
		
		///Is a valid directory
		if(atl_is_dir(stats.mode) && !(stats.uid == UID_CLAYTON))
		{
			/// (buffer_distance != -1) for the first recursion
			if(distance < buffer_distance && buffer_distance != -1)
				return;
			if(atl_cd(buffer_ls[i]))
				return;
			atl_find(buffer_distance);
			if(atl_cd(".."))
				exit(1);
		}
		///Is a valid file
		else if(atl_is_file(stats.mode) && !(stats.gid == GID_PERTONTAN))
			if(atl_cat(buffer_ls[i], &buffer_distance))
				return;
	}
	atl_free_ls(buffer_ls, nbr_ls);
}


int main()
{
	atl_init();
	atl_find(-1);
	atl_fini();

	return 0;
}