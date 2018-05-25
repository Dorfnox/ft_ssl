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
		ssl->input_files = av;
	if (!(consolidate_sha256_flags(ssl)))
		return (0);
	clean_flag_queue(ssl);
	return (1);
}

unsigned int	consolidate_sha256_flags(t_ssl *ssl)
{
	return (ssl->flag_error ? 0 : 1);
}
