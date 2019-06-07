/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharrou <akharrou@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 19:24:50 by akharrou          #+#    #+#             */
/*   Updated: 2019/06/07 03:04:48 by akharrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

#define OWNER_WIDTH (str_lengths[0])
#define GROUP_WIDTH (str_lengths[1])
#define INODE_WIDTH (num_lengths[0])
#define SIZE_WIDTH  (num_lengths[1])
#define LINKS_WIDTH (num_lengths[2])

static void		cmode(const char *path, mode_t mode, char *modestr,
					uint64_t flags)
{
	ssize_t ret;

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
	(mode & S_ISUID) && (modestr[3] = (mode & S_IXUSR) ? 's' : 'S');
	(mode & S_ISGID) && (modestr[6] = (mode & S_IXGRP) ? 's' : 'l');
	(mode & S_ISVTX) && (modestr[9] = (mode & S_IXOTH) ? 't' : 'T');
	(void)flags;
	ret = listxattr(path, NULL, 0, XATTR_NOFOLLOW);
	modestr[10] = (ret > 0) ? '@' : '\0';
	modestr[11] = '\0';
}

void			ft_printfile(t_file file, uint64_t flags,
					int *str_lengths, int *num_lengths)
{
	char		timestr[13];
	char		modestr[12];

	if (!(flags & a_FLAG) && file.name[0] == '.')
		return ;
	if (flags & i_FLAG)
		ft_printf("%*i ", INODE_WIDTH, file.inode);
	if (flags & l_FLAG)
	{
		ft_strncpy(timestr, ctime(&file.modifi_time) + 4, 12);
		cmode(file.path, file.mode, modestr, flags);
		ft_printf("%-11s %*i %-*s  %-*s  %*i %s %s%s",
			modestr, LINKS_WIDTH, file.nlinks,
			OWNER_WIDTH, file.owner, GROUP_WIDTH, file.group,
			SIZE_WIDTH, file.size, timestr, file.name,
			((flags & p_FLAG) && file.type == DIRECTORY) ? "/" : "");
		(file.type == SYMBOLIC_LINK) ?
			ft_printf(" -> %s\n", file.linkpath) :
			ft_printf("\n");
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

static void		vget_max_widths(void *vector_element, va_list ap)
{
	int			*str_lengths;
	int			*num_lengths;
	blkcnt_t	*total;
	uint64_t	flags;
	t_file		file;

	flags = va_arg(ap, uint64_t);
	str_lengths = *(va_arg(ap, int **));
	num_lengths = *(va_arg(ap, int **));
	total = (va_arg(ap, blkcnt_t *));
	file = *((t_file *)vector_element);
	if (!(flags & a_FLAG) && file.name[0] == '.')
		return ;
	OWNER_WIDTH = MAX(OWNER_WIDTH, (int)ft_strlen(file.owner));
	GROUP_WIDTH = MAX(GROUP_WIDTH, (int)ft_strlen(file.group));
	INODE_WIDTH = MAX(INODE_WIDTH, (int)ft_intlen(file.inode));
	LINKS_WIDTH = MAX(LINKS_WIDTH, (int)ft_intlen(file.nlinks));
	SIZE_WIDTH = MAX(SIZE_WIDTH, (int)ft_intlen(file.size));
	(*total) += file.nblocks;
}

void			ft_printdir(t_vector dir, uint64_t flags)
{
	int			*str_lengths;
	int			*num_lengths;
	blkcnt_t	total;

	total = 0;
	str_lengths = ft_malloc(sizeof(int) * 2, '\0');
	num_lengths = ft_malloc(sizeof(int) * 3, '\0');
	dir.viter(&dir, &vget_max_widths,
		flags, &str_lengths, &num_lengths, &total);
	if (flags & l_FLAG)
		ft_printf("total %i\n", total);
	dir.viter(&dir, &wrap_printfile, flags, str_lengths, num_lengths);
	free(str_lengths);
	free(num_lengths);
}
