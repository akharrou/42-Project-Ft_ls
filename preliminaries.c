
/*
**  Ft_ls -- Preliminaries.
*/

#include "ft_ls.h"

uint64_t		get_flags(int *argc, const char **argv[])
{
	uint64_t	flags;
	size_t		i;
	size_t		j;
	size_t		k;

	flags = 0;
	i = -1;
	while ((*argv)[++i] && (*argv)[i][0] == '-' && (*argv)[i][1] != '\0')
	{
		j = 0;
		while ((*argv)[i][++j] != '\0')
		{
			k = -1;
			while (g_flags[++k].symbol != '\0')
				if ((*argv)[i][j] == g_flags[k].symbol)
				{
					flags |= g_flags[k].value;
					break ;
				}
			if (g_flags[k].symbol == '\0')
				EXIT(unknown_flag((*argv)[i][j]));
		}
	}
	(*argc) -= i;
	return (flags);
}

void			*get_cmpft(uint64_t flags)
{
	int			(*cmpft)(void *, void *);
	size_t		i;

	i = 0;
	cmpft = &compare_by_ascii;
	if (flags & SORT_FLAG)
	{
		while (g_flags[i].symbol != '\0')
		{
			if (flags & g_flags[i].value)
			{
				cmpft = (flags & R_FLAG) ?
					g_flags[i].reverse_cmp_function :
					g_flags[i].cmp_function;
				break ;
			}
			++i;
		}
	}
	return ((void *)cmpft);
}
