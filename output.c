/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharrou <akharrou@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 19:24:50 by akharrou          #+#    #+#             */
/*   Updated: 2019/06/05 20:48:31 by akharrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			ft_printfile(t_file file, uint64_t flags,
					int links_width, int size_width)
{
	char		timestr[13];
	char		modestr[11];

	if (!(flags & a_FLAG))
		if ((ft_strcmp(file.name, ".") == 0 || ft_strcmp(file.name, "..") == 0))
			return ;
	if (flags & i_FLAG)
		ft_printf("%i ", file.inode);
	if (flags & l_FLAG)
	{
		ft_strncpy(timestr, ctime(&file.modifi_time) + 4, 12);
		cmode(file.mode, modestr);
		ft_printf("%11s %*i %s  %s  %*i %12s %s%s\n",
			modestr, links_width, file.nlinks, file.owner, file.group,
			size_width, file.size, timestr, file.name,
			((flags & p_FLAG) && file.type == DIRECTORY) ? "/" : "");
		if (file.type == SYMBOLIC_LINK)
			ft_printf(" -> %s", file.linkpath);
	}
	else
		ft_printf("%s%s\n",
			file.name, ((flags & p_FLAG) && file.type == DIRECTORY) ? "/" : "");
}

void			ft_printdir(t_vector dir, uint64_t flags)
{
	int			links_width;
	int			size_width;
	blkcnt_t	total;
	size_t		i;

	total = 0;
	size_width = 0;
	links_width = 0;
	i = -1;
	while (++i < dir.length)
	{
		if (!(flags & a_FLAG) && ((t_file *)dir.vector[i])->name[0] == '.')
			continue;
		links_width = MAX(
			links_width,
			(int)ft_intlen(((t_file *)dir.vector[i])->nlinks));
		size_width = MAX(
			size_width, (int)ft_intlen(((t_file *)dir.vector[i])->size));
		total += ((t_file *)dir.vector[i])->nblocks;
	}
	if (flags & l_FLAG)
		ft_printf("total %i\n", total);
	dir.viter(&dir, &ft_vprintfile, flags, links_width, size_width);
}
