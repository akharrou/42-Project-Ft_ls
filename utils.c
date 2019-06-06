/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharrou <akharrou@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 17:03:13 by akharrou          #+#    #+#             */
/*   Updated: 2019/06/06 04:55:10 by akharrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
** These serve the vector iter() & viter() methods in the ft_ls() function.
*/

void			print_errors(void *vector_element)
{
	t_file		file;

	if (!vector_element)
		return ;
	file = *(t_file *)vector_element;
	if (file.type == UNKNOWN_FILE)
		ft_printf("./ft_ls: %s: No such file or directory\n", file.name);
}

void			print_files(void *vector_element)
{
	t_file		file;

	if (!vector_element)
		return ;
	file = *(t_file *)vector_element;
	if (file.type != UNKNOWN_FILE && file.type != DIRECTORY)
		ft_printf("%s\n", file.name);
}

void			vprint_directories(void *vector_element, va_list ap)
{
	int			(*cmpft)(void *, void *);
	char		*dirpath;
	uint64_t	flags;
	t_file		*file;

	if (!vector_element)
		return ;
	dirpath = va_arg(ap, char *);
	flags = va_arg(ap, uint64_t);
	cmpft = va_arg(ap, int (*)(void *, void *));
	file = (t_file *)vector_element;
	if ((!(flags & a_FLAG) && file->name[0] == '.') ||
		ft_strcmp(file->name, ".") == 0 ||
		ft_strcmp(file->name, "..") == 0)
	{
		return ;
	}
	if (file->type == DIRECTORY)
	{
		ft_printf("\n%s%s:\n", dirpath, file->name);
		ft_listdir(ft_vstrjoin(dirpath, 2, file->name, "/"), flags, cmpft);
	}
}

/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
*/
