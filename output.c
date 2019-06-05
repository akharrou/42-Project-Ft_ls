/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharrou <akharrou@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 19:24:50 by akharrou          #+#    #+#             */
/*   Updated: 2019/06/04 22:01:07 by akharrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	cmode(mode_t mode, char *modestr)
{
	ft_strcpy(modestr, "----------");
	S_IFREG & mode && (modestr[0] = '-');
	S_IFDIR & mode && (modestr[0] = 'd');
	S_IFLNK & mode && (modestr[0] = 'l');
	S_IFIFO & mode && (modestr[0] = 'p');
	S_IFSOCK & mode && (modestr[0] = 's');
	S_IFCHR & mode && (modestr[0] = 'c');
	S_IFBLK & mode && (modestr[0] = 'b');
	S_IRUSR & mode && (modestr[1] = 'r');
	S_IWUSR & mode && (modestr[2] = 'w');
	S_IXUSR & mode && (modestr[3] = 'x');
	S_IRGRP & mode && (modestr[4] = 'r');
	S_IWGRP & mode && (modestr[5] = 'w');
	S_IXGRP & mode && (modestr[6] = 'x');
	S_IROTH & mode && (modestr[7] = 'r');
	S_IWOTH & mode && (modestr[8] = 'w');
	S_IXOTH & mode && (modestr[9] = 'x');
	if (mode & S_ISUID)
		modestr[3] = (mode & S_IXUSR) ? 's' : 'S';
	if (mode & S_ISGID)
		modestr[6] = (mode & S_IXGRP) ? 's' : 'l';
	if (mode & S_ISVTX)
		modestr[9] = (mode & S_IXOTH) ? 't' : 'T';
}

void		ft_printfile(t_file file, uint64_t flags,
				int links_width, int size_width)
{
	char	*tmp_timestr;
	char	timestr[13];
	char	modestr[11];

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
		ft_printf("%11s %*i %s  %s  %*i %12s %s%s",
			modestr, links_width, file.nlinks, file.owner, file.group,
			size_width, file.size, timestr, file.name,
			((flags & p_FLAG) && file.type == DIRECTORY) ? "/" : "");
		if (file.type == SYMBOLIC_LINK)
			ft_printf(" -> %s", file.linkpath);
	}
	else
		ft_printf("%s%s",
			file.name, ((flags & p_FLAG) && file.type == DIRECTORY) ? "/" : "");
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
