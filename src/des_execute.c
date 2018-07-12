/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpierce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 13:35:52 by bpierce           #+#    #+#             */
/*   Updated: 2018/05/23 13:35:57 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
**	Main execution loop for des-ecb encryption (electronic cookbook)
*/

char		*execute_des_ecb(t_ssl *ssl, char *input, t_io_len *l)
{
	t_des		des;
	uint64_t	message;
	uint64_t	encryption;
	char		*output;

	init_des(&des);
	init_des_key(ssl, &des);
	init_des_subkeys(&des, ssl->f.d);
	output = create_des_output(ssl, &l->in_len, &l->out_len);
	while (l->out_len < l->in_len)
	{
		message = des_ecb_str_to_64bit(&input);
		printbits_little_endian(&message, 8);
		encryption = process_des_ecb(&des, message);
		insert_64bit_into_string(&output[l->out_len], encryption);
		l->out_len += 8;
	}
	clean_des_ecb(&des);
	return (output);
}

/*
**	Turns the character string into a uint64_t message.
**	If there are any remaining bits left, the number of remaining bits
**	required in order to fill the last byte needed are appended to message.
*/

uint64_t	des_ecb_str_to_64bit(char **input)
{
	uint8_t			i;
	uint64_t	message;
	uint64_t	remaining;

	i = -1;
	message = 0;
	while (++i < 8 && **input)
	{
		message |= ((uint64_t)(**input) << (56 - (i * 8)));
		++(*input);
	}
	remaining = 8 - i;
	while (i < 8)
	{
		message |= (remaining << (56 - (i * 8)));
		++i;
	}
	return (message);
}

/*
**	Allocates enough space for the:
**	- Salted__ (8 bytes)
**	- salt (usually 8 bytes)
**	- input len
**	- An extra 8 bytes in case the input length is a modulus of 8
*/

char		*create_des_output(t_ssl *ssl, size_t *in_len, size_t *out_len)
{
	char		*output;
	int			len;
	uint64_t	salt;

	len = 8 + (PBKDF_SALT_SIZE / 2) + (*in_len) + 8;
	MAL_ERR((output = ft_strnew(len)), "Creating des output");
	*out_len = 0;
	if (ssl->user_password)
	{
		salt = hex_str_to_64bit_le(ssl->user_salt);
		ft_memcpy(output, "Salted__", 8);
		ft_memcpy(&output[8], &salt, PBKDF_SALT_SIZE / 2);
		*out_len = 8 + (PBKDF_SALT_SIZE / 2);
	}
	*in_len += (*out_len + ((*in_len % 8) == 0 ? 8 : 0));
	return (output);
}

/*
**	1) Applies an initial permutation to turn 64 bit message into 56 bit.
**	2) Runs 16 iterations of the des algorithm on right permutation.
**	3) After each iteration the left block becomes the previous right,
**	and the right block is the result of the des algorithm.
**	4) The final left and right are concatenated together in reverse order.
**	5) Return is a final permutation of the right-left concatenation using
**	the inverse table.
*/

uint64_t	process_des_ecb(t_des *des, uint64_t message)
{
	uint64_t	left;
	uint64_t	right;
	uint64_t	reverse;
	int			i;

	des->initial_perm = permutated_choice(message, des->ip_table, 64);
	left = des->initial_perm >> 32;
	right = des->initial_perm & 0xFFFFFFFF;
	des->l[0] = right;
	des->r[0] = left ^ des_alg(des, right, des->subkey[0]);
	i = 0;
	while (++i < 16)
	{
		des->l[i] = des->r[i - 1];
		des->r[i] = des->l[i - 1] ^ des_alg(des, des->r[i - 1], des->subkey[i]);
	}
	reverse = ((uint64_t)des->r[15] << 32) | (uint64_t)des->l[15];
	return (permutated_choice(reverse, des->inverse_table, 64));
}

/*
**	1) Uses the ebit table to expand the current block from 32 to 48 bits.
**	2) XOR's the subkey with the current block after ebit expansion.
**	3) Uses the S Tables to create a new 32 bit block.
**	4) Return is a new block shifted around using the P Table.
*/

uint32_t	des_alg(t_des *des, uint32_t block, uint64_t key)
{
	uint64_t	xor;
	int			row;
	int			col;
	int			i;
	uint32_t	output;

	i = -1;
	xor = 0;
	while (++i < 48)
		xor |= (((uint64_t)block >> (32 - des->ebit[i])) & 1) << (48 - (i + 1));
	xor ^= key;
	i = -1;
	block = 0;
	while (++i < 8)
	{
		row = (xor >> (42 - (6 * i))) & 0x3F;
		col = (row >> 1) & 0xF;
		row = ((row >> 4) & 2) | (row & 1);
		block |= (uint32_t)des->s[i][row][col] << (28 - (4 * i));
	}
	i = -1;
	output = 0;
	while (++i < 32)
		output |= ((block >> (32 - des->p_table[i])) & 1) << (32 - (i + 1));
	return (output);
}
