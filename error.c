/*
**  Ft_ls -- Error Function(s).
*/

#include "Libft/Includes/libft.h"

void	usage(void)
{
	ft_printf("usage: ./ft_ls [ -Ralrt1 ] [ file ... ]\n");
}

void	unknown_flag(char *unknown_flag)
{
	ft_printf("./ft_ls: illegal option -- %c\n", unknown_flag);
	usage();
}
