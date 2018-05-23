/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_flags.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpierce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 15:00:29 by bpierce           #+#    #+#             */
/*   Updated: 2018/05/21 13:28:50 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

unsigned int	handle_base64_flags(t_ssl *ssl, char **av)
{
	while (*av)
	{
		if (SE_2(*av, "-d", "-e"))
		{
			if (!(handle_base64_regular_flags(ssl, av)))
				return (0);
		}
		else if (SE_2(*av, "-i", "-o"))
		{
			if (!(SE_(*av, "-i") ? i_flag(ssl, &av) : o_flag(ssl, &av)))
				return (0);
		}
		else
			return ((ssl->flag_error = FLAG_ERR2(*av)) ? 0 : 0);
		++av;
	}
	ssl->f.e = ssl->f.d ? 0 : 1;
	return (1);
}

unsigned int	handle_base64_regular_flags(t_ssl *ssl, char **av)
{
	if (SE_("-d", *av))
	{
		if (ssl->f.e && (ssl->flag_error = FLAG_ERR3("-e")))
			return (0);
		return ((ssl->f.d = 1));
	}
	else if (SE_("-e", *av))
	{
		if (ssl->f.d && (ssl->flag_error = FLAG_ERR3("-d")))
			return (0);
		return ((ssl->f.e = 1));
	}
	return (0);
}
