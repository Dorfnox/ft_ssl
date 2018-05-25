/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpierce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 13:40:53 by bpierce           #+#    #+#             */
/*   Updated: 2018/05/23 13:40:58 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
**	Initializes des struct, as well as the keys and subkeys to be used in des
*/

void		init_des(t_des *des)
{
	des->pc1 = ft_intarrayfromstr(PERMUTATED_CHOICE_1);
	des->pc2 = ft_intarrayfromstr(PERMUTATED_CHOICE_2);
	des->shifts = ft_intarrayfromstr(NUM_OF_SHIFTS);
	des->ip_table = ft_intarrayfromstr(IP_TABLE);
	des->ebit = ft_intarrayfromstr(EBIT_TABLE);
	GET_S1;
	GET_S2;
	GET_S3;
	GET_S4;
	GET_S5;
	GET_S6;
	GET_S7;
	GET_S8;
	des->p_table = ft_intarrayfromstr(P_TABLE);
	des->inverse_table = ft_intarrayfromstr(INVERSE_TABLE);
}

void		initialize_des_keys(t_des *des, char *user_key)
{
	int			i;
	uint64_t	lr;

	des->key = key_string_to_hex(user_key);
	des->key_pc1 = permutated_choice(des->key, des->pc1, 56);
	des->l[0] = LEFT_ROT_28(des->key_pc1 >> 28, des->shifts[0]);
	des->r[0] = LEFT_ROT_28(des->key_pc1 & 0xFFFFFFF, des->shifts[0]);
	i = 0;
	while (++i < 16)
	{
		des->l[i] = LEFT_ROT_28(des->l[i - 1], des->shifts[i]);
		des->r[i] = LEFT_ROT_28(des->r[i - 1], des->shifts[i]);
	}
	i = -1;
	while (++i < 16)
	{
		lr = ((uint64_t)des->l[i] << 28) | (uint64_t)des->r[i];
		des->subkey[i] = permutated_choice(lr, des->pc2, 48);
	}
}

uint64_t	key_string_to_hex(char *key_string)
{
	int			i;
	uint64_t	x;
	uint64_t	hex_char;

	i = -1;
	x = 0;
	while (++i < 16)
	{
		hex_char = key_string[i];
		hex_char -= hex_char  > 47 && hex_char < 58 ? 48 : 0;
		hex_char -= hex_char  > 64 && hex_char < 71 ? 55 : 0;
		x |= (hex_char & 0xF) << (60 - (i * 4));
	}
	return (x);
}

uint64_t	permutated_choice(uint64_t key, int *pc, int size)
{
	int			i;
	uint64_t	newkey;

	i = -1;
	newkey = 0;
	while (++i < size)
		newkey |= (key >> (MAX_64(size + 8) - pc[i]) & 1) << (size - (i + 1));
	return (newkey);
}
