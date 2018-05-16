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

char			*execute_md5(t_ssl *ssl, char **input)
{
	t_md5	md5;

	init_md5(&md5);
	append_bits_to_input(input);
	(void)ssl;
	(void)input;
	return (NULL);
}

void			append_bits_to_input(char **input)
{
	int		bitlen;
	int		last;
	int		num_of_bits_to_add;
	char	*padding;

	bitlen = ft_strlen(*input) * 8;
	last = (bitlen + 1) % 512;
	DBI(last);
	num_of_bits_to_add = 0;
	if (last > 448)
		num_of_bits_to_add = 512 - (512 - last);
	else if (last < 448)
		num_of_bits_to_add = 448 - last;
	++num_of_bits_to_add;
	DBI(num_of_bits_to_add);
	(void)padding;
}
