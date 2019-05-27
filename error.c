
/*
**  Ft_ls -- Error Function(s).
*/

#include "Libft/Includes/libft.h"

void	usage(void)
{
	ft_printf("usage: ./ft_ls [ -Ralrt1 ] [ file ... ]\n");
	exit(EXIT_FAILURE);
}

void	error(void)
{
	perror(NULL);
	exit(EXIT_FAILURE);
}
