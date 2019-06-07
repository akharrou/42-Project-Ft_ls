/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharrou <akharrou@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 19:20:24 by akharrou          #+#    #+#             */
/*   Updated: 2019/06/06 22:28:01 by akharrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libft/Includes/libft.h"

void	usage(void)
{
	ft_printf("usage: ./ft_ls [ -1LRSacfilprtu ] [ file ... ]\n");
}

void	unknown_flag(char unknown_flag)
{
	ft_printf("./ft_ls: illegal option -- %c\n", unknown_flag);
	usage();
}
