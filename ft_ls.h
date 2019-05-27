
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
	void		(*handler)(void *);
}				t_flag;

enum			e_flag_values
{
	LS_A_OPTION = (1 << 0),
	LS_L_OPTION = (1 << 1),
	LS_R_OPTION = (1 << 2),
	LS_T_OPTION = (1 << 3),
	LS_RR_OPTION = (1 << 4)
};

/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
** Structure(s).
*/

typedef struct	s_file_information
{
	char		name[NAMEMAX + 1];
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
** State.
*/

typedef struct	s_ft_ls_state
{
	uint8_t		flags;
	int			(*compare)(t_file a, t_file b);
}				t_state;

/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
** Global(s).
*/

extern t_flag g_flags[];

/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
** Main Function(s).
*/


/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
** Utility Function(s).
*/

void	ls_a_handler(t_state *state, uint64_t *flags);
void	ls_l_handler(t_state *state, uint64_t *flags);
void	ls_r_handler(t_state *state, uint64_t *flags);
void	ls_t_handler(t_state *state, uint64_t *flags);
void	ls_rr_handler(t_state *state, uint64_t *flags);
void	ls_f_handler(t_state *state, uint64_t *flags);

/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
*/

#endif
