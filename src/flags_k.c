/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpierce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 15:44:40 by bpierce           #+#    #+#             */
/*   Updated: 2018/05/22 15:44:48 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

unsigned int	key_flag(t_ssl *ssl, char ***av)
{
	if (ssl->f.k && (ssl->flag_error = FLAG_ERR4("-k")))
		return (0);
	if (ssl->f.p && (ssl->flag_error = FLAG_ERR3("-k", "-p")))
		return (0);
	++(*av);
	if (!**av)
	{
		ssl->flag_error = ft_str256(2, FLAG_ERR1("-k"), HEX_ERR1);
		return (0);
	}
	ssl->user_key = get_key_from_user(**av);
	return ((ssl->f.k = 1));
}

char			*get_key_from_user(char *given_key)
{
	char	*key;
	int		i;

	key = ft_strnew(17);
	if (!(ft_strncpy(key, given_key, 16)))
	{
		free(key);
		return (NULL);
	}
	key[16] = '\0';
	ft_strtoupper(&key);
	while (!key_is_valid(key))
	{
		ft_bzero(key, 17);
		readpassphrase(HEX_ERROR, key, 17, RPP_FORCEUPPER);
		ft_putstr("-------------------------------------------\n");
	}
	if ((i = ft_strlen(key)) < 16)
		while (i < 16)
			key[i++] = '0';
	return (key);
}

int				key_is_valid(char *key)
{
	char	*hex;
	int		i;
	int		strlen;

	if (!key || ((strlen = ft_strlen(key)) < 1))
		return (0);
	hex = "0123456789ABCDEF";
	i = -1;
	while (++i < strlen)
	{
		if (!ft_strchr(hex, key[i]))
			return (0);
	}
	return (1);
}
