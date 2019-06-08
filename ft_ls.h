/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharrou <akharrou@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 19:50:11 by akharrou          #+#    #+#             */
/*   Updated: 2019/06/07 19:39:16 by akharrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
** Header File(s).
*/

# include "Libft/Includes/libft.h"

# include <sys/dir.h>
# include <sys/types.h>
# include <sys/xattr.h>
# include <sys/acl.h>
# include <sys/stat.h>
# include <dirent.h>

# include <grp.h>
# include <pwd.h>

# include <time.h>

/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
** Macro(s).
*/

# define SORT_FLAG (t_FLAG | u_FLAG | c_FLAG | S_FLAG| f_FLAG | r_FLAG)

/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
** File Type(s).
*/

# define UNKNOWN_FILE    DT_UNKNOWN
# define REGULAR_FILE    DT_REG
# define DIRECTORY       DT_DIR
# define SYMBOLIC_LINK   DT_LNK
# define NAMED_PIPE      DT_FIFO
# define SOCKET          DT_SOCK
# define BLOCK_FILE      DT_BLK
# define CHARACTER_FILE  DT_CHR

/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
** Flag(s).
*/

typedef struct	s_flag
{
	const char	symbol;
	uint64_t	value;
	int			(*cmp_function)(void *, void *);
	int			(*reverse_cmp_function)(void *, void *);
}				t_flag;

enum			e_flag_values
{
	a_FLAG = (1 << 0),
	l_FLAG = (1 << 1),
	r_FLAG = (1 << 2),
	t_FLAG = (1 << 3),
	u_FLAG = (1 << 4),
	c_FLAG = (1 << 5),
	S_FLAG = (1 << 6),
	p_FLAG = (1 << 7),
	i_FLAG = (1 << 8),
	f_FLAG = ((1 << 9) | a_FLAG),
	L_FLAG = (1 << 10),
	R_FLAG = (1 << 11),
	_1_FLAG = (1 << 12)
};

/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
** Structure(s).
*/

typedef struct	s_file_information
{
	char		name[MAX_PATHLEN + 1];
	char		path[MAX_PATHLEN + 1];
	ino_t		inode;
	dev_t		device_id;
	char		*owner;
	char		*group;
	uint8_t		type;
	mode_t		mode;
	char		linkpath[MAX_PATHLEN + 1];
	off_t		size;
	nlink_t		nlinks;
	blkcnt_t	nblocks;
	time_t		access_time;
	time_t		modifi_time;
	time_t		change_time;
}				t_file;

/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
** Defined in: globals.c
** Global(s).
*/

extern t_flag	g_flags[];

/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
** Defined in: preliminaries.c
** Utility Function(s).
*/

uint64_t		get_flags(int *argc, const char **argv[]);
void			*get_cmpft(uint64_t flags);

/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
** Defined in: core.c, info.c, output.c
** Core Function(s).
*/

int				ft_ls(int argc, const char *argv[], uint64_t flags,
					int (*cmpft)(void *, void *));

int				ft_listdirs(t_vector files, uint64_t flags,
					int (*cmpft)(void *, void *));

int				ft_listdir(char *dirpath, uint64_t flags,
					int (*cmpft)(void *, void *));

int				ft_listfile(char *path, uint64_t flags,
					int (*cmpft)(void *, void *));

/*
**  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -
*/

t_vector		ft_getdirfiles(char dirpath[MAX_PATHLEN + 1],
					uint64_t flags);

t_file			ft_getfile(const char path[MAX_PATHLEN + 1],
					uint64_t flags);

/*
**  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -
*/

void			ft_printdir(t_vector dir, uint64_t flags);

void			ft_printfile(t_file file, uint64_t flags,
					int *str_lengths, int *num_lengths);

/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
** Defined in: utils.c
** Utility Function(s).
*/

void			print_errors(void *vector_element);
void			vprint_files(void *vector_element, va_list ap);
void			vprint_dirs(void *vector_element, va_list ap);
void			*wrap_getfile_from_argv(void *vector_element, va_list ap);

void			free_file_element(void *vector_element);

/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
** Defined in: error.c
** Error Management Function(s).
*/

void			usage(void);
void			unknown_flag(char unknown_flag);

/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
** Defined in: Comparators/
** Compare Function(s).
*/

int				compare_by_none(void *a, void *b);

int				compare_by_size(void *a, void *b);
int				compare_by_ascii(void *a, void *b);
int				compare_by_mtime(void *a, void *b);
int				compare_by_atime(void *a, void *b);
int				compare_by_ctime(void *a, void *b);

int				reverse_compare_by_size(void *a, void *b);
int				reverse_compare_by_ascii(void *a, void *b);
int				reverse_compare_by_mtime(void *a, void *b);
int				reverse_compare_by_atime(void *a, void *b);
int				reverse_compare_by_ctime(void *a, void *b);

/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
*/

#endif
