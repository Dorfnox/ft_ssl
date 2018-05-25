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

char		*execute_des_ecb(t_ssl *ssl, char *input)
{
	t_des	des;
	char	*output;

	des.user_key = ssl->user_key;
	init_des(&des);
	output = NULL;
	while (ssl->input_len)
	{
		DB("message");
		create_message_block(ssl, &des, &input);
		printbits_little_endian(&des.message, 8);
		DB("initial permutation");
		des.initial_perm = permutated_choice(des.message, des.ip_table, 64);
		printbits_little_endian(&des.initial_perm, 8);
		DB("subkey application");
		process_permutation_using_subkeys(&des);
	}
	clean_des_ecb(&des);
	return (output);
}

/*
**	Creates the uint64_t message from 64 bits of the input,
**	then moves the input pointer for next cycle;
*/

void		create_message_block(t_ssl *ssl, t_des *des, char **input)
{
	int		i;

	i = -1;
	des->message = 0;
	while (ssl->input_len && ssl->input_len-- && ++i < 8)
		des->message |= ((uint64_t)(*input)[i] << (56 - (i * 8)));
	*input += ssl->input_len != 0 ? 8 : 0;
	des->message = 0x0123456789abcdef; // REMOVE - this is for testing
}

/*
**	16 iterations 
*/

void		process_permutation_using_subkeys(t_des *des)
{
	uint64_t	left;
	uint64_t	right;
	uint64_t	reverse;
	uint64_t	output;
	int			i;

	left = des->initial_perm >> 32;
	right = des->initial_perm & 0xFFFFFFFF;
	des->l[0] = right;
	des->r[0] = left ^ apply_des_subkey(des, right, des->subkey[0]);
	printbits_little_endian(&des->l[0], 4);
	printbits_little_endian(&des->r[0], 4);
	i = 0;
	while (++i < 16)
	{
		des->l[i] = des->r[i - 1];
		des->r[i] = des->l[i - 1] ^ apply_des_subkey(des, des->r[i - 1], des->subkey[i]);
	}
	reverse = ((uint64_t)des->r[15] << 32) | (uint64_t)des->l[15];
	i = -1;
	output = 0;
	while (++i < 64)
		output |= ((reverse >> (64 - des->inverse_table[i])) & 1) << (64 - (i + 1));
	DB("Result");
	printbits_little_endian(&output, 8);
	exit(0);
}

uint32_t	apply_des_subkey(t_des *des, uint32_t block, uint64_t key)
{
	uint64_t	ebit48;
	uint64_t	xor;
	int			row;
	int			col;
	int			i;
	uint32_t	out;
	uint32_t		out2;

	printbits_little_endian(&block, 4);
	ebit48 = get_ebit(des, block);
	DB("ebit");
	printbits_little_endian(&ebit48, 8);
	xor = ebit48 ^ key;
	DB("xor");
	printbits_little_endian(&xor, 8);
	i = -1;
	out = 0;
	while (++i < 8 || !(i = -1))
	{
		row = (xor >> (42 - (6 * i))) & 0x3F;
		col = (row >> 1) & 0xF;
		row = ((row >> 4) & 2) | (row & 1);
		out |= (uint32_t)des->s[i][row][col] << (28 - (4 * i));
	}
	out2 = 0;
	while (++i < 32)
		out2 |= ((out >> (32 - des->p_table[i])) & 1) << (32 - (i + 1));
	printbits_little_endian(&out, 4);
	printbits_little_endian(&out2, 4);
	return (out2);
}

uint64_t	get_ebit(t_des *des, uint32_t b)
{
	uint64_t	ebit;
	int			i;

	i = -1;
	ebit = 0;
	while (++i < 48)
		ebit |= (((uint64_t)b >> (32 - des->ebit[i])) & 1) << (48 - (i + 1));
	return (ebit);
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
