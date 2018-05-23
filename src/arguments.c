/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpierce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 15:03:02 by bpierce           #+#    #+#             */
/*   Updated: 2018/05/19 15:03:09 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
**	Main command handler functions
*/

unsigned int	handle_command(t_ssl *ssl, char **av)
{
	if (SE_("md5", *av) && (ssl->execute_func = execute_message_digest))
	{
		init_command_settings(ssl, "md5", "MD5", VALID_MD5_FLAGS);
		ssl->handle_flags = handle_md5_flags;
		ssl->enc_func = execute_md5;
	}
	else if (SE_("sha256", *av) && (ssl->execute_func = execute_message_digest))
	{
		init_command_settings(ssl, "sha256", "SHA256", VALID_SHA256_FLAGS);
		ssl->handle_flags = handle_sha256_flags;
		ssl->enc_func = execute_sha256;
	}
	else if (SE_("sha224", *av) && (ssl->execute_func = execute_message_digest))
	{
		init_command_settings(ssl, "sha224", "SHA224", VALID_SHA224_FLAGS);
		ssl->handle_flags = handle_sha256_flags;
		ssl->enc_func = execute_sha224;
	}
	return (ssl->execute_func ? 1 : handle_command_2(ssl, av));
}

unsigned int	handle_command_2(t_ssl *ssl, char **av)
{
	if (SE_("base64", *av) && (ssl->execute_func = execute_cipher))
	{
		init_command_settings(ssl, "base64", "BASE64", VALID_BASE64_FLAGS);
		ssl->handle_flags = handle_base64_flags;
		ssl->enc_func = execute_base64;
	}
	else if (SE_("des-ecb", *av) && (ssl->execute_func = execute_cipher))
	{
		init_command_settings(ssl, "des-ecb", "DES-ECB", VALID_DES_FLAGS);
		ssl->handle_flags = handle_des_flags;
		ssl->enc_func = execute_base64;
	}
	else
		ssl->flag_error = FLAG_ERR0(*av);
	return (ssl->execute_func ? 1 : 0);
}

void			init_command_settings(
					t_ssl *ssl, char *sn, char *ln, char *valid_flags)
{
	static char	command_lowercase[MAX_COMMAND_SIZE];
	static char	command_uppercase[MAX_COMMAND_SIZE];
	static char	command_valid_flags[MAX_COMMAND_SIZE];
	int			i;

	i = -1;
	while (sn[++i] || !(i = -1))
		command_lowercase[i] = sn[i];
	while (ln[++i] || !(i = -1))
		command_uppercase[i] = ln[i];
	while (valid_flags[++i])
		command_valid_flags[i] = valid_flags[i];
	ssl->cmd_name_lower = command_lowercase;
	ssl->cmd_name_upper = command_uppercase;
	ssl->cmd_valid_flags = command_valid_flags;
}

/*
**	Stores the given parameter in the given ***array
**	Will reallocate **save if things already exist in the deferenced array
*/

unsigned int	collect_given_parameter(char ***save, char *param)
{
	char	**tmp;
	int		i;

	if (!param || !save)
		return (0);
	if ((tmp = *save))
	{
		i = -1;
		while (tmp[++i])
			;
		tmp = malloc(sizeof(char *) * (i + 2));
		ft_memcpy(tmp, *save, sizeof(char *) * i);
		tmp[i] = param;
		tmp[i + 1] = NULL;
	}
	else
	{
		tmp = malloc(sizeof(char *) * 2);
		tmp[0] = param;
		tmp[1] = NULL;
	}
	free(*save);
	*save = tmp;
	return (1);
}
