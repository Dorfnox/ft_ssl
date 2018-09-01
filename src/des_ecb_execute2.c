/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_ecb_execute2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpierce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 00:16:01 by bpierce           #+#    #+#             */
/*   Updated: 2018/08/31 00:16:09 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
**	Turns the character string into a uint64_t message.
**	If there are any remaining bits left, the number of remaining bits
**	required in order to fill the last byte needed are appended to message.
*/

uint64_t	des_ecb_str_to_64bit(char **input, size_t *in_len)
{
	uint8_t		i;
	uint64_t	message;
	uint64_t	remaining;
	uint8_t		shift_amount;

	i = -1;
	message = 0;
	while (++i < 8 && *in_len)
	{
		shift_amount = 56 - (i * 8);
		message |= ((((uint64_t)(**input)) << shift_amount) &
			(0xFFUL << shift_amount));
		++(*input);
		--(*in_len);
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
**	A special decrypt method, silimar to above, that flips all the bits
**	Input will for sure be in chunks of 8 bytes
*/

uint64_t	des_ecb_str_to_64bit_dec(char **input, size_t *len)
{
	uint64_t	message;

	if (*len % 8)
		error_out("Improper input size");
	ft_memcpy(&message, *input, 8);
	message = (message & 0x00000000FFFFFFFF) << 32 |
				(message & 0xFFFFFFFF00000000) >> 32;
	message = (message & 0x0000FFFF0000FFFF) << 16 |
				(message & 0xFFFF0000FFFF0000) >> 16;
	message = (message & 0x00FF00FF00FF00FF) << 8 |
				(message & 0xFF00FF00FF00FF00) >> 8;
	*input += 8;
	*len -= 8;
	return (message);
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
