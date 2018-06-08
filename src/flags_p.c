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
**	mallocs a size to hold both the password and the concatenated salt
*/

char		*get_password_from_user(char *given_pass)
{
	char	*pass;
	char	pass_confirm[PBKDF_PASSWORD_SIZE];
	int		k;

	pass = ft_strnew(PBKDF_PASSWORD_SIZE + PBKDF_SALT_SIZE);
	if (!(ft_strncpy(pass, given_pass, PBKDF_PS)) || (k = 0))
	{
		free(pass);
		return (NULL);
	}
	pass[PBKDF_PASSWORD_SIZE] = '\0';
	while (ft_strlen(ft_strremove(pass, " \t\r\n\v\f")) < 1 && (k = 1))
	{
		ft_bzero(pass, PBKDF_PS);
		readpassphrase(PASSWORD_ERROR, pass, PBKDF_PS + 1, RPP_FORCEUPPER);
	}
	k == 1 ? readpassphrase("Please [92mconfirm your password[0m: ",
		pass_confirm, PBKDF_PS + 1, RPP_FORCEUPPER) : 0;
	if (k == 1 && !(ft_strequ(pass_confirm, pass)))
		ft_strdel(&pass);
	!pass ? write(1, "PASSWORD VERIFICATION FAILED\n", 29) : 0;
	return (pass);
}
