/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_sha256_helper.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpierce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 14:57:38 by bpierce           #+#    #+#             */
/*   Updated: 2018/05/20 14:57:44 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"


void	append_bits_sha256(t_ssl *ssl, t_sha256 *sha, char *input)
{
	uint64_t	num_of_bits;
	uint64_t	zero_bits;

	num_of_bits = ssl->input_len * 8;
	zero_bits = 0;
	while ((num_of_bits + 1 + zero_bits + 64) % 512)
		zero_bits++;
	sha->data = ft_memalloc(ssl->input_len + 1 + (zero_bits / 8) + 8);
	ft_memcpy(sha->data, input, ssl->input_len);
	sha->data[ssl->input_len] = 128;
	num_of_bits = swap_endian64(num_of_bits);
	ft_memcpy(sha->data + ssl->input_len + (zero_bits / 8) + 1, &num_of_bits, 8);
	ssl->input_len += (1 + (zero_bits / 8) + 8);
}

char	*build_sha256_output(t_sha256 *sha)
{
	char			*hex_string;
	char			*output;
	int				i;
	unsigned int	j;
	t_32bitunion	u;

	hex_string = "0123456789abcdef";
	if (!(output = malloc(sizeof(char) * 65)))
		return (NULL);
	j = 3;
	i = 0;
	while (i < 64)
	{
		u.v = i < 56 ? sha->h6 : sha->h7;
		u.v = i < 48 ? sha->h5: u.v;
		u.v = i < 40 ? sha->h4 : u.v;
		u.v = i < 32 ? sha->h3 : u.v;
		u.v = i < 24 ? sha->h2 : u.v;
		u.v = i < 16 ? sha->h1 : u.v;
		u.v = i < 8 ? sha->h0 : u.v;
		output[i++] = hex_string[(u.p8[j % 4] >> 4) & 0xf];
		output[i++] = hex_string[u.p8[j-- % 4] & 0xF];
	}
	output[64] = 0;
	return (output);
}

void	clean_sha256(t_sha256 *sha)
{
	free(sha->data);
}