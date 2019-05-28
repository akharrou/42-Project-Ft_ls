
/*
**  Ft_ls -- Preliminaries.
*/

#include "ft_ls.h"

uint64_t		get_flags(int *ac, const char **av[])
{
	uint64_t	flags;
	size_t		i;
	size_t		j;

	flags = 0;
	while (*(*av) && (*(*av))[0] == '-')
	{
		i = 1;
		while ((*(*av))[i] != '\0')
		{
			j = 0;
			while (g_flags[j].symbol != '\0')
				if ((*(*av))[i] == g_flags[j].symbol)
				{
					flags |= g_flags[j].value;
					break ;
				}
			if (g_flags[i].symbol == '\0')
				EXIT(unknown_flag((char *)(*(*av))[j]));
		}
		(*av) += 1;
		(*ac) -= 1;
	}
	return (flags);
}

void			*get_cmpft(uint64_t flags)
{
	int			(*cmpft)(void *, void *);

	cmpft = NULL;
	(void)flags;
	return (cmpft);
}
