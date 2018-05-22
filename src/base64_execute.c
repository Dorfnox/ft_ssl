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
	return (ssl->f.e ? base64_encrypt(ssl, input) : base64_decrypt(ssl, input));
}

char		*base64_encrypt(t_ssl *ssl, char *input)
{
	t_base64	b;
	char		*t;
	char		*output;

	t = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	b.input_len = (int)ssl->input_len;
	b.output_len = 4 * ((b.input_len + 2) / 3);
	if (!(output = ft_strnew(b.output_len)))
		return (NULL);
	b.i = 0;
	b.j = -1;
	while (b.i < b.input_len && (b.k = -1))
	{
		b.res_a = b.i < b.input_len ? (int)input[b.i++] : 0;
		b.res_b = b.i < b.input_len ? (int)input[b.i++] : 0;
		b.res_c = b.i < b.input_len ? (int)input[b.i++] : 0;
		b.res_d = (b.res_a << 16) | (b.res_b << 8) | b.res_c;
		while (++b.k < 4)
			output[++b.j] = t[(b.res_d >> (18 - (6 * b.k))) & 0x3F];
	}
	output[b.output_len - 1] = b.res_c == 0 ? '=' : output[b.output_len - 1];
	output[b.output_len - 2] = b.res_b == 0 ? '=' : output[b.output_len - 2];
	return (output);
}

int			*get_decrypt_table(char *input, int input_len, int *output_len)
{
	static int	table[256];
	char		*t;
	int			count;

	t = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	count = -1;
	while (++count < 64)
		table[(int)t[count]] = count;
	*output_len = 3 * (input_len / 4);
	*output_len -= input[input_len - 1] == '=' ? 1 : 0;
	*output_len -= input[input_len - 2] == '=' ? 1 : 0;
	return (table);
}

char		*base64_decrypt(t_ssl *ssl, char *input)
{
	t_base64	b;
	char		*output;
	int			*t;

	b.input_len = (int)ssl->input_len;
	if (!(t = get_decrypt_table(input, b.input_len, &b.output_len)))
		return (NULL);
	if (!(output = ft_strnew(b.output_len)))
		return (NULL);
	b.i = 0;
	b.j = -1;
	while (b.i < b.input_len && (b.k = -1))
	{
		b.res_a = input[b.i] != '=' ? t[(int)input[b.i++]] : 0 & ++b.i;
		b.res_b = input[b.i] != '=' ? t[(int)input[b.i++]] : 0 & ++b.i;
		b.res_c = input[b.i] != '=' ? t[(int)input[b.i++]] : 0 & ++b.i;
		b.res_d = input[b.i] != '=' ? t[(int)input[b.i++]] : 0 & ++b.i;
		b.res_e = (b.res_a << 18) + (b.res_b << 12) + (b.res_c << 6) + b.res_d;
		while (++b.k < 3 && ++b.j < b.output_len)
			output[b.j] = (char)((b.res_e >> (16 - (8 * b.k))) & 0xFF);
	}
	if (output[4] == '\n')
		DB("YES");
	return (output);
}