#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "atlacan.h"
#include <unistd.h>


void find(const int distance)
{
	int buffer_distance = distance;
	char** buffer_ls;
	int nbr_ls;

	if(atl_ls(&buffer_ls, &nbr_ls))
		return;

	//for (int i = 0; i < nbr_ls; ++i)
	//	printf("%s\n", buffer_ls[i]);
	
	for (int i = 0; i < nbr_ls; ++i)
	{
		struct atl_stat stats;
		if(atl_stat(buffer_ls[i], &stats))
			return;
		
		if(atl_is_dir(stats.mode) && !(stats.uid == UID_CLAYTON))
		{
			if(distance < buffer_distance && buffer_distance != -1)
				return;
			if(atl_cd(buffer_ls[i]))
				return;
			find(buffer_distance);
			if(atl_cd(".."))
				exit(1);
		}
		else if(atl_is_file(stats.mode) && !(stats.gid == GID_PERTONTAN))
		{
			if(atl_cat(buffer_ls[i], &buffer_distance))
				return;
		}
	}
	atl_free_ls(buffer_ls, nbr_ls);
}





int main()
{
	atl_init();
	
	find(-1);

	atl_fini();

	return 0;
}