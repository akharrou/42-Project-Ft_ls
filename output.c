
/*
**  Ft_ls -- Output
*/

#include "ft_ls.h"

void		ft_printfile(t_file file, uint64_t flags,
				int links_width, int size_width)
{
	if (!(flags & A_FLAG))
		if ((ft_strcmp(file.name, ".") == 0 || ft_strcmp(file.name, "..") == 0))
			return ;
	if (flags & L_FLAG)
		ft_printf("%11s %*i %s  %s  %*i %3s %2i %2i:%2i %s",
			file.mode,
			links_width, file.links,
			file.owner, file.group,
			size_width, file.size,
			file.month, file.day, file.hour, file.minute, file.second,
			file.name);
	else
		ft_putstr(file.name);
	if (file.type == SYMBOLIC_LINK)
		ft_printf(" -> %s", file.linked_to_path);
	return ;
}

void		ft_printdir(t_vector directory, uint64_t flags)
{
	int		links_width;
	int		size_width;
	size_t	i;

	i = 0;
	size_width = 0;
	links_width = 0;
	while (i < directory.length)
	{
		links_width = MAX(
			links_width, ft_intlen(((t_file *)directory.vector[i])->links));
		size_width = MAX(
			size_width, ft_intlen(((t_file *)directory.vector[i])->size));
		++i;
	}
	directory.viter(&directory, &ft_vprintfile, flags, links_width, size_width);
	return ;
}
