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

/*
**	The main loop for handling base64
*/

char		*execute_base64(t_ssl *ssl, char *input)
{
	t_md5		md5;
	size_t		i;
	int			j;

	init_md5(&md5);
	append_bits_md5(ssl, &md5, input);
	i = 0;
	while (i < ((ssl->input_len * 8) / 512))
	{
		ft_memcpy(md5.m, &md5.data[i++ * 64], 64);
		md5.a2 = md5.a;
		md5.b2 = md5.b;
		md5.c2 = md5.c;
		md5.d2 = md5.d;
		j = -1;
		while (++j < 64)
			execute_md5_(&md5, j);
		md5.a += md5.a2;
		md5.b += md5.b2;
		md5.c += md5.c2;
		md5.d += md5.d2;
	}
	clean_md5(&md5);
	return (build_md5_output(&md5));
}

void		clean_base64(t_md5 *md5)
{
	free(md5->data);
}
