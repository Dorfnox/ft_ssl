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
	ssl->flag_queue = initq();
	enqueue(ssl->flag_queue, d_flag);
	enqueue(ssl->flag_queue, e_flag);
	enqueue(ssl->flag_queue, i_flag);
	enqueue(ssl->flag_queue, o_flag);
	if (!flag_handler(ssl, &av))
	{
		if (!ssl->flag_error)
			ssl->flag_error = FLAG_ERR2(*av);
		return (0);
	}
	if (!(consolidate_base64_flags(ssl)))
		return (0);
	clean_flag_queue(ssl);
	return (1);
}

unsigned int	consolidate_base64_flags(t_ssl *ssl)
{
	ssl->f.e = !ssl->f.d ? 1 : 0;
	return (ssl->flag_error ? 0 : 1);
}
