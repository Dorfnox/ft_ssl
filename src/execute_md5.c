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
**	The main loop for handling md5
*/

char			*execute_md5(t_ssl *ssl, char *input)
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

void			execute_md5_(t_md5 *md5, int j)
{
	if (j < 16)
	{
		md5->f = MD5_F1(md5->b2, md5->c2, md5->d2);
		md5->g = j;
	}
	else if (j < 32)
	{
		md5->f = MD5_F2(md5->b2, md5->c2, md5->d2);
		md5->g = (5 * j + 1) % 16;
	}
	else if (j < 48)
	{
		md5->f = MD5_F3(md5->b2, md5->c2, md5->d2);
		md5->g = (3 * j + 5) % 16;
	}
	else
	{
		md5->f = MD5_F4(md5->b2, md5->c2, md5->d2);
		md5->g = (7 * j) % 16;
	}
	md5->f = md5->f + md5->a2 + md5->k[j] + md5->m[md5->g];
	md5->a2 = md5->d2;
	md5->d2 = md5->c2;
	md5->c2 = md5->b2;
	md5->b2 = md5->b2 + LEFT_ROTATE(md5->f, md5->s[j]);
}

/*
**	append_bits_and_create_data:
**	-------------------------------
**
**	Calculates the num of bytes needed to be added to the character string.
**	Mainly works with bytes because input is assumed to be a character string.
**	1) adds a single bit of 1.
**	2) adds enough bytes of '0' value to fill 448 bits (when modulo with 512)
**	3) adds the 'Length' as a 64-bit number.
**	4) if length is 24, it appends:
**	0001100000000000000000000000000000000000000000000000000000000000
**	as the last 64 bits.
*/

void			append_bits_md5(t_ssl *ssl, t_md5 *md5, char *input)
{
	size_t		num_of_bytes;
	uint64_t	original_len_in_bits;

	original_len_in_bits = ssl->input_len * 8;
	num_of_bytes = original_len_in_bits + 1;
	while (num_of_bytes % 512 != 448)
		++num_of_bytes;
	num_of_bytes /= 8;
	md5->data = ft_memalloc(num_of_bytes + 64);
	ft_memcpy(md5->data, input, ssl->input_len);
	md5->data[ssl->input_len] = 0b10000000;
	ft_memcpy(md5->data + num_of_bytes, &original_len_in_bits, 8);
	ssl->input_len = num_of_bytes + 8;
}

char			*build_md5_output(t_md5 *md5)
{
	char			*hex_string;
	char			*output;
	int				i;
	unsigned int	j;
	t_32bitunion	u;

	hex_string = "0123456789abcdef";
	if (!(output = malloc(sizeof(char) * 33)))
		return (NULL);
	j = 0;
	i = 0;
	while (i < 32)
	{
		u.v = i < 24 ? md5->c : md5->d;
		u.v = i < 16 ? md5->b : u.v;
		u.v = i < 8 ? md5->a : u.v;
		output[i++] = hex_string[u.p8[j % 4] >> 4];
		output[i++] = hex_string[u.p8[j++ % 4] & 15];
	}
	output[32] = 0;
	return (output);
}

void			clean_md5(t_md5 *md5)
{
	free(md5->data);
}
