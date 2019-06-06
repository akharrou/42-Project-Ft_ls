/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharrou <akharrou@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 19:24:50 by akharrou          #+#    #+#             */
/*   Updated: 2019/06/05 16:56:55 by akharrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			ft_printfile(t_file file, uint64_t flags,
					int links_width, int size_width)
{
	char		*tmp_timestr;
	char		timestr[13];
	char		modestr[11];

	if (!(flags & a_FLAG))
		if ((ft_strcmp(file.name, ".") == 0 || ft_strcmp(file.name, "..") == 0))
			return ;
	if (flags & i_FLAG)
		ft_printf("%i ", file.inode);
	if (flags & l_FLAG)
	{
		tmp_timestr = ctime(&file.modifi_time);
		ft_strncpy(timestr, tmp_timestr + 4, 12);
		free(tmp_timestr);
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

void			ft_printdir(const char *full_dirname, t_vector directory,
					uint64_t flags)
{
	struct stat	dirstat;
	int			links_width;
	int			size_width;
	size_t		i;

	i = 0;
	size_width = 0;
	links_width = 0;
	while (i < directory.length)
	{
		links_width = MAX(
			links_width,
			(int)ft_intlen(((t_file *)directory.vector[i])->nlinks));
		size_width = MAX(
			size_width,
			(int)ft_intlen(((t_file *)directory.vector[i])->size));
		++i;
	}
	if ((stat(full_dirname, &dirstat)) == -1)
		EXIT(perror(NULL));
	ft_printf("total %i\n", dirstat.st_blocks);
	directory.viter(&directory, &ft_vprintfile, flags, links_width, size_width);
	return ;
}
