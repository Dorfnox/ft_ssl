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

unsigned int	handle_des_flags(t_ssl *ssl, char **av)
{
	ssl->flag_queue = initq();
	enqueue(ssl->flag_queue, d_flag);
	enqueue(ssl->flag_queue, e_flag);
	enqueue(ssl->flag_queue, i_flag);
	enqueue(ssl->flag_queue, o_flag);
	enqueue(ssl->flag_queue, k_flag);
	if (!flag_handler(ssl, &av))
	{
		if (!ssl->flag_error)
			ssl->flag_error = FLAG_ERR2(*av);
		return (0);
	}
	if (!(consolidate_des_flags(ssl)))
		return (0);
	clean_flag_queue(ssl);
	return (1);
}

/*
**	The consolidate functions can be used to inform the user of required flags
**	and set default flags if no flag was specified.
*/

unsigned int	consolidate_des_flags(t_ssl *ssl)
{
	ssl->f.e = !ssl->f.d ? 1 : 0;
	if (!ssl->f.k)
		ssl->flag_error = ft_str256(2, ft_str256(0), ERROR_HEX1);
	return (ssl->flag_error ? 0 : 1);
}
