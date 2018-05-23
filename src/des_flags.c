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
		return (0);
	consolidate_des_flags(ssl);
	clean_flag_queue(ssl);
	return (1);
}

void			consolidate_des_flags(t_ssl *ssl)
{
	ssl->f.e = ssl->f.d ? 0 : 1;
}
