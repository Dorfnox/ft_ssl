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
	add_flag(&ssl->flag_queue, "-p", p_flag);
	add_flag(&ssl->flag_queue, "-q", q_flag);
	add_flag(&ssl->flag_queue, "-r", r_flag);
	add_flag(&ssl->flag_queue, "-s", s_flag);
	if (!flag_handler(ssl, &av))
		ssl->input_files = av;
	if (!(consolidate_md5_flags(ssl)))
		return (0);
	return (1);
}

unsigned int	consolidate_md5_flags(t_ssl *ssl)
{
	return (ssl->flag_error ? 0 : 1);
}
