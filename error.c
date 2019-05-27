/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharrou <akharrou@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 18:45:56 by akharrou          #+#    #+#             */
/*   Updated: 2019/05/26 19:02:16 by akharrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libft/Includes/libft.h"

void	usage(void)
{
	ft_printf("usage: ./ft_ls [ -Ralrt1 ] [ file ... ]\n");
	exit(EXIT_FAILURE);
}

void	error(void)
{
	perror(NULL);
	exit(EXIT_FAILURE);
}
