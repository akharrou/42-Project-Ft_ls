/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharrou <akharrou@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 17:03:13 by akharrou          #+#    #+#             */
/*   Updated: 2019/06/07 03:42:06 by akharrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			print_errors(void *vector_element)
{
	t_file		file;

	if (!vector_element)
		return ;
	file = *(t_file *)vector_element;
	if (file.type == UNKNOWN_FILE)
		ft_printf("./ft_ls: %s: No such file or directory\n", file.name);
}

void			vprint_files(void *vector_element, va_list ap)
{
	t_file		file;
	uint64_t	flags;

	if (!vector_element)
		return ;
	flags = va_arg(ap, uint64_t);
	file = *(t_file *)vector_element;
	if (file.type != UNKNOWN_FILE && file.type != DIRECTORY)
	{
		ft_strncpy(file.name, file.path, MAX_PATHLEN);
		if (!(flags & l_FLAG))
			ft_printf("%s\n", file.name);
		else
			ft_printfile(file, flags, (int[2]){ft_strlen(file.owner),
				ft_strlen(file.group)}, (int[3]){ft_intlen(file.inode),
				ft_intlen(file.size), ft_intlen(file.nlinks)});
	}
}

void			ft_listdirs(t_vector files, uint64_t flags,
					int (*cmpft)(void *, void *))
{
	t_file		*file;
	size_t		i;

	i = -1;
	while (++i < files.length)
	{
		file = (t_file *)files.vector[i];
		if (file->type == DIRECTORY)
		{
			if ((!(flags & a_FLAG) && file->name[0] == '.') ||
				ft_strcmp(file->name, ".") == 0 ||
				ft_strcmp(file->name, "..") == 0)
			{
				continue ;
			}
			ft_printf("\n%s:\n", file->path);
			ft_listdir(ft_strdup(file->path), flags, cmpft);
		}
	}
}
