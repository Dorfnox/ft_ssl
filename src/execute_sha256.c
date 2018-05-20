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
**	Main loop for handling sha256 execution
**	Built for use on a system that uses LITTLE ENDIAN.
*/

char	*execute_sha256(t_ssl *ssl, char *input)
{
	t_sha256	sha;
	size_t		i;
	size_t		k;
	size_t		number_of_chunks;

	init_sha256(&sha);
	append_bits_sha256(ssl, &sha, input);
	i = -1;
	k = 0;
	number_of_chunks = ssl->input_len * 8 / 512;
	while (++i < number_of_chunks)
	{
		init_words(&sha, &k);
		init_working_variables(&sha);
		perform_algorithm(&sha);
		add_to_digest(&sha);
	}
	clean_sha256(&sha);
	return (build_sha256_output(&sha));
}

void	init_words(t_sha256 *sha, size_t *k)
{
	unsigned short	j;

	j = -1;
	while (++j < 16)
	{
		sha->w[j] = (((uint32_t)sha->data[*k]) << 24) |
					(((uint32_t)sha->data[*k + 1]) << 16) |
					(((uint32_t)sha->data[*k + 2]) << 8) |
					((uint32_t)sha->data[*k + 3]);
		*k += 4;
	}
	j = 15;
	while (++j < 64)
	{
		sha->tmpa = RIGHT_ROTATE(sha->w[j - 15], 7) ^
					RIGHT_ROTATE(sha->w[j - 15], 18) ^
					sha->w[j - 15] >> 3;
		sha->tmpb = RIGHT_ROTATE(sha->w[j - 2], 17) ^
					RIGHT_ROTATE(sha->w[j - 2], 19) ^
					sha->w[j - 2] >> 10;
		sha->w[j] = sha->w[j - 16] + sha->tmpa + sha->w[j - 7] + sha->tmpb;
	}
}

void	init_working_variables(t_sha256 *sha)
{
	sha->a = sha->h0;
	sha->b = sha->h1;
	sha->c = sha->h2;
	sha->d = sha->h3;
	sha->e = sha->h4;
	sha->f = sha->h5;
	sha->g = sha->h6;
	sha->h = sha->h7;
}

void	perform_algorithm(t_sha256 *sha)
{
	unsigned short	j;

	j = -1;
	while (++j < 64)
	{
		sha->tmpa = RIGHT_ROTATE(sha->e, 6) ^ RIGHT_ROTATE(sha->e, 11) ^ RIGHT_ROTATE(sha->e, 25);
		sha->tmpb = (sha->e & sha->f) ^ ((~sha->e) & sha->g);
		sha->tmpc = sha->h + sha->tmpa + sha->tmpb + sha->k[j] + sha->w[j];
		sha->tmpd = RIGHT_ROTATE(sha->a, 2) ^ RIGHT_ROTATE(sha->a, 13) ^ RIGHT_ROTATE(sha->a, 22);
		sha->tmpe = (sha->a & sha->b) ^ (sha->a & sha->c) ^ (sha->b & sha->c);
		sha->tmpf = sha->tmpd + sha->tmpe;
		sha->h = sha->g;
		sha->g = sha->f;
		sha->f = sha->e;
		sha->e = sha->d + sha->tmpc;
		sha->d = sha->c;
		sha->c = sha->b;
		sha->b = sha->a;
		sha->a = sha->tmpc + sha->tmpf;
	}
}

void	add_to_digest(t_sha256 *sha)
{
	sha->h0 += sha->a;
	sha->h1 += sha->b;
	sha->h2 += sha->c;
	sha->h3 += sha->d;
	sha->h4 += sha->e;
	sha->h5 += sha->f;
	sha->h6 += sha->g;
	sha->h7 += sha->h;
}
