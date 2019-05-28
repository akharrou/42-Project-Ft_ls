
/*
**  Ft_ls -- Core Function(s).
*/

#include "ft_ls.h"

/*
**    NAME
**         ft_print_dir -- print all entries of a directory
**
**    SYNOPSIS
**         #include <libft.h>
**
**         void
**         ft_print_dir(t_vector directory, uint64_t flags);
**
**    PARAMETERS
**
**         t_vector directory     Brief
**
**         uint64_t flags         Brief
**
**    DESCRIPTION
**         Description.
**
**    RETURN VALUES
**         If successful returns 0; otherwise -1.
*/

void	ft_print_dir(t_vector directory, uint64_t flags)
{
	(void)directory;
	(void)flags;
	return ;
}

/*
**    NAME
**         ft_getdir -- get all entries of a directory
**
**    SYNOPSIS
**         #include <libft.h>
**
**         t_vector
**         ft_getdir(struct s_vector *self);
**
**    PARAMETERS
**
**         const char dirname[PATHMAX]      Name of directory.
**
**    DESCRIPTION
**         (not done); get a vector containing all the directory entries of
**         the 'dirname' directory
**
**    RETURN VALUES
**         If successful returns 0; otherwise -1.
*/

t_vector	ft_getdir(const char dirname[PATHMAX])
{
	t_vector result;

	result = vector.constructor(0, NULL);
	(void)dirname;
	return (result);
}

/*
**    NAME
**         ft_listdir -- list all entries of a directory
**
**    SYNOPSIS
**         #include <libft.h>
**
**         int
**         ft_listdir(const char dirname[PATHMAX], uint64_t flags,
**             int (*cmpft)(void *, void *));
**
**    PARAMETERS
**
**         const char dirname[PATHMAX]      Name of directory.
**
**         uint64_t flags                   Brief
**
**         int (*cmpft)(void *, void *)     Brief
**
**    DESCRIPTION
**         Description.
**
**    RETURN VALUES
**         If successful returns 0; otherwise -1.
*/

void	ft_listdir(const char dirname[PATHMAX], uint64_t flags,
			int (*cmpft)(void *, void *))
{
	(void)dirname;
	(void)flags;
	(void)cmpft;
}

/*
**    NAME
**         ft_ls -- equivalent to the 'ls' system command
**
**    SYNOPSIS
**         #include <libft.h>
**
**         int
**         ft_ls(int ac, const char *av[], uint64_t flags,
**             int (*cmpft)(void *, void *));
**
**    PARAMETERS
**
**         int ac                           Argument count.
**
**         const char *av[]                 Argument vector.
**
**         uint64_t flags                   Flags.
**
**         int (*cmpft)(void *, void *)     Comparasion function
**                                          used to sort the entries
**                                          of a directory.
**
**    DESCRIPTION
**         Description.
**
**    RETURN VALUES
**         If successful returns 0; otherwise -1.
*/

int		ft_ls(int ac, const char *av[], uint64_t flags,
			int (*cmpft)(void *, void *))
{
	(void)ac;
	(void)av;
	(void)flags;
	(void)cmpft;
	return (0);
}
