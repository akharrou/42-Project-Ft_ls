
int			ft_listdirs(const char *dirs[], size_t n, uint64_t flags,
				int (*cmpft)(void *, void *))
{
	size_t	i;

	if (!dirs || !cmpft || n < 1)
		return (-1);
	(flags & R_FLAG) ?
		ft_quicksort(dirs, n, sizeof(char *), &ft_reverse_cmpstr) :
		ft_quicksort(dirs, n, sizeof(char *), &ft_cmpstr);
	/* print errors, then files, then directories */
	i = 0;
	while (dirs[i])
	{
		if (ft_isdirectory(dirs[i]))
		{
			if (n > 1)
				ft_printf("%s:\n", dirs[i]);
			ft_listdir(dirs[i++], flags, cmpft);
		}
	}
	return (0);
}


int			ft_ls(int argc, const char *argv[], uint64_t flags,
				int (*cmpft)(void *, void *))
{
	size_t	i;

	i = 0;
	if (argv == NULL || cmpft == NULL)
		return (-1);
	if (argv[i])
		ft_listdirs(argv, (size_t)argc, flags, cmpft);
	else
		ft_listdirs((const char **)ft_strtab(1, "./"), 1, flags, cmpft);
	return (0);
}



	i = -1;
	while (argv[++i])
		if (!ft_isfile(argv[i]) && !ft_isdirectory(argv[i]))
			ft_printf("./ft_ls: %s: No such file or directory\n", argv[i]);
	i = -1;
	while (argv[++i])
		if (ft_isfile(argv[i]))
			ft_printf("%s\n", argv[i]);
	i = -1;
	while (argv[++i])
		if (ft_isdirectory(argv[i]))
		{
			if (n > 1)
				ft_printf("%s:\n", argv[i]);
			ft_listdir(argv[i], flags, cmpft);
		}






int			ft_ls(const char *argv[], size_t n, uint64_t flags,
				int (*cmpft)(void *, void *))
{
	t_vector	errs;
	t_vector	fils;
	t_vector	dirs;
	size_t		i;

	if (argv == NULL || cmpft == NULL)
		return (-1);
	if (argv[0] == NULL)
		return (ft_listdir("./", flags, cmpft));
	ft_quicksort(argv, n, sizeof(char *),
		((flags & R_FLAG) ? &ft_reverse_cmpstr : &ft_cmpstr));
	fils = vector.filter(argv, n, sizeof(char *), &ft_isfile);
	errs = vector.filter(argv, n, sizeof(char *), &ft_is_unknown);
	dirs = vector.filter(argv, n, sizeof(char *), &ft_isdirectory);
	errs.iter(&errs, &print_error);
	fils.iter(&fils, &print_files);
	i = -1;
	while (++i < dirs.length)
	{
		if (dirs.length > 1)
			ft_printf("%s:\n", argv[i]);
		ft_listdir((char *)dirs.vector[i], flags, cmpft);
	}
	DESTRUCT_VECTORS;
	return (0);
}


	while (++i < files.length)
	{
		if (ft_isdirectory((char *)((t_file *)files.vector[i]).name))
		{
			if (n > 1)
				ft_printf("%s:\n", argv[i]);
			ft_listdir((char *)files.vector[i], flags, cmpft);
		}
	}

# define DESTRUCT(vector_instance) (vector.destructor(&vector_instance))
# define DESTRUCT_VECTORS { DESTRUCT(errs); DESTRUCT(fils); DESTRUCT(dirs); }




int				ft_ls(int argc, const char *argv[], uint64_t flags,
					int (*cmpft)(void *, void *))
{
	t_vector	files;
	size_t		i;

	if (argv == NULL || cmpft == NULL)
		return (-1);
	if (argc == 0)
		return (ft_listdir(".", flags, cmpft));
	files = vector.map(argv, (size_t)argc, sizeof(char *), &get_file_entry);
	ft_quicksort(files.vector, files.length, sizeof(void *), cmpft);
	files.iter(&files, &print_errs);
	files.iter(&files, &print_files);
	i = -1;
	while (i < files.length)
	{
		if (ft_isdirectory((char *)((t_file *)files.vector[i])->name))
		{
			if (argc > 1)
				ft_printf("%s:\n", (char *)((t_file *)files.vector[i])->name);
			ft_listdir((char *)((t_file *)files.vector[i])->name, flags, cmpft);
		}
	}
	vector.destructor(&files);
	return (0);
}


// /*
// **  Ft_ls -- Core Function(s).
// */

// #include "ft_ls.h"

// /*
// **    NAME
// **         ft_print_dir -- print all entries of a directory
// **
// **    SYNOPSIS
// **         #include <libft.h>
// **
// **         void
// **         ft_print_dir(t_vector directory, uint64_t flags);
// **
// **    PARAMETERS
// **
// **         t_vector directory     Brief
// **
// **         uint64_t flags         Brief
// **
// **    DESCRIPTION
// **         Description.
// **
// **    RETURN VALUES
// **         If successful returns 0; otherwise -1.
// */

// void			ft_print_dir(t_vector directory, uint64_t flags)
// {
// 	/* TODO : kev -- print all entry names (and corresponding info based on flags) */
// 	(void)directory;
// 	(void)flags;
// 	return ;
// }

// /*
// **    NAME
// **         ft_getdir -- get all entries of a directory
// **
// **    SYNOPSIS
// **         #include <libft.h>
// **
// **         t_vector
// **         ft_getdir(struct s_vector *self);
// **
// **    PARAMETERS
// **
// **         const char dirname[MAX_PATHLEN]      Name of directory.
// **
// **    DESCRIPTION
// **         (not done); get a vector containing all the directory entries of
// **         the 'dirname' directory
// **
// **    RETURN VALUES
// **         If successful returns 0; otherwise -1.
// */

// t_vector		ft_getdir(const char dirname[MAX_PATHLEN])
// {
// /* TODO : Aymen -- add functionality to ft_getdirectory function so that it returns a vector with */
// /*                 t_file struct containing all needed information for each file/dir */

// 	t_vector	directory;
// 	DIR			*dirdes;

// 	directory = vector.empty(NULL);
// 	dirdes = opendir(dirname);
// 	if (dirdes != NULL)
// 	{
// 		directory = ft_getdir(dirdes);
// 		closedir(dirdes);
// 	}
// 	else
// 		perror(NULL);
// 	return (directory);
// }

// /*
// **    NAME
// **         ft_listdir -- list all entries of a directory
// **
// **    SYNOPSIS
// **         #include <libft.h>
// **
// **         int
// **         ft_listdir(const char dirname[MAX_PATHLEN], uint64_t flags,
// **             int (*cmpft)(void *, void *));
// **
// **    PARAMETERS
// **
// **         const char dirname[MAX_PATHLEN]      Name of directory.
// **
// **         uint64_t flags                   Brief
// **
// **         int (*cmpft)(void *, void *)     Brief
// **
// **    DESCRIPTION
// **         Description.
// **
// **    RETURN VALUES
// **         If successful returns 0; otherwise -1.
// */

// void	ft_listdir(const char dirname[MAX_PATHLEN], uint64_t flags,
// 			int (*cmpft)(void *, void *))
// {
// 	t_vector	directory;
// 	size_t		i;

// 	directory = ft_getdirectory(dirname);
// 	if (directory.vector)
// 	{
// 		ft_quicksort(
// 			directory.vector, directory.length, sizeof(void *), cmpft);
// 		print_directory(directory, flags);
// 		if (flags & RR_FLAG)
// 		{
// 			i = 0;
// 			while (i < directory.length)
// 			{
// 				if (((t_file *)directory.vector)[i].type == DIRECTORY)
// 					ft_listdir(((t_file *)directory.vector)[i].name, flags, cmpft);
// 				++i;
// 			}
// 		}
// 		vector.destructor(&directory);
// 	}
// 	return (0);
// }

// /*
// **    NAME
// **         ft_ls -- equivalent to the 'ls' system command
// **
// **    SYNOPSIS
// **         #include <libft.h>
// **
// **         int
// **         ft_ls(int ac, const char *av[], uint64_t flags,
// **             int (*cmpft)(void *, void *));
// **
// **    PARAMETERS
// **
// **         int ac                           Argument count.
// **
// **         const char *av[]                 Argument vector.
// **
// **         uint64_t flags                   Flags.
// **
// **         int (*cmpft)(void *, void *)     Comparasion function
// **                                          used to sort the entries
// **                                          of a directory.
// **
// **    DESCRIPTION
// **         Description.
// **
// **    RETURN VALUES
// **         If successful returns 0; otherwise -1.
// */

// int		ft_ls(int ac, const char *av[], uint64_t flags,
// 			int (*cmpft)(void *, void *))
// {
// 	if (!av || ! cmpft)
// 		return (-1);
// 	if (av && *av)
// 	{
// 		/* TODO: aymen - implement the input into 3: errors, files & directories */
// 	}
// 	else
// 		ft_listdir("./", flags, cmpft);
// 	return (0);
// }

/* —                  ——_— _— _— _— _— _— _— _— _— _— _— _— _— _— _— _— _— _— _— _— _— _— */



	{
		i = 0;
		while (i < directory.length)
		{
			if (((t_file *)directory.vector[i])->type == DIRECTORY)
			{
				ft_printf("%s:\n", ((t_file *)directory.vector[i])->name);
				ft_listdir(
					((t_file *)directory.vector)[i].name, flags, cmpft);
			}
			++i;
		}
	}
