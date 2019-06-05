
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
	if (file.type == UNKNOWN_FILE)
		ft_printf("./ft_ls: %s: No such file or directory\n", file.name);
}

void			print_files(void *vector_element)
{
	t_file		file;

	if (!vector_element)
		return ;
	file = *(t_file *)vector_element;
	if (file.type != UNKNOWN_FILE && file.type != DIRECTORY)
		ft_printf("%s\n", file.name);
}

void			vprint_directories(void *vector_element, va_list ap)
{
	int			(*cmpft)(void *, void *);
	char		*parent_dir;
	uint64_t	flags;
	int			argc;
	t_file		file;

	if (!vector_element)
		return ;
	parent_dir = va_arg(ap, char *);
	flags = va_arg(ap, uint64_t);
	cmpft = va_arg(ap, int (*)(void *, void *));
	argc = va_arg(ap, int);
	file = *(t_file *)vector_element;
	if (file.type == DIRECTORY)
	{
		if (argc > 1)
			ft_printf("%s/%s:\n", parent_dir, file.name);
		ft_listdir(file.name, parent_dir, flags, cmpft);
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
