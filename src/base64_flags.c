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
		if (handle_base64_regular_flags(ssl, av))
			;
		else if (SE_("-i", *av))
		{
			if (!handle_i_parameter(ssl, ++av))
				return (0);
		}
		else if (SE_("-o", *av))
		{
			if (!handle_o_parameter(ssl, ++av))
				return (0);
		}
		else
			return ((ssl->flag_error = FLAG_ERR2(*av)) ? 0 : 0);
		++av;
	}
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

unsigned int	handle_i_parameter(t_ssl *ssl, char **av)
{
	if (!*av && (ssl->flag_error = FLAG_ERR1("-i")))
		return (0);
	if (ssl->f.i && (ssl->flag_error = FLAG_ERR4("-i")))
		return (0);
	ssl->in_file = *av;
	return (1);
}

unsigned int	handle_o_parameter(t_ssl *ssl, char **av)
{
	if (!*av && (ssl->flag_error = FLAG_ERR1("-o")))
		return (0);
	if (ssl->f.o && (ssl->flag_error = FLAG_ERR4("-o")))
		return (0);
	ssl->out_file = *av;
	return (1);
}
