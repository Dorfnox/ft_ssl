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

#include "ft_ssl_md5.h"

int					ssl_error(char *name, char *message, int ret_val)
{
	char	*err;

	err = ft_str128(1, "ft_ssl: ");
	err = ft_str128(3, err, name, name ? ": " : "");
	err = ft_str128(2, err, message);
	write(1, err, ft_strlen(err));
	return (ret_val);
}
