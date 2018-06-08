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

/*
**	If no user key was provided,
**	creates PBKDF parameters and calls pbkdf using the parameters.
**	The iv is not used, but is still saved here.
*/

void		init_des_key(t_ssl *ssl, t_des *des)
{
	t_pbkdf		p;
	int			i;
	char		buff;

	if (!ssl->user_key)
	{
		p.password = ssl->user_password;
		p.pass_len = ft_strlen(ssl->user_password);
		p.salt = hex_str_to_64bit_le(ssl->user_salt);
		p.salt_len = PBKDF_SALT_SIZE / 2;
		p.num_of_iterations = PBKDF_ITERATIONS;
		p.algo = PBKDF_ALGO;
		pbkdf2(&p);
		ssl->user_key = p.key;
		ssl->iv = p.iv;
	}
	i = -1;
	des->key = 0;
	while ((buff = ssl->user_key[++i]))
	{
		buff -= buff  > 47 && buff < 58 ? 48 : 0;
		buff -= buff  > 64 && buff < 71 ? 55 : 0;
		des->key |= (buff & 0xF) << (60 - (i * 4));
	}
}

/*
**	Builds the 16 subkeys.
**	If the reverse flag is on, ft_varrayrev will reverse the keys.
*/

void		init_des_subkeys(t_des *des, uint8_t reverse)
{
	int			i;
	char		buff;

	des->key_pc1 = permutated_choice(des->key, des->pc1, 56);
	des->l[0] = LEFT_ROT_28(des->key_pc1 >> 28, des->shifts[0]);
	des->r[0] = LEFT_ROT_28(des->key_pc1 & 0xFFFFFFF, des->shifts[0]);
	i = 0;
	while (++i < 16 || !(i = -1))
	{
		des->l[i] = LEFT_ROT_28(des->l[i - 1], des->shifts[i]);
		des->r[i] = LEFT_ROT_28(des->r[i - 1], des->shifts[i]);
	}
	while (++i < 16)
	{
		buff = ((uint64_t)des->l[i] << 28) | (uint64_t)des->r[i];
		des->subkey[i] = permutated_choice(buff, des->pc2, 48);
	}
	if (reverse)
		ft_varrayrev((void **)(&des->subkey), 16);
}

/*
**	Wide usage:
**	Takes the input table and size of the table and can permutate
**	going smaller as well as staying at 64 bits.
**	The only situation where it won't work is moving bigger,
**	ex: moving from a 32-bit storage to 48.
*/

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
