
/*
**  Utility Function(s).
*/

#include "ft_ls.h"

/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
** These serve the vector iter() & viter() methods in the ft_ls() function.
*/

void			print_errors(void *vector_element)
{
	t_file		file;

	if (!vector_element)
		return ;
	file = *(t_file *)vector_element;
	if (file.type == UNKNOWN)
		ft_printf("./ft_ls: %s: No such file or directory\n", file.name);
}

void			print_files(void *vector_element)
{
	t_file		file;

	if (!vector_element)
		return ;
	file = *(t_file *)vector_element;
	if (file.type != UNKNOWN && file.type != DIRECTORY)
		ft_printf("%s\n", file.name);
}

void			vprint_directories(void *vector_element, va_list ap)
{
	int			(*cmpft)(void *, void *);
	t_file		file;
	uint64_t	flags;
	int			argc;

	if (!vector_element)
		return ;
	argc = va_arg(ap, int);
	flags = va_arg(ap, uint64_t);
	cmpft = va_arg(ap, int (*)(void *, void *));
	file = *(t_file *)vector_element;
	if (file.type == DIRECTORY)
	{
		if (argc > 1)
			ft_printf("%s:\n", file.name);
		ft_listdir(file.name, flags, cmpft);
	}
}

/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
** This serves the vector viter() method in the ft_printdir() function.
*/

void			ft_vprintfile(void *vector_element, va_list ap)
{
	int			size_width;
	int			links_width;
	uint64_t	flags;

	if (!vector_element)
		return ;
	flags = va_arg(ap, uint64_t);
	links_width = va_arg(ap, int);
	size_width = va_arg(ap, int);
	ft_printfile(*(t_file *)vector_element, flags, links_width, size_width);
}

/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
*/
