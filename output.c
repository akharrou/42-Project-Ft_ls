/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharrou <akharrou@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 19:24:50 by akharrou          #+#    #+#             */
/*   Updated: 2019/06/01 19:58:30 by akharrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_printfile(t_file file, uint64_t flags,
				int links_width, int size_width)
{
	char	**timetab;

	if (!(flags & A_FLAG))
		if ((ft_strcmp(file.name, ".") == 0 || ft_strcmp(file.name, "..") == 0))
			return ;
	if (flags & L_FLAG)
	{
		timetab = ft_strsplit(ctime(&file.modifi_time), " :");
		ft_printf("%11s %*i %s  %s  %*i %3s %2s %2s:%2s %s",
			file.mode,
			links_width, file.nlinks,
			file.owner, file.group,
			size_width, file.size,
			timetab[1], timetab[2], timetab[3], timetab[4],
			file.name);
		if (file.type == SYMBOLIC_LINK)
			ft_printf(" -> %s", file.linkpath);
	}
	else
		ft_putstr(file.name);
	freestrtab(timetab);
	return;
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
			links_width, ft_intlen(((t_file *)directory.vector[i])->nlinks));
		size_width = MAX(
			size_width, ft_intlen(((t_file *)directory.vector[i])->size));
		++i;
	}
	directory.viter(&directory, &ft_vprintfile, flags, links_width, size_width);
	return ;
}
