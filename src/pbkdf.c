/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pbkdf.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpierce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 16:17:28 by bpierce           #+#    #+#             */
/*   Updated: 2018/05/26 16:31:17 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
**	Returns a key using the password, salt, and stuffs.
*/

char		*pbkdf(t_ssl *ssl)
{
	char	*(*algo)(t_ssl *ssl, char *input);
	t_pbkdf p;
	int		pass_len;

	p.algo = PBKDF_ALGO;
	p.salt = str_to_64bit(ssl->user_salt, NULL);
	p.salt_size = PBKDF_SALT_SIZE;
	pass_len = ft_strlen(ssl->user_password);
	(void)algo;
	return (NULL);
}
