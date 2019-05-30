
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
