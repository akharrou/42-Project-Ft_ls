/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharrou <akharrou@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 19:24:50 by akharrou          #+#    #+#             */
/*   Updated: 2019/06/06 05:25:59 by akharrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		cmode(mode_t mode, char *modestr)
{
	ft_strcpy(modestr, "----------");
	S_ISREG(mode) && (modestr[0] = '-');
	S_ISDIR(mode) && (modestr[0] = 'd');
	S_ISLNK(mode) && (modestr[0] = 'l');
	S_ISFIFO(mode) && (modestr[0] = 'p');
	S_ISSOCK(mode) && (modestr[0] = 's');
	S_ISCHR(mode) && (modestr[0] = 'c');
	S_ISBLK(mode) && (modestr[0] = 'b');
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
	modestr[10] = '\0';
}

void			ft_printfile(t_file file, uint64_t flags,
					int *str_lengths, int *num_lengths)
{
	char		timestr[13];
	char		modestr[11];

	if (!(flags & a_FLAG) && file.name[0] == '.')
		return ;
	if (flags & i_FLAG)
		ft_printf("%*i ", num_lengths[0], file.inode);
	if (flags & l_FLAG)
	{
		ft_strncpy(timestr, ctime(&file.modifi_time) + 4, 12);
		cmode(file.mode, modestr);
		ft_printf("%s %*i %*s  %*s  %*i %12s %s%s\n",
			modestr, num_lengths[2], file.nlinks,
			str_lengths[0], file.owner, str_lengths[1], file.group,
			num_lengths[1], file.size, timestr, file.name,
			((flags & p_FLAG) && file.type == DIRECTORY) ? "/" : "");
		if (file.type == SYMBOLIC_LINK)
			ft_printf(" -> %s", file.linkpath);
	}
	else
		ft_printf("%s%s\n",
			file.name, ((flags & p_FLAG) && file.type == DIRECTORY) ? "/" : "");
}

static void		wrap_printfile(void *vector_element, va_list ap)
{
	int			*str_lengths;
	int			*num_lengths;
	uint64_t	flags;

	if (!vector_element)
		return ;
	flags = va_arg(ap, uint64_t);
	str_lengths = va_arg(ap, int *);
	num_lengths = va_arg(ap, int *);
	ft_printfile(*(t_file *)vector_element, flags, str_lengths, num_lengths);
}

void			ft_printdir(t_vector dir, uint64_t flags)
{
	int			str_lengths[2];
	int			num_lengths[3];
	blkcnt_t	total;
	t_file		file;
	size_t		i;

	total = 0;
	ft_bzero(str_lengths, (sizeof(int) * 2));
	ft_bzero(num_lengths, (sizeof(int) * 3));
	i = -1;
	while (++i < dir.length)
	{
		file = *((t_file *)dir.vector[i]);
		if (!(flags & a_FLAG) && file.name[0] == '.')
			continue ;
		str_lengths[0] = MAX(str_lengths[0], (int)ft_strlen(file.owner));
		str_lengths[1] = MAX(str_lengths[1], (int)ft_strlen(file.group));
		num_lengths[0] = MAX(num_lengths[0], (int)file.inode);
		num_lengths[1] = MAX(num_lengths[1], (int)file.size);
		num_lengths[2] = MAX(num_lengths[2], (int)file.nlinks);
		total += ((t_file *)dir.vector[i])->nblocks;
	}
	if (flags & l_FLAG)
		ft_printf("total %i\n", total);
	dir.viter(&dir, &wrap_printfile, flags, str_lengths, num_lengths);
}

/* TODO : make sure getting the widths works and prints correctly */
