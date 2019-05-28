
/*
**  Ft_ls -- Core Program.
*/

#include "ft_ls.h"

void	ft_listdir(const char dirname[PATHMAX], uint64_t flags,
			int (*cmpft)(void *, void *))
{
	t_vector	directory;
	size_t		i;

	directory = ft_getdirectory(dirname);
	if (directory.vector)
	{
		ft_quicksort(
			directory.vector, directory.length, sizeof(void *), cmpft);
		print_directories(directory, flags);
		if (flags & RR_FLAG)
		{
			i = 0;
			while (i < directory.length)
			{
				if (((t_file)directory.vector[i]).type == DIRECTORY)
					ls_call(state, directory.vector[i]);
				++i;
			}
		}
		vector.destructor(&directory);
	}
	return ;
}

/* TODO: aymen - implement the input into 3: errors, files & directories */

void	ft_ls(int ac, const char *av[], uint64_t flags,
			int (*cmpft)(void *, void *))
{
	if (av && *av)
	{

		/* do stuff */
	}
	else
		ls_call("./", flags, cmpft);
}
