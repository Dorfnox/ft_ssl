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
**	Main loop for handling sha224 execution
**	As the implementation is nearly identical to sha256,
**	it uses the same functions, for the most part.
**	The only difference is that the h0 - h7 values are initialized differently,
**	and h7 is not used in the digest.
**	Built for use on a system that uses LITTLE ENDIAN.
*/

char	*execute_sha224(t_ssl *ssl, char *input, size_t input_len)
{
	t_sha256	sha;
	size_t		i;
	size_t		k;
	size_t		number_of_chunks;

	(void)ssl;
	init_sha224(&sha);
	append_bits_sha256(&sha, input, &input_len);
	i = -1;
	k = 0;
	number_of_chunks = input_len * 8 / 512;
	while (++i < number_of_chunks)
	{
		init_words(&sha, &k);
		init_working_variables(&sha);
		perform_algorithm(&sha);
		add_to_digest(&sha);
	}
	clean_sha256(&sha);
	return (build_sha224_output(&sha));
}

void	init_sha224(t_sha256 *sha)
{
	sha->h0 = 0xc1059ed8;
	sha->h1 = 0x367cd507;
	sha->h2 = 0x3070dd17;
	sha->h3 = 0xf70e5939;
	sha->h4 = 0xffc00b31;
	sha->h5 = 0x68581511;
	sha->h6 = 0x64f98fa7;
	sha->h7 = 0xbefa4fa4;
	init_sha256_k_table1(sha);
	init_sha256_k_table2(sha);
	init_sha256_k_table3(sha);
}

char	*build_sha224_output(t_sha256 *sha)
{
	char			*hex_string;
	char			*output;
	int				i;
	unsigned int	j;
	t_32bitunion	u;

	hex_string = "0123456789abcdef";
	if (!(output = malloc(sizeof(char) * 57)))
		return (NULL);
	j = 3;
	i = 0;
	while (i < 56)
	{
		u.v = i < 48 ? sha->h5 : sha->h6;
		u.v = i < 40 ? sha->h4 : u.v;
		u.v = i < 32 ? sha->h3 : u.v;
		u.v = i < 24 ? sha->h2 : u.v;
		u.v = i < 16 ? sha->h1 : u.v;
		u.v = i < 8 ? sha->h0 : u.v;
		output[i++] = hex_string[(u.p8[j % 4] >> 4) & 0xf];
		output[i++] = hex_string[u.p8[j-- % 4] & 0xF];
	}
	output[56] = 0;
	return (output);
}
