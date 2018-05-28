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

/*
** This p flag handles the 'password' for des encryption.
*/

unsigned int	password_flag(t_ssl *ssl, char ***av)
{
	if (ssl->f.p && (ssl->flag_error = FLAG_ERR4("-p")))
		return (0);
	if (ssl->f.k && (ssl->flag_error = FLAG_ERR3("-p", "-k")))
		return (0);
	++(*av);
	if (!**av)
	{
		ssl->flag_error = ft_str256(2, FLAG_ERR1("-p"), PASSWORD_ERR1);
		return (0);
	}
	ssl->user_password = get_password_from_user(**av);
	return (!ssl->user_password ? 0 : (ssl->f.p = 1));
}

/*
**	mallocs a size of 126 to hold salting for later.
*/

char		*get_password_from_user(char *given_password)
{
	char	*password;
	char	pass_confirm[PBKDF_PASSWORD_SIZE];

	password = ft_strnew(PBKDF_PASSWORD_SIZE + PBKDF_SALT_SIZE);
	if (!(ft_strncpy(password, given_password, PBKDF_PASSWORD_SIZE)))
	{
		free(password);
		return (NULL);
	}
	password[PBKDF_PASSWORD_SIZE] = '\0';
	while (strlen(ft_strremove(password, " \t\r\n\v\f")) < 1)
	{
		ft_bzero(password, PBKDF_PASSWORD_SIZE);
		readpassphrase(PASSWORD_ERROR,
			password, PBKDF_PASSWORD_SIZE + 1, RPP_FORCEUPPER);
		ft_putstr("-------------------------------------------\n");
	}
	readpassphrase("Please [92mconfirm your password[0m: ",
		pass_confirm, PBKDF_PASSWORD_SIZE + 1, RPP_FORCEUPPER);
	if (!(ft_strequ(pass_confirm, password)))
		ft_strdel(&password);
	!password ? write(1, "PASSWORD VERIFICATION FAILED\n", 29) : 0;
	return (password);
}
