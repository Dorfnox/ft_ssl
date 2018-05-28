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
	add_flag(&ssl->flag_queue, "-d", d_flag);
	add_flag(&ssl->flag_queue, "-e", e_flag);
	add_flag(&ssl->flag_queue, "-i", i_flag);
	add_flag(&ssl->flag_queue, "-o", o_flag);
	if (!flag_handler(ssl, &av))
	{
		if (!ssl->flag_error)
			ssl->flag_error = FLAG_ERR2(*av);
		return (0);
	}
	if (!(consolidate_base64_flags(ssl)))
		return (0);
	return (1);
}

unsigned int	consolidate_base64_flags(t_ssl *ssl)
{
	ssl->f.e = !ssl->f.d ? 1 : 0;
	return (ssl->flag_error ? 0 : 1);
}
