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

char		*execute_base64(t_ssl *s, char *in, t_io_len *l)
{
	if (s->f.e)
		return (base64_encrypt(in, l->in_len, &l->out_len));
	return (base64_decrypt(in, l->in_len, &l->out_len));
}

char		*base64_encrypt(char *input, size_t in_len, size_t *o_len)
{
	t_base64	b;
	char		*t;
	char		*output;

	t = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	*o_len = 4 * ((in_len + 2) / 3);
	!(output = ft_strnew(*o_len)) ? malloc_error("creating base64 output") : 0;
	b.i = 0;
	b.j = -1;
	while (b.i < in_len && (b.k = -1))
	{
		b.res_a = b.i < in_len ? (uint8_t)input[b.i++] : 0;
		b.res_b = b.i < in_len ? (uint8_t)input[b.i++] : 0;
		b.res_c = b.i < in_len ? (uint8_t)input[b.i++] : 0;
		b.res_d = (b.res_a << 16) | (b.res_b << 8) | b.res_c;
		while (++b.k < 4)
			output[++b.j] = t[(b.res_d >> (18 - (6 * b.k))) & 0x3F];
	}
	output[*o_len - 1] = b.res_c == 0 ? '=' : output[*o_len - 1];
	output[*o_len - 2] = b.res_b == 0 ? '=' : output[*o_len - 2];
	return (output);
}

char		*base64_decrypt(char *input, size_t in_len, size_t *o_len)
{
	t_base64	b;
	char		*output;
	int			*t;

	if (!(t = get_decrypt_table(input, in_len, o_len)))
		return (NULL);
	if (!(output = ft_strnew(*o_len)))
		return (NULL);
	b.i = 0;
	b.j = -1;
	while (b.i < in_len && (b.k = -1))
	{
		b.res_a = input[b.i] != '=' ? t[(int)input[b.i++]] : 0 & ++b.i;
		b.res_b = input[b.i] != '=' ? t[(int)input[b.i++]] : 0 & ++b.i;
		b.res_c = input[b.i] != '=' ? t[(int)input[b.i++]] : 0 & ++b.i;
		b.res_d = input[b.i] != '=' ? t[(int)input[b.i++]] : 0 & ++b.i;
		b.res_e = (b.res_a << 18) + (b.res_b << 12) + (b.res_c << 6) + b.res_d;
		while (++b.k < 3 && ++b.j < *o_len)
			output[b.j] = (char)((b.res_e >> (16 - (8 * b.k))) & 0xFF);
	}
	return (output);
}

/*
**	Creates a decrypt table for all characters present in the input
*/

int			*get_decrypt_table(char *input, size_t in_len, size_t *o_len)
{
	static int	table[256];
	char		*t;
	int			count;

	t = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	count = -1;
	while (++count < 64)
		table[(int)t[count]] = count;
	*o_len = 3 * (in_len / 4);
	*o_len -= input[in_len - 1] == '=' ? 1 : 0;
	*o_len -= input[in_len - 2] == '=' ? 1 : 0;
	return (table);
}
