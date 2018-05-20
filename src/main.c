/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpierce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:57:13 by bpierce           #+#    #+#             */
/*   Updated: 2018/03/30 20:57:13 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int		main(int ac, char **av)
{
	t_ssl	ssl;

	if (ac == 1)
		return (ssl_error(NULL, USAGE, 1));
	ft_bzero(&ssl, sizeof(t_ssl));
	if (!(handle_command(&ssl, av + 1)))
	{
		return (ssl_error(NULL, COMMANDS, 1));
	}
	if (!(ssl.handle_flags(&ssl, av + 2)))
	{
		return (ssl_error(ssl.cmd_name_lower, ssl.flag_error, 1));
	}
	execute_all(&ssl);
	clean_up(&ssl);
	// while (1)
	// 	;
	return (0);
}
