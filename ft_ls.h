/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharrou <akharrou@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 19:50:11 by akharrou          #+#    #+#             */
/*   Updated: 2019/06/11 22:45:12 by akharrou         ###   ########.fr       */
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

# ifndef _DARWIN_FEATURE_64_BIT_INODE
#  define _DARWIN_FEATURE_64_BIT_INODE
# endif

# define SORT_FLAG        (f_FLAG | S_FLAG | t_FLAG)
# define SIX_MONTHS       (15778463)

# define RECURSIVE        (1 << 0)
# define PRINT_DOTTED     (1 << 1)
# define HAS_FILES        (1 << 2)

# define OWNER_WIDTH      (str_lengths[0])
# define GROUP_WIDTH      (str_lengths[1])
# define INODE_WIDTH      (num_lengths[0])
# define SIZE_WIDTH       (num_lengths[1])
# define LINKS_WIDTH      (num_lengths[2])

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

typedef struct			s_flag
{
	const char			symbol;
	uint64_t			value;
}						t_flag;

typedef struct			s_sortflag
{
	const char			symbol;
	uint64_t			value;
	int					(*cmp_function)(const void *, const void *);
	int					(*reverse_cmp_function)(const void *, const void *);
}						t_sortflag;

enum					e_flag_values
{
	a_FLAG = (1 << 0),
	d_FLAG = (1 << 1),
	l_FLAG = (1 << 2),
	r_FLAG = (1 << 3),
	t_FLAG = (1 << 4),
	u_FLAG = (1 << 5),
	U_FLAG = (1 << 6),
	c_FLAG = (1 << 7),
	S_FLAG = (1 << 8),
	p_FLAG = (1 << 9),
	i_FLAG = (1 << 10),
	g_FLAG = (1 << 11),
	f_FLAG = ((1 << 12) | a_FLAG),
	L_FLAG = (1 << 13),
	R_FLAG = (1 << 14),
	_1_FLAG = (1 << 15),
};

/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
** Structure(s).
*/

typedef struct			s_file_information
{
	char				name[MAX_PATHLEN + 1];
	char				path[MAX_PATHLEN + 1];
	char				owner[MAX_NAMELEN + 1];
	char				group[MAX_NAMELEN + 1];
	uint8_t				type;
	ino_t				inode;
	dev_t				device_id;
	mode_t				mode;
	char				linkpath[MAX_PATHLEN + 1];
	off_t				size;
	nlink_t				nlinks;
	blkcnt_t			nblocks;
	struct timespec		time;
}						t_file;

/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
** Defined in: globals.c
** Global(s).
*/

extern t_flag			g_flags[];
extern t_sortflag		g_sortflags[];

/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
** Defined in: preliminaries.c
** Utility Function(s).
*/

uint64_t				get_flags(int *argc, const char **argv[]);
void					*get_cmpft(uint64_t flags);

/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
** Defined in: core.c, info.c, output.c
** Core Function(s).
*/

void					ft_listfile(char *path, uint64_t flags,
							int (*cmpft)(const void *, const void *));

void					ft_listdir(char *dirpath, uint64_t flags,
							int (*cmpft)(const void *, const void *));

void					ft_listdirs(t_vector files, uint64_t flags,
							int (*cmpft)(const void *, const void *),
							uint8_t options);

void					ft_ls(int argc, const char *argv[], uint64_t flags,
							int (*cmpft)(const void *, const void *));

/*
**  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -
*/

t_vector				ft_getdirfiles(char dirpath[MAX_PATHLEN + 1],
							uint64_t flags);

t_file					ft_getfile(const char path[MAX_PATHLEN + 1],
							uint64_t flags);

/*
**  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -
*/

int						ft_printdir(t_vector dir, uint64_t flags);

void					ft_printfile(t_file file, uint64_t flags,
							int *str_lengths, int *num_lengths);

/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
** Defined in: utils.c
** Utility Function(s).
*/

void					print_errors(t_vector files);
int						print_files(t_vector files, uint64_t flags);
void					*wrap_getfile_from_argv(void *vector_element,
							va_list ap);
void					vget_max_widths(void *vector_element, va_list ap);

void					free_file_element(void *vector_element);

/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
** Defined in: error.c
** Error Management Function(s).
*/

void					usage(void);
void					unknown_flag(char unknown_flag);

/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
** Defined in: Comparators/
** Compare Function(s).
*/

int						compare_by_none(const void *a, const void *b);

int						compare_by_size(const void *a, const void *b);
int						compare_by_ascii(const void *a, const void *b);
int						compare_by_time(const void *a, const void *b);

int						reverse_compare_by_size(const void *a, const void *b);
int						reverse_compare_by_ascii(const void *a, const void *b);
int						reverse_compare_by_time(const void *a, const void *b);

/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
*/

#endif
