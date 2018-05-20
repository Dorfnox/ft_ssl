/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpierce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 14:12:51 by bpierce           #+#    #+#             */
/*   Updated: 2018/05/19 14:13:01 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

unsigned int		handle_command(t_ssl *ssl, char **av)
{
	int		success;

	success = 0;
	if (SE_("md5", *av) && (success = 1))
	{
		init_command_settings(ssl, "md5", "MD5", VALID_MD5_FLAGS);
		ssl->enc_type = MD5;
		ssl->handle_flags = handle_md5_flags;
		ssl->execute_func = execute_md5;
	}
	else if (SE_("sha256", *av) && (success = 1))
	{
		init_command_settings(ssl, "sha256", "SHA256", VALID_SHA256_FLAGS);
		ssl->enc_type = SHA_256;
		ssl->handle_flags = handle_sha256_flags;
		ssl->execute_func = execute_sha256;
	}
	return (success);
}

void				init_command_settings(
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
