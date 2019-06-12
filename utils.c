/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharrou <akharrou@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 17:03:13 by akharrou          #+#    #+#             */
/*   Updated: 2019/06/11 22:34:35 by akharrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			print_errors(t_vector files)
{
	t_file		file;
	size_t		i;

	i = 0;
	while (i < files.length)
	{
		file = *(t_file *)files.vector[i];
		if (file.type == UNKNOWN_FILE)
			ft_printf("./ft_ls: %s: No such file or directory\n", file.name);
		++i;
	}
	return ;
}

static void		vget_format_info(void *vector_element, va_list ap)
{
	int			*str_lengths;
	int			*num_lengths;
	t_file		file;

	str_lengths = va_arg(ap, int *);
	num_lengths = va_arg(ap, int *);
	file = *((t_file *)vector_element);
	if (file.type == UNKNOWN_FILE || file.type == DIRECTORY)
		return ;
	OWNER_WIDTH = MAX(OWNER_WIDTH, (int)ft_strlen(file.owner));
	GROUP_WIDTH = MAX(GROUP_WIDTH, (int)ft_strlen(file.group));
	INODE_WIDTH = MAX(INODE_WIDTH, (int)ft_intlen(file.inode));
	LINKS_WIDTH = MAX(LINKS_WIDTH, (int)ft_intlen(file.nlinks));
	SIZE_WIDTH = MAX(SIZE_WIDTH, (int)ft_intlen(file.size));
	return ;
}

int				print_files(t_vector files, uint64_t flags)
{
	int			str_lengths[2];
	int			num_lengths[3];
	size_t		total_files;
	t_file		file;
	size_t		i;

	ft_bzero(str_lengths, sizeof(int) * 2);
	ft_bzero(num_lengths, sizeof(int) * 3);
	files.viter(&files, &vget_format_info, str_lengths, num_lengths);
	total_files = 0;
	i = 0;
	while (i < files.length)
	{
		file = *(t_file *)files.vector[i];
		if (file.type != UNKNOWN_FILE &&
			(file.type != DIRECTORY || (flags & d_FLAG)))
		{
			++total_files;
			ft_strncpy(file.name, file.path, MAX_PATHLEN);
			ft_printfile(file, flags, str_lengths, num_lengths);
		}
		++i;
	}
	return ((total_files > 0) ? HAS_FILES : 0);
}

void			*wrap_getfile_from_argv(void *vector_element, va_list ap)
{
	const char	*path;
	uint64_t	flags;
	t_file		*file;

	flags = va_arg(ap, uint64_t);
	path = (*(const char **)vector_element);
	file = (t_file *)malloc(sizeof(t_file));
	(*file) = ft_getfile(path, flags);
	ft_strncpy(file->name, file->path, MAX_PATHLEN);
	return (file);
}

void			vget_max_widths(void *vector_element, va_list ap)
{
	int			*str_lengths;
	int			*num_lengths;
	blkcnt_t	*total;
	uint64_t	flags;
	t_file		file;

	str_lengths = va_arg(ap, int *);
	num_lengths = va_arg(ap, int *);
	total = (va_arg(ap, blkcnt_t *));
	flags = va_arg(ap, uint64_t);
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
