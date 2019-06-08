/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharrou <akharrou@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 17:03:13 by akharrou          #+#    #+#             */
/*   Updated: 2019/06/07 20:47:16 by akharrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			free_file_element(void *vector_element)
{
	free((t_file *)vector_element);
}

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

void			*wrap_getfile_from_argv(void *vector_element, va_list ap)
{
	const char	*path;
	uint64_t	flags;
	t_file		*file;

	flags = va_arg(ap, uint64_t);
	path = (*(const char **)vector_element);
	file = (t_file *)malloc(sizeof(t_file));
	(*file) = ft_getfile(path, flags);
	return (file);
}
