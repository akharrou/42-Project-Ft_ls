
#include "../ft_ls.h"

int		compare_by_time(void *a, void *b)
{
	long	res;

	res = ((t_file *)a)->modifi_time - ((t_file *)b)->modifi_time;
	if (res == 0)
		return (0);
	return ((res > 0) ? 1 : -1);
}

int		reverse_compare_by_time(void *a, void *b)
{
	return (-(compare_by_time(a, b)));
}
