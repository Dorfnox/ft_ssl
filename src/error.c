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

int		ssl_error(char *name, char *message, int ret_val)
{
	char	*err;

	err = ft_str1024(1, "ft_ssl: ");
	err = ft_str1024(3, err, name, name ? ": " : "");
	err = ft_str1024(2, err, message);
	write(1, err, ft_strlen(err));
	return (ret_val);
}

void	clean_up(t_ssl *ssl)
{
	free(ssl->given_strings);
}

void	malloc_error(char *message)
{
	message ? ft_pflite("ft_ssl: Malloc Eror: %s\n", message) : 0;
	exit(1);
}