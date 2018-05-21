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
	unsigned int	success;

	success = 0;
	if (SE_("md5", *av) && (success = 1))
	{
		init_command_settings(ssl, "md5", "MD5", VALID_MD5_FLAGS);
		ssl->handle_flags = handle_md5_flags;
		ssl->execute_func = execute_md5;
	}
	else if (SE_("sha256", *av) && (success = 1))
	{
		init_command_settings(ssl, "sha256", "SHA256", VALID_SHA256_FLAGS);
		ssl->handle_flags = handle_sha256_flags;
		ssl->execute_func = execute_sha256;
	}
	else if (SE_("sha224", *av) && (success = 1))
	{
		init_command_settings(ssl, "sha224", "SHA224", VALID_SHA224_FLAGS);
		ssl->handle_flags = handle_sha256_flags;
		ssl->execute_func = execute_sha224;
	}
	else
		ft_pflite("ft_ssl: error: '%s' is an invalid command.\n\n", *av);
	return (success);
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
