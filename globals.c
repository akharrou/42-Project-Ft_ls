/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharrou <akharrou@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 19:20:33 by akharrou          #+#    #+#             */
/*   Updated: 2019/06/04 21:45:52 by akharrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**    DESCRIPTION
**         Dispatch table associating every flag with the
**         unique bit it is represented by & its comparsion.
**         function if it has one.
*/

t_flag g_flags[] =
{
	{ '1', _1_FLAG, compare_by_ascii, reverse_compare_by_ascii },
	{ 'R', R_FLAG, compare_by_ascii, reverse_compare_by_ascii },
	{ 'l', l_FLAG, compare_by_ascii, reverse_compare_by_ascii },
	{ 'a', a_FLAG, compare_by_ascii, reverse_compare_by_ascii },
	{ 'r', r_FLAG, compare_by_ascii, reverse_compare_by_ascii },
	{ 't', t_FLAG, &compare_by_mtime, &reverse_compare_by_mtime },
	{ 'u', u_FLAG, &compare_by_atime, &reverse_compare_by_atime },
	{ 'c', c_FLAG, &compare_by_ctime, &reverse_compare_by_ctime },
	{ 's', S_FLAG, &compare_by_size, &reverse_compare_by_size },
	{ 'f', f_FLAG, &compare_by_none, &compare_by_none },
	\
	{ '\0', 0, NULL, NULL }
};
