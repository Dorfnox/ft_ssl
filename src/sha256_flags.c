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

unsigned int	handle_sha256_flags(t_ssl *ssl, char **av)
{
	ssl->flag_queue = initq();
	enqueue(ssl->flag_queue, p_flag);
	enqueue(ssl->flag_queue, q_flag);
	enqueue(ssl->flag_queue, r_flag);
	enqueue(ssl->flag_queue, s_flag);
	if (!flag_handler(ssl, &av))
	{
		if (ssl->flag_error)
			return (0);
		if (CE_('-', **av))
			return ((ssl->flag_error = FLAG_ERR2(*av)) ? 0 : 0);
		ssl->input_files = av;
	}
	consolidate_sha256_flags(ssl);
	clean_flag_queue(ssl);
	return (1);
}

void			consolidate_sha256_flags(t_ssl *ssl)
{
	(void)ssl;
}
