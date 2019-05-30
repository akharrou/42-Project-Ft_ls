/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vdprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharrou <akharrou@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 21:41:20 by akharrou          #+#    #+#             */
/*   Updated: 2019/05/30 11:25:44 by akharrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/stdlib_42.h"
#include "../Includes/stdio_42.h"
#include "../Includes/ft_printf.h"

/*
** Reproduction of the libc 'vdprintf()' function.
*/

int				ft_vdprintf(int filedes, const char *format, va_list *args)
{
	char	*output;
	size_t	len;

	len = vasprintf(&output, format, *args);
	write(filedes, output, len);
	return (len);
}
