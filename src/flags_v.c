/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_v.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpierce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 15:44:40 by bpierce           #+#    #+#             */
/*   Updated: 2018/07/12 15:00:30 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
**	Handling for the -v flag, the initialization vector
*/

unsigned int	vector_flag(t_ssl *ssl, char ***av)
{
	if (ssl->f.v && (ssl->flag_error = FLAG_ERR4("-v")))
		return (0);
	++(*av);
	if (!**av)
	{
		ssl->flag_error = ft_str256(2, FLAG_ERR1("-v"), VECTOR_ERR1);
		return (0);
	}
	ssl->user_iv = get_vector_from_user(**av);
	return (!ssl->user_iv ? 0 : (ssl->f.v = 1));
}

char			*get_vector_from_user(char *given_vector)
{
	char	*vector;
	int		i;

	vector = ft_strnew(PBKDF_VECTOR_SIZE + 1);
	if (!(ft_strncpy(vector, given_vector, PBKDF_VECTOR_SIZE)))
	{
		free(vector);
		return (NULL);
	}
	vector[PBKDF_VECTOR_SIZE] = '\0';
	ft_strtoupper(&vector);
	while (!vector_is_valid(vector))
	{
		ft_bzero(vector, PBKDF_VECTOR_SIZE + 1);
		readpassphrase(VECTOR_ERROR, vector,
			PBKDF_VECTOR_SIZE + 1, RPP_FORCEUPPER);
		ft_putstr("-------------------------------------------\n");
	}
	if ((i = ft_strlen(vector)) < PBKDF_VECTOR_SIZE)
		while (i < PBKDF_VECTOR_SIZE)
			vector[i++] = '0';
	return (vector);
}

int				vector_is_valid(char *vector)
{
	char	*hex;
	int		i;
	int		strlen;

	if (!vector || ((strlen = ft_strlen(vector)) < 1))
		return (0);
	hex = "0123456789ABCDEF";
	i = -1;
	while (++i < strlen)
	{
		if (!ft_strchr(hex, vector[i]))
			return (0);
	}
	return (1);
}
