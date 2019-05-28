
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
			{
				if ((*(*av))[i] == g_flags[j].symbol)
				{
					flags |= g_flags[j].value;
					break ;
				}
				j++;
			}
			if (g_flags[j].symbol == '\0')
				EXIT(unknown_flag((*(*av))[i]));
			i++;
		}
		(*av) += 1;
		(*ac) -= 1;
	}
	ft_printf("%ld\n", flags);
	return (flags);
}

void			*get_cmpft(uint64_t flags)
{
	int			(*cmpft)(void *, void *);
	size_t		i;

	i = 0;
	cmpft = &sort_by_ascii;
	if (flags & SORT_FLAG)
		while (g_flags[i].symbol != 0)
		{
			if (flags & g_flags[i].value)
			{
				if (flags & R_FLAG)
					cmpft = g_flags[i].rev_cmp_funct;
				else
					cmpft = g_flags[i].cmp_funct;
				break ;
			}
			i++;
		}
	return (cmpft);
}
