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

unsigned int	salt_flag(t_ssl *ssl, char ***av)
{
	if (ssl->f.s && (ssl->flag_error = FLAG_ERR4("-s")))
		return (0);
	if (ssl->f.k && (ssl->flag_error = FLAG_ERR3("-s", "-k")))
		return (0);
	++(*av);
	if (!**av)
	{
		ssl->flag_error = ft_str256(2, FLAG_ERR1("-s"), SALT_ERR1);
		return (0);
	}
	ssl->user_salt = get_salt_from_user(**av);
	return (!ssl->user_salt ? 0 : (ssl->f.s = 1));
}

char		*get_salt_from_user(char *given_salt)
{
	char	*salt;
	int		i;

	salt = ft_strnew(PBKDF_SALT_SIZE + 1);
	if (!(ft_strncpy(salt, given_salt, PBKDF_SALT_SIZE)))
	{
		free(salt);
		return (NULL);
	}
	salt[PBKDF_SALT_SIZE] = '\0';
	ft_strtoupper(&salt);
	while (!salt_is_valid(salt))
	{
		ft_bzero(salt, PBKDF_SALT_SIZE + 1);
		readpassphrase(SALT_ERROR, salt, PBKDF_SALT_SIZE + 1, RPP_FORCEUPPER);
		ft_putstr("-------------------------------------------\n");
	}
	if ((i = ft_strlen(salt)) < PBKDF_SALT_SIZE)
		while (i < PBKDF_SALT_SIZE)
			salt[i++] = '0';
	return (salt);
}

int			salt_is_valid(char *salt)
{
	char	*hex;
	int		i;
	int		strlen;

	if (!salt || ((strlen = ft_strlen(salt)) < 1))
		return (0);
	hex = "0123456789ABCDEF";
	i = -1;
	while (++i < strlen)
	{
		if (!ft_strchr(hex, salt[i]))
			return (0);
	}
	return (1);
}
