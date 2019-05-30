
#include "../ft_ls.h"

int				compare_by_size(void *a, void *b)
{
	return (((t_file *)a)->size - ((t_file *)b)->size);
}

int				reverse_compare_by_size(void *a, void *b)
{
	return (-(compare_by_size(a, b)));
}
