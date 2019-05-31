
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

# include <time.h>

# include <sys/dir.h>
# include <dirent.h>

# include <sys/types.h>
# include <sys/stat.h>

# include <grp.h>
# include <pwd.h>

/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
** Macro(s).
*/

# define SORT_FLAG (T_FLAG | S_FLAG| F_FLAG | R_FLAG)

/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
** Flags.
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
	A_FLAG = (1 << 0),
	L_FLAG = (1 << 1),
	R_FLAG = (1 << 2),
	T_FLAG = (1 << 3),
	S_FLAG = (1 << 4),
	\
	F_FLAG = ((1 << 5) | A_FLAG),
	RR_FLAG = (1 << 6),
	ONE_FLAG = (1 << 7)
};

/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
** Structure(s).
*/

enum			e_file_types
{
    UNKNOWN         = DT_UNKNOWN,
    REGULAR_FILE    = DT_REG,
    DIRECTORY       = DT_DIR,
    SYMBOLIC_LINK   = DT_LNK,
    NAMED_PIPE      = DT_FIFO,
    SOCKET          = DT_SOCK,
    BLOCK_FILE      = DT_BLK,
    CHARACTER_FILE  = DT_CHR
};

typedef struct	s_file_information
{
	char		name[MAX_NAMELEN + 1];
	char		path[MAX_PATHLEN + 1];
	uint32_t	type;
	\
	char		linked_to_path[MAX_PATHLEN + 1];
	\
	char		*time;
	\
	size_t		size;
	\
	uint32_t	group;
	uint32_t	owner;
	\
	uint32_t	links;
	uint32_t	mode;
	\
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
** Defined in: core.c
** Core Function(s).
*/

int				ft_ls(int argc, const char *argv[], uint64_t flags,
					int (*cmpft)(void *, void *));

/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
** Defined in: utils.c
** Utility Function(s).
*/

t_vector		ft_getdirentries(const char dirpath[MAX_PATHLEN + 1]);
t_vector		ft_getdir(const char path[MAX_PATHLEN + 1]);
void			ft_printdir(t_vector directory, uint64_t flags);
int				ft_listdir(const char dirname[MAX_PATHLEN], uint64_t flags,
					int (*cmpft)(void *, void *));

void			print_errors(void *vector_element);
void			print_files(void *vector_element);
void			vprint_directories(void *vector_element, va_list ap);
void			ft_vprintfile(void *vector_element, va_list ap);
void			ft_printfile(t_file file, uint64_t flags,
					int links_width, int size_width);

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
int				compare_by_time(void *a, void *b);
int				compare_by_ascii(void *a, void *b);

int				reverse_compare_by_size(void *a, void *b);
int				reverse_compare_by_time(void *a, void *b);
int				reverse_compare_by_ascii(void *a, void *b);

/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
*/

#endif
