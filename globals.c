/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharrou <akharrou@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 19:20:33 by akharrou          #+#    #+#             */
/*   Updated: 2019/06/11 12:42:01 by akharrou         ###   ########.fr       */
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
	{ '1', _1_FLAG },
	{ 'R', R_FLAG },
	{ 'L', L_FLAG },
	{ 'l', l_FLAG },
	{ 'a', a_FLAG },
	{ 'r', r_FLAG },
	{ 't', t_FLAG },
	{ 'u', u_FLAG },
	{ 'U', U_FLAG },
	{ 'c', c_FLAG },
	{ 'p', p_FLAG },
	{ 'i', i_FLAG },
	{ 'g', g_FLAG },
	{ 'S', S_FLAG },
	{ 'f', f_FLAG },
	\
	{ '\0', 0 }
};
