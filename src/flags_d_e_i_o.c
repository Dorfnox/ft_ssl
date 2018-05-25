/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpierce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 15:44:40 by bpierce           #+#    #+#             */
/*   Updated: 2018/05/22 15:44:48 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

unsigned int	d_flag(t_ssl *ssl, char ***av)
{
	(void)av;
	if (ssl->f.e && (ssl->flag_error = FLAG_ERR3("-d", "-e")))
		return (0);
	return ((ssl->f.d = 1));
}

unsigned int	e_flag(t_ssl *ssl, char ***av)
{
	(void)av;
	if (ssl->f.d && (ssl->flag_error = FLAG_ERR3("-e", "-d")))
		return (0);
	return ((ssl->f.e = 1));
}

unsigned int	i_flag(t_ssl *ssl, char ***av)
{
	if (ssl->f.i && (ssl->flag_error = FLAG_ERR4("-i")))
		return (0);
	++(*av);
	if (!**av && (ssl->flag_error = FLAG_ERR1("-i")))
		return (0);
	ssl->in_file = **av;
	return ((ssl->f.i = 1));
}

unsigned int	o_flag(t_ssl *ssl, char ***av)
{
	if (ssl->f.o && (ssl->flag_error = FLAG_ERR4("-o")))
		return (0);
	++(*av);
	if (!**av && (ssl->flag_error = FLAG_ERR1("-o")))
		return (0);
	ssl->out_file = **av;
	return ((ssl->f.o = 1));
}
