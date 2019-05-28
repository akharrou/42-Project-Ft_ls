
/*
**  Ft_ls -- Header File.
*/

#ifndef FT_LS_H
# define FT_LS_H

/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
** Header File(s).
*/

# include "Libft/Includes/libft.h"

# include <sys/types.h>
# include <dirent.h>

/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
** Macro(s).
*/

# define SORT_FLAG (T_FLAG | R_FLAG | F_FLAG)

/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
** Flags.
*/

typedef struct	s_flag
{
	const char	symbol;
	uint64_t	value;
	int			(*cmp_funct)(void *, void *);
	int			(*rev_cmp_funct)(void *, void *);
}				t_flag;

enum			e_flag_values
{
	RR_FLAG = (1 << 0),
	A_FLAG = (1 << 1),
	L_FLAG = (1 << 2),
	R_FLAG = (1 << 3),
	T_FLAG = (1 << 4),
	F_FLAG = ((1 << 5) | A_FLAG)
};

/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
** Structure(s).
*/

enum			e_types
{
	FILE_,
	ERROR_,
	DIRECTORY_
};

typedef struct	s_file_information
{
	char		name[NAMEMAX + 1];
	uint32_t	type;
	\
	uint32_t	month;
	uint32_t	day;
	uint32_t	hour;
	uint32_t	minute;
	\
	size_t		total_bytes;
	\
	uint32_t	group;
	uint32_t	owner;
	\
	uint32_t	links;
	uint32_t	filemode;
	\
}				t_file;

/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
** FILE: globals.c
** Describtion: Global(s).
*/

extern t_flag	g_flags[];

/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
** FILE: core.c
** Describtion: Core Function(s).
*/

int				ft_ls(int ac, const char *av[], uint64_t flags,
					int (*cmpft)(void *, void *));

void			ft_listdir(const char dirname[PATHMAX], uint64_t flags,
					int (*cmpft)(void *, void *));

/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
** FILE: preliminaries.c & core.c
** Describtion: Utility Function(s).
*/

uint64_t		get_flags(int *ac, const char **av[]);
void			*get_cmpft(uint64_t flags);

t_vector		ft_getdir(const char dirname[PATHMAX]);
void			ft_print_dir(t_vector directory, uint64_t flags);

/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
** FILE: error.c
** Describtion: Error Management Function(s).
*/

void			usage(void);
void			unknown_flag(char unknown_flag);

/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
*/

/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
** FILE: compare_functions.c
** Describtion: Compare Function(s).
*/

int				sort_by_time(void *a, void *b);
int				sort_by_rev_time(void *a, void *b);
int				sort_by_nosort(void *a, void *b);
int				sort_by_ascii(void *a, void *b);

/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
*/

#endif
