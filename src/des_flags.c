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
	add_flag(&ssl->flag_queue, "-d", d_flag);
	add_flag(&ssl->flag_queue, "-e", e_flag);
	add_flag(&ssl->flag_queue, "-i", i_flag);
	add_flag(&ssl->flag_queue, "-o", o_flag);
	add_flag(&ssl->flag_queue, "-k", key_flag);
	add_flag(&ssl->flag_queue, "-p", password_flag);
	add_flag(&ssl->flag_queue, "-s", salt_flag);
	add_flag(&ssl->flag_queue, "-a", base64_flag);
	if (!flag_handler(ssl, &av))
	{
		if (!ssl->flag_error)
			ssl->flag_error = FLAG_ERR2(*av);
		return (0);
	}
	return (consolidate_des_flags(ssl));
}

/*
**	The consolidate functions can be used to inform the user of required flags
**	and set default flags if no flag was specified.
*/

unsigned int	consolidate_des_flags(t_ssl *ssl)
{
	if (ssl->flag_error)
		return (0);
	ssl->f.e = !ssl->f.d ? 1 : 0;
	if (!ssl->f.p && !ssl->f.k)
		ssl->user_password = get_password_from_user(" ");
	if (!ssl->f.s && (ssl->user_password))
		ssl->user_salt = random_hex_string(PBKDF_SALT_SIZE);
	return (1);
}
