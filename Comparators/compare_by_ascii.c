
#include "../ft_ls.h"

int				compare_by_ascii(void *a, void *b)
{
	return (
		ft_strcmp(((t_file *)a)->name, ((t_file *)b)->name));
}

int				reverse_compare_by_ascii(void *a, void *b)
{
	return (-(compare_by_ascii(a, b)));
}
