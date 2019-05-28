
/*
**  Ft_ls -- Flag Parser.
*/

#include "ft_ls.h"

// A_FLAG = (1 << 0),						We get more information / include in our expansion
// L_FLAG = (1 << 1),						We get more information
// R_FLAG = (1 << 2),						We change all our compare functions
// T_FLAG = (1 << 3),						Use the time_sort, or rev_time sort?
// F_FLAG = ((1 << 4) | A_FLAG),			Use ZERO return cmpfunction
// RR_FLAG = (1 << 5)						Used in the reccursive call

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
					break;
				}
			}
			if (g_flags[i].symbol == '\0')
				EXIT(unknown_flag((char *)(*(*av))[j]));
		}
		*av = *av + 1;
		*ac = *ac - 1;
	}
	return (flags);
}

void		*get_cmpft(uint64_t flags)
{
	int			(*cmpft)(void *, void *);
	(void)flags;
	cmpft = NULL;
	return (cmpft);
}
