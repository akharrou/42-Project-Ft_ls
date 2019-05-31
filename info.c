
/*
**  Ft_ls -- Gather information about each file/directory
*/

#include "ft_ls.h"

t_vector	ft_getdirfiles()
{

}

t_vector	ft_getdirfiles(const char dirname[MAX_PATHLEN + 1])
{
	t_vector	dir;
	t_vector	dirfiles;

	dir = ft_getdirentries(dirname);
	dirfiles = vector.map(
		dir.vector, dir.length, sizeof(void *), &ft_getdirfile);
	/* create and fill in a t_file structure for each entry in the 'dir' vector and store it in a vector */
}
