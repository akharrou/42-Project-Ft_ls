/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharrou <akharrou@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 23:44:04 by akharrou          #+#    #+#             */
/*   Updated: 2019/06/11 22:44:02 by akharrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char		get_special_char(const char *path)
{
	char		special;
	ssize_t		xattr;
	acl_t		acl;

	xattr = listxattr(path, NULL, 0, XATTR_NOFOLLOW);
	acl = acl_get_link_np(path, ACL_TYPE_EXTENDED);
	if (xattr > 0)
		special = '@';
	else if (acl != NULL)
		special = '+';
	else
		special = ' ';
	acl_free(acl);
	return (special);
}

static void		cmode(const char *path, mode_t mode, char *modestr)
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
	(mode & S_ISUID) && (modestr[3] = (mode & S_IXUSR) ? 's' : 'S');
	(mode & S_ISGID) && (modestr[6] = (mode & S_IXGRP) ? 's' : 'l');
	(mode & S_ISVTX) && (modestr[9] = (mode & S_IXOTH) ? 't' : 'T');
	modestr[10] = get_special_char(path);
	modestr[11] = '\0';
}

char			*ctimespec(char *dest, struct timespec st_timespec)
{
	ft_strncpy(dest, ctime(&st_timespec.tv_sec) + 4, 7);
	if (st_timespec.tv_sec < time(0) - SIX_MONTHS ||
		st_timespec.tv_sec > time(0) + SIX_MONTHS)
	{
		ft_strncpy(dest + 7, ctime(&st_timespec.tv_sec) + 19, 5);
	}
	else
	{
		ft_strncpy(dest + 7, ctime(&st_timespec.tv_sec) + 11, 5);
	}
	dest[12] = '\0';
	return (dest);
}

void			ft_printfile(t_file file, uint64_t flags,
					int *str_lengths, int *num_lengths)
{
	char		owner_group[MAX_NAMELEN];
	char		timestr[13];
	char		modestr[12];

	if (!(flags & a_FLAG) && file.name[0] == '.')
		return ;
	(flags & i_FLAG) ? ft_printf("%*i ", INODE_WIDTH, file.inode) : PASS;
	if (flags & (l_FLAG | g_FLAG))
	{
		ctimespec(timestr, file.time);
		cmode(file.path, file.mode, modestr);
		(flags & g_FLAG) ?
			ft_sprintf(owner_group, "%-*s", GROUP_WIDTH, file.group) :
			ft_sprintf(owner_group, "%-*s  %-*s",
				OWNER_WIDTH, file.owner, GROUP_WIDTH, file.group);
		ft_printf("%-11s %*i %s  %*lli %12s %s%s",
			modestr, LINKS_WIDTH, file.nlinks, owner_group,
			SIZE_WIDTH, file.size, timestr, file.name,
			((flags & p_FLAG) && file.type == DIRECTORY) ? "/" : "");
		(file.type == SYMBOLIC_LINK) ?
			ft_printf(" -> %s\n", file.linkpath) : ft_printf("\n");
	}
	else
		ft_printf("%s%s\n",
			file.name, ((flags & p_FLAG) && file.type == DIRECTORY) ? "/" : "");
}

int				ft_printdir(t_vector dir, uint64_t flags)
{
	int			str_lengths[2];
	int			num_lengths[3];
	blkcnt_t	total;
	size_t		i;

	ft_bzero(str_lengths, sizeof(int) * 2);
	ft_bzero(num_lengths, sizeof(int) * 3);
	total = 0;
	dir.viter(
		&dir, &vget_max_widths, str_lengths, num_lengths, &total, flags);
	if (flags & (l_FLAG | g_FLAG))
		ft_printf("total %i\n", total);
	i = 0;
	while (i < dir.length)
	{
		ft_printfile(*(t_file *)dir.vector[i], flags, str_lengths, num_lengths);
		++i;
	}
	return (0);
}
