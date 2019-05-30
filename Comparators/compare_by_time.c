
#include "../ft_ls.h"

int				compare_by_time(void *a, void *b)
{
	return (((t_file *)a)->time - ((t_file *)b)->time);
}

int				reverse_compare_by_time(void *a, void *b)
{
	return (-(compare_by_time(a, b)));
}
