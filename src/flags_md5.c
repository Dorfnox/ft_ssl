/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_md5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpierce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 15:00:29 by bpierce           #+#    #+#             */
/*   Updated: 2018/05/19 15:00:36 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

unsigned int	handle_md5_flags(t_ssl *ssl, char **av)
{
	while (*av)
	{
		if (handle_md5_regular_flags(ssl, av))
			;
		else if (SE_("-s", *av))
		{
			ssl->f.s = collect_given_parameter(&ssl->given_strings, *(++av));
			if (!ssl->f.s)
				return ((ssl->flag_error = FLAG_ERR1) ? 0 : 0);
		}
		else if (CE_('-', **av))
			return ((ssl->flag_error = FLAG_ERR2) ? 0 : 0);
		else
		{
			ssl->input_files = av;
			break ;
		}
		++av;
	}
	return (1);
}

unsigned int	handle_md5_regular_flags(t_ssl *ssl, char **av)
{
	if (SE_("-p", *av))
		return ((ssl->f.p = 1));
	else if (SE_("-q", *av))
		return ((ssl->f.q = 1));
	else if (SE_("-r", *av))
		return ((ssl->f.r = 1));
	return (0);
}
