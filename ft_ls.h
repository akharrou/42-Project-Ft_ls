/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharrou <akharrou@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 13:53:43 by akharrou          #+#    #+#             */
/*   Updated: 2019/05/26 19:35:09 by akharrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
** Header File(s).
*/

# include "Libft/Includes/libft.h"

# include <sys/types.h>
# include <dirent.h>
# include <stdio.h>

/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
** Macro(s).
*/


/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
** Structure(s).
*/

typedef struct	s_ft_ls_information
{

}				t_ls;

typedef struct	s_ls_file
{
	uint32_t	month;
	uint32_t	day;
	uint32_t	hour;
	uint32_t	minute;
	\
	uint32_t	filemode;
	uint32_t	links;
	uint32_t	owner;
	uint32_t	group;
	\
	size_t		total_bytes;
	\
	char		name[NAMEMAX + 1];
}				t_ls_file;

typedef struct	s_ls_order
{
	char *name;
	/* function pointer to comparasion function */
}				t_ls_order;

extern t_ls_orders[] = {

	{ "l", &cmp_lexicographically },
	{ "t", &cmp_time },
	{ "f", &cmp_none }
}

/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
** Global(s).
*/


/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
** Main Function(s).
*/


/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
** Utility Function(s).
*/


/*
** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **
*/

#endif
