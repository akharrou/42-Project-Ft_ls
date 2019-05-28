
/*
**  Ft_ls -- Main.
*/

#include "ft_ls.h"

int				main(int ac, const char *av[])
{
	int			(*cmpft)(void *, void *);
	uint64_t	flags;

	++av;
	flags = get_flags(&ac, &av);
	cmpft = (int (*)(void *, void *))get_cmpft(flags);
	ft_ls(ac, av, flags, cmpft);
	return (0);
}

/*
**  TODO :
**
**  Done [_]  ;  Reviewed [_]  ;            1 - implement comparasion functions
**  Done [✓]  ;  Reviewed [_]  ;  Kevin     2 - get the comparasion function
**  Done [_]  ;  Reviewed [_]  ;            3 - must check if we have permissions before recursing down
**  Done [_]  ;  Reviewed [_]  ;            4 - must exclude '.' & '..' from recursive calling
**  Done [_]  ;  Reviewed [_]  ;  Aymen     5 - implement the input into 3: errors, files & directories
**  Done [_]  ;  Reviewed [_]  ;  Aymen     6 - implement the vector.filter constructor
**  Done [_]  ;  Reviewed [_]  ;            7 - implement the printing function for a vector containing all files/directories
**  Done [_]  ;  Reviewed [_]  ;  Aymen     8 - add functionality to ft_getdirectory function so that it returns a vector with
**                                              t_file struct containing all needed information for each file/dir
*/
