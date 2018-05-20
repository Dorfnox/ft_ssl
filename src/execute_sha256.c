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

char				*execute_sha256(t_ssl *ssl, char *input)
{
	t_sha256	sha;
	size_t		i;
	size_t		j;

	init_sha256(&sha);
	append_bits_sha256(ssl, &sha, input);
	i = 0;
	while (i < ((ssl->input_len * 8) / 512))
	{
		ft_memcpy(sha.w, &sha.data[i++ * 64], 64);
		j = 15;
		while (++j < 64)
		{
			sha.tmpa = RIGHT_ROTATE(sha.w[j - 15], 7) ^ RIGHT_ROTATE(sha.w[j - 15], 18) ^ sha.w[j - 15] >> 3;
			sha.tmpb = RIGHT_ROTATE(sha.w[j - 2], 17) ^ RIGHT_ROTATE(sha.w[j - 2], 19) ^ sha.w[j - 2] >> 10;
			sha.w[j] = sha.w[j - 16] + sha.tmpa + sha.w[j - 7] + sha.tmpb;
		}
		sha.a = sha.h0;
		sha.b = sha.h1;
		sha.c = sha.h2;
		sha.d = sha.h3;
		sha.e = sha.h4;
		sha.f = sha.h5;
		sha.g = sha.h6;
		sha.h = sha.h7;
		j = -1;
		while (++j < 64)
		{
			sha.tmpa = RIGHT_ROTATE(sha.e, 6) ^ RIGHT_ROTATE(sha.e, 11) ^ RIGHT_ROTATE(sha.e, 25);
			sha.tmpb = (sha.e & sha.f) ^ ((~sha.e) & sha.g);
			sha.tmpc = sha.h + sha.tmpa + sha.tmpb + sha.k[j] + sha.w[j];
			sha.tmpd = RIGHT_ROTATE(sha.a, 2) ^ RIGHT_ROTATE(sha.a, 13) ^ RIGHT_ROTATE(sha.a, 22);
			sha.tmpe = (sha.a & sha.b) ^ (sha.a & sha.c) ^ (sha.b & sha.c);
			sha.tmpf = sha.tmpd + sha.tmpe;
			sha.h = sha.g;
			sha.g = sha.f;
			sha.f = sha.e;
			sha.e = sha.d + sha.tmpc;
			sha.d = sha.c;
			sha.c = sha.b;
			sha.b = sha.a;
			sha.a = sha.tmpc + sha.tmpf;
		}
		sha.h0 += sha.a;
		sha.h1 += sha.b;
		sha.h2 += sha.c;
		sha.h3 += sha.d;
		sha.h4 += sha.e;
		sha.h5 += sha.f;
		sha.h6 += sha.g;
		sha.h7 += sha.h;
	}
	clean_sha256(&sha);
	return (build_sha256_output(&sha));
}

void				append_bits_sha256(t_ssl *ssl, t_sha256 *sha, char *input)
{
	uint64_t	num_of_bits;
	uint64_t	zero_bits;

	num_of_bits = ssl->input_len * 8;
	zero_bits = 0;
	while ((num_of_bits + 1 + zero_bits + 64) % 512)
		zero_bits++;
	sha->data = malloc(ssl->input_len + 1 + (zero_bits / 8) + 8);
	ft_pflite("input length: %u\nzero bits:    %u\nzero bits/8:  %u\ntotal:        %u\n", ssl->input_len, zero_bits, zero_bits / 8, ssl->input_len + (zero_bits / 8) + 1 + 8);
	ft_memcpy(sha->data, input, ssl->input_len);
	sha->data[ssl->input_len] = 128;
	num_of_bits = TO_BIG_ENDIAN64(&num_of_bits);
	DBI(num_of_bits);
	ft_memcpy(sha->data + ssl->input_len + (zero_bits / 8) + 1, &num_of_bits, 8);
	ssl->input_len += 1 + (zero_bits / 8) + 8;
}

char				*build_sha256_output(t_sha256 *sha)
{
	char			*hex_string;
	char			*output;
	int				i;
	unsigned int	j;
	t_32bitunion	u;

	hex_string = "0123456789abcdef";
	if (!(output = malloc(sizeof(char) * 65)))
		return (NULL);
	j = 0;
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
		// u.v = i < 56 ? sha->h1 : sha->h0;
		// u.v = i < 48 ? sha->h2: u.v;
		// u.v = i < 40 ? sha->h3 : u.v;
		// u.v = i < 32 ? sha->h4 : u.v;
		// u.v = i < 24 ? sha->h5 : u.v;
		// u.v = i < 16 ? sha->h6 : u.v;
		// u.v = i < 8 ? sha->h7 : u.v;
		output[i++] = hex_string[u.p8[j % 4] >> 4];
		output[i++] = hex_string[u.p8[j++ % 4] & 0xF];
	}
	output[64] = 0;
	return (output);
}

void				clean_sha256(t_sha256 *sha)
{
	free(sha->data);
}
