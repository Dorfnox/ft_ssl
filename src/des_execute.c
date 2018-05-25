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
**	REQUIRES a '\0' char string as input;
*/

char		*execute_des_ecb(t_ssl *ssl, char *input)
{
	t_des		des;
	uint64_t	message;
	uint64_t	encryption;
	char		*output;
	size_t		len;

	des.user_key = ssl->user_key;
	init_des(&des);
	if (!(output = ft_strnew(ssl->input_len +
		(!(ssl->input_len % 8) ? 0 : 8 - (ssl->input_len % 8)))))
		return (NULL);
	len = 0;
	while (len < ssl->input_len)
	{
		message = create_message_block(&input);
		message = 0x0123456789abcdef; // REMOVE - this is for testing
		DB("Message");
		printbits_little_endian(&message, 8);
		encryption = process_des_ecb(&des, message);
		DB("Encrypted Message");
		printbits_little_endian(&encryption, 8);
		ft_memcpy(&output[len], &encryption, 8);
		len += 8;
	}
	clean_des_ecb(&des);
	return (output);
}

/*
**	Creates the uint64_t message from 64 bits of the input,
**	then moves the input pointer for next cycle;
*/

uint64_t	create_message_block(char **input)
{
	int			i;
	uint64_t	message;

	i = -1;
	message = 0;
	while (**input && ++i < 8)
	{
		message |= ((uint64_t)(**input) << (56 - (i * 8)));
		++(*input);
	}
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

void		clean_des_ecb(t_des *des)
{
	int		i;
	int		j;

	free(des->pc1);
	free(des->pc2);
	free(des->shifts);
	free(des->ip_table);
	free(des->ebit);
	i = -1;
	while (++i < 8)
	{
		j = -1;
		while (++j < 4)
			free(des->s[i][j]);
	}
	free(des->p_table);
	free(des->inverse_table);
}
