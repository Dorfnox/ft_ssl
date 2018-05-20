/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_sha256.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpierce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 15:00:44 by bpierce           #+#    #+#             */
/*   Updated: 2018/05/19 15:00:50 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

unsigned int		handle_sha256_flags(t_ssl *ssl, char **av)
{
	while (*av)
	{
		if (SE_("-p", *av))
			ssl->f.p = 1;
		else if (SE_("-q", *av))
			ssl->f.q = 1;
		else if (SE_("-r", *av))
			ssl->f.r = 1;
		else if (SE_("-s", *av))
		{
			ssl->f.s = 1;
			if (!collect_given_parameter(&ssl->given_strings, *(++av)))
				return ((ssl->flag_error = FLAG_ERROR1) ? 0 : 0);
		}
		else if (CE_('-', **av))
			return ((ssl->flag_error = FLAG_ERROR2) ? 0 : 0);
		else
		{
			ssl->input_files = av;
			break ;
		}
		++av;
	}
	return (1);
}
