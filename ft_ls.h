
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


/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
** Flags.
*/

typedef struct	s_flag
{
	const char	symbol;
	uint64_t	value;
}				t_flag;

enum			e_flag_values
{
	A_FLAG = (1 << 0),
	L_FLAG = (1 << 1),
	R_FLAG = (1 << 2),
	T_FLAG = (1 << 3),
	F_FLAG = ((1 << 4) | A_FLAG),
	RR_FLAG = (1 << 5)
};

/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
** Structure(s).
*/

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
** Global(s).
*/

extern t_flag	g_flags[];

/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
** Main Function(s).
*/

void			ft_ls(int ac, const char *av[], uint64_t flags,
				int (*cmpft)(void *, void *));

void			ft_listdir(const char dirname[PATHMAX], uint64_t flags,
				int (*cmpft)(void *, void *));

/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
** Utility Function(s).
*/

uint64_t		get_flags(int *ac, const char **av[]);
void			*get_cmpft(uint64_t flags);

/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
** Error Management Function(s).
*/

void			usage(void);
void			unknown_flag(char *unknown_flag);

/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
*/

#endif
