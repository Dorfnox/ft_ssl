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

unsigned int	p_flag(t_ssl *ssl, char ***av)
{
	(void)av;
	return ((ssl->f.p = 1));
}

unsigned int	q_flag(t_ssl *ssl, char ***av)
{
	(void)av;
	return ((ssl->f.q = 1));
}

unsigned int	r_flag(t_ssl *ssl, char ***av)
{
	(void)av;
	return ((ssl->f.r = 1));
}

unsigned int	s_flag(t_ssl *ssl, char ***av)
{
	++(*av);
	if (!collect_given_parameter(&ssl->given_strings, **av))
	{
		ssl->flag_error = FLAG_ERR1("-s");
		return (0);
	}
	return ((ssl->f.s = 1));
}
