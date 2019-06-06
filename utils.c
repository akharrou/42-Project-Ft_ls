/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharrou <akharrou@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 17:03:13 by akharrou          #+#    #+#             */
/*   Updated: 2019/06/05 20:22:49 by akharrou         ###   ########.fr       */
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
	t_file		file;

	if (!vector_element)
		return ;
	dirpath = va_arg(ap, char *);
	flags = va_arg(ap, uint64_t);
	cmpft = va_arg(ap, int (*)(void *, void *));
	file = *(t_file *)vector_element;
	if (file.type == DIRECTORY &&
		ft_strcmp(file.name, ".") != 0 &&
		ft_strcmp(file.name, "..") != 0)
	{
		ft_printf("\n%s%s:\n", dirpath, file.name);
		ft_listdir(ft_vstrjoin(dirpath, 2, file.name, "/"), flags, cmpft);
	}
}

/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
** This serves the vector viter() method in the ft_printdir() function.
*/

void			ft_vprintfile(void *vector_element, va_list ap)
{
	int			size_width;
	int			links_width;
	uint64_t	flags;

	if (!vector_element)
		return ;
	flags = va_arg(ap, uint64_t);
	links_width = va_arg(ap, int);
	size_width = va_arg(ap, int);
	ft_printfile(*(t_file *)vector_element, flags, links_width, size_width);
}

/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
*/

uint8_t			mode2type(uint8_t mode)
{
	uint8_t		type;

	if (S_IFREG & mode)
		type = REGULAR_FILE;
	else if (S_IFDIR & mode)
		type = DIRECTORY;
	else if (S_IFLNK & mode)
		type = SYMBOLIC_LINK;
	else if (S_IFIFO & mode)
		type = NAMED_PIPE;
	else if (S_IFSOCK & mode)
		type = SOCKET;
	else if (S_IFCHR & mode)
		type = CHARACTER_FILE;
	else if (S_IFBLK & mode)
		type = BLOCK_FILE;
	else
		type = UNKNOWN_FILE;
	return (type);
}

void			cmode(mode_t mode, char *modestr)
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
	modestr[10] = '\0';
}

/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
*/

void			*wrap_getfile_from_argv(void *vector_element)
{
	t_file		*file;

	file = (t_file *)malloc(sizeof(t_file));
	(*file) = ft_getfile((const char *)vector_element);
	return (file);
}

void			*wrap_getfile_from_dirent(void *vector_element, va_list ap)
{
	t_file		*file;

	(void)ap;
	file = (t_file *)malloc(sizeof(t_file));
	(*file) = ft_getfile(((struct dirent *)vector_element)->d_name);
	return (file);
}

/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
*/
